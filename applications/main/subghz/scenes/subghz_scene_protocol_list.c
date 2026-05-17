#include "../subghz_i.h"
#include <lib/subghz/subghz_protocol_registry.h>

void subghz_scene_protocol_list_submenu_callback(void* context, uint32_t index) {
    SubGhz* subghz = context;
    view_dispatcher_send_custom_event(subghz->view_dispatcher, index);
}

void subghz_scene_protocol_list_on_enter(void* context) {
    SubGhz* subghz = context;

    submenu_reset(subghz->submenu);

    size_t protocol_count = subghz_protocol_registry_count(&subghz_protocol_registry);
    
    char header_str[32];
    snprintf(header_str, sizeof(header_str), "Protocols: %zu", protocol_count);
    submenu_set_header(subghz->submenu, header_str);

    for(size_t i = 0; i < protocol_count; i++) {
        const SubGhzProtocol* protocol =
            subghz_protocol_registry_get_by_index(&subghz_protocol_registry, i);
        if(protocol) {
            submenu_add_item(
                subghz->submenu,
                protocol->name,
                i,
                subghz_scene_protocol_list_submenu_callback,
                subghz);
        }
    }

    submenu_set_selected_item(
        subghz->submenu,
        scene_manager_get_scene_state(subghz->scene_manager, SubGhzSceneProtocolList));

    view_dispatcher_switch_to_view(subghz->view_dispatcher, SubGhzViewIdMenu);
}

bool subghz_scene_protocol_list_on_event(void* context, SceneManagerEvent event) {
    SubGhz* subghz = context;

    if(event.type == SceneManagerEventTypeCustom) {
        scene_manager_set_scene_state(subghz->scene_manager, SubGhzSceneProtocolList, event.event);
        return true;
    }
    return false;
}

void subghz_scene_protocol_list_on_exit(void* context) {
    SubGhz* subghz = context;
    submenu_reset(subghz->submenu);
}
