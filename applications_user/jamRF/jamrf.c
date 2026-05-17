#include "core/check.h"
#include "core/log.h"
#include "core/thread.h"
#include "furi_hal_region.h"
#include "furi_hal_resources.h"
#include "helpers/radio_device_loader.h"
#include "input/input.h"
#include <furi.h>
#include <furi_hal.h>
#include <gui/elements.h>
#include <gui/gui.h>
#include <lib/subghz/subghz_tx_rx_worker.h>
#include <stdint.h>
#include <subghz/devices/devices.h>

#define SNPRINTF_FREQUENCY(buff, freq)                                         \
  snprintf(buff, sizeof(buff), "%03u.%03u", freq / 1000000 % 1000,             \
           freq / 1000 % 1000);

#define DEBUG(...) FURI_LOG_D("JamRF", __VA_ARGS__);
#define ERROR(...) FURI_LOG_E("JamRF", __VA_ARGS__);
#define INFO(...) FURI_LOG_I("JamRF", __VA_ARGS__);

typedef struct {
  size_t frequency_idx;
  volatile bool active;

  const SubGhzDevice *subghz_device;
  SubGhzTxRxWorker *subghz_txrx;

  FuriThread *tx_thread;

} JamRFModel;

typedef struct {
  Gui *gui;
  ViewPort *view_port;

  FuriMutex *model_mutex;
  JamRFModel *model;

  FuriMessageQueue *event_queue;
} JamRF;

static const unsigned int frequencies[] = {
    300000000, 302750000, 303870000, 303900000, 304250000, 307000000, 307500000,
    307800000, 309000000, 310000000, 312000000, 312100000, 312200000, 313000000,
    313850000, 314000000, 314350000, 314980000, 315000000, 318000000, 320000000,
    320150000, 330000000, 345000000, 348000000, 350000000, 387000000, 390000000,
    418000000, 430000000, 430500000, 431000000, 431500000, 433070000, 433220000,
    433420000, 433650000, 433880000, 433920000, 434070000, 434170000, 434190000,
    434390000, 434420000, 434620000, 434770000, 438900000, 440170000, 464000000,
    467000000, 779000000, 868350000, 868400000, 868800000, 868950000, 906400000,
    915000000, 925000000, 928000000};

static const size_t NUM_FREQS = sizeof(frequencies) / sizeof(frequencies[0]);

static void render_callback(Canvas *const canvas, void *ctx) {
  JamRF *app = ctx;

  furi_mutex_acquire(app->model_mutex, FuriWaitForever);

  elements_button_center(canvas, app->model->active ? "Stop" : "Start");

  canvas_set_font(canvas, FontBigNumbers);

  char buffer[8];

  SNPRINTF_FREQUENCY(buffer, frequencies[app->model->frequency_idx]);

  canvas_draw_str_aligned(canvas, 64, 30, AlignCenter, AlignCenter, buffer);

  furi_mutex_release(app->model_mutex);
}

static void input_callback(InputEvent *ev, void *ctx) {
  JamRF *app = ctx;

  furi_message_queue_put(app->event_queue, ev, FuriWaitForever);
}

static int32_t jammer_tx_thread(void *ctx) {
  JamRF *app = ctx;

  uint8_t data[1024];

  furi_hal_random_fill_buf(data, sizeof(data));

  while (app->model->active && app->model->subghz_txrx) {
    INFO("Sending data");
    if (!subghz_tx_rx_worker_write(app->model->subghz_txrx, data,
                                   sizeof(data))) {
      ERROR("Error sending data");
      furi_delay_ms(20);
    }
    furi_delay_ms(10);
  }

  return 0;
}

static void jammer_adjust_frequency(JamRF *app, bool up) {
  if (up) {
    if (app->model->frequency_idx < NUM_FREQS - 1) {
      app->model->frequency_idx++;
      INFO("Adjusted frequency up");
    }
  } else {
    if (app->model->frequency_idx > 0) {
      app->model->frequency_idx--;
      INFO("Adjusted frequency down");
    }
  }
}

static bool jammer_start(JamRF *app) {
  furi_assert(app->model->active);
  INFO("Jammer started");

  app->model->tx_thread = furi_thread_alloc();
  furi_thread_set_name(app->model->tx_thread, "Jamming transmit");
  furi_thread_set_stack_size(app->model->tx_thread, 2048);
  furi_thread_set_context(app->model->tx_thread, app);
  furi_thread_set_callback(app->model->tx_thread, jammer_tx_thread);

  furi_thread_start(app->model->tx_thread);

  return subghz_tx_rx_worker_start(app->model->subghz_txrx,
                                   app->model->subghz_device,
                                   frequencies[app->model->frequency_idx]);
}

static void jammer_stop(JamRF *app) {
  furi_assert(!app->model->active);

  if (subghz_tx_rx_worker_is_running(app->model->subghz_txrx)) {
    subghz_tx_rx_worker_stop(app->model->subghz_txrx);
  }

  if (app->model->tx_thread) {
    furi_thread_join(app->model->tx_thread);
    furi_thread_free(app->model->tx_thread);
    app->model->tx_thread = NULL;
  }
}

static JamRF *jamrf_alloc() {
  JamRF *app = malloc(sizeof(JamRF));

  app->model = malloc(sizeof(JamRFModel));
  app->model->frequency_idx = 18; // 315.00 MHz
  app->model->active = false;

  subghz_devices_init();

  app->model->subghz_device =
      radio_device_loader_set(NULL, SubGhzRadioDeviceTypeExternalCC1101);

  if (!app->model->subghz_device) {
    app->model->subghz_device =
        radio_device_loader_set(NULL, SubGhzRadioDeviceTypeInternal);
  }

  furi_assert(app->model->subghz_device != NULL);

  subghz_devices_reset(app->model->subghz_device);
  subghz_devices_idle(app->model->subghz_device);

  subghz_devices_load_preset(app->model->subghz_device,
                             FuriHalSubGhzPresetOok650Async, NULL);

  app->model->subghz_txrx = subghz_tx_rx_worker_alloc();

  app->model_mutex = furi_mutex_alloc(FuriMutexTypeNormal);
  app->event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

  app->view_port = view_port_alloc();
  view_port_draw_callback_set(app->view_port, render_callback, app);
  view_port_input_callback_set(app->view_port, input_callback, app);

  app->gui = furi_record_open(RECORD_GUI);

  gui_add_view_port(app->gui, app->view_port, GuiLayerFullscreen);

  return app;
}

void jamrf_free(JamRF *app) {
  furi_hal_power_suppress_charge_exit();

  jammer_stop(app);

  if (app->model->subghz_txrx) {
    subghz_tx_rx_worker_free(app->model->subghz_txrx);
    app->model->subghz_txrx = NULL;
  }

  if (radio_device_loader_is_external(app->model->subghz_device)) {
    if (furi_hal_power_is_otg_enabled()) {
      furi_hal_power_disable_otg();
    }
  } else {
    radio_device_loader_end(app->model->subghz_device);
  }

  app->model->subghz_device = NULL;

  subghz_devices_deinit();

  gui_remove_view_port(app->gui, app->view_port);
  furi_record_close(RECORD_GUI);
  view_port_free(app->view_port);

  furi_message_queue_free(app->event_queue);
  furi_mutex_free(app->model_mutex);

  free(app->model);
  free(app);
}

int32_t jamrf_app(void *p) {
  UNUSED(p);

  furi_hal_power_suppress_charge_enter();

  JamRF *app = jamrf_alloc();

  InputEvent input;
  while (furi_message_queue_get(app->event_queue, &input, FuriWaitForever) ==
         FuriStatusOk) {

    if (input.key == InputKeyBack && input.type == InputTypeLong) {
      break;
    }

    furi_check(furi_mutex_acquire(app->model_mutex, FuriWaitForever) ==
               FuriStatusOk);

    if (input.key == InputKeyOk && input.type == InputTypePress) {
      if (app->model->active) {
        app->model->active = false;
        jammer_stop(app);

        goto cleanup;
      }

      // if inactive
      INFO("Attempting Freq: %03u.%03u",
           frequencies[app->model->frequency_idx] / 1000000 % 1000,
           frequencies[app->model->frequency_idx] / 1000 % 1000);

      if (!furi_hal_region_is_frequency_allowed(
              frequencies[app->model->frequency_idx])) {
        goto cleanup;
      }

      app->model->active = true;

      if (!jammer_start(app)) {
        ERROR("Error starting jammer");
        break;
      }
    } else if (!app->model->active && (input.type == InputTypePress ||
                                       input.type == InputTypeRepeat)) {
      if (input.key == InputKeyLeft) {
        jammer_adjust_frequency(app, false);
      } else if (input.key == InputKeyRight) {
        jammer_adjust_frequency(app, true);
      }
    }

  cleanup:
    furi_mutex_release(app->model_mutex);
    view_port_update(app->view_port);
  }

  jamrf_free(app);

  return 0;
}
