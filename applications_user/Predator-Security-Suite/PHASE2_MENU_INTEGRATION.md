# Phase 2 Menu & UI Integration Guide
## Complete Scene Architecture for New Cryptographic Algorithms

**Date**: October 18, 2025  
**Purpose**: Integration plan for Phase 2A/2B algorithms into Predator UI  
**Status**: Implementation Ready

---

## 🎯 Overview

We've added **7 new cryptographic protocols** that need UI integration:

### Phase 2A (Complete)
1. **ISO 15693** - Enterprise/Library RFID
2. **EM4305** - Writable 125kHz (Cloning)
3. **FeliCa** - Japan/Asia-Pacific Transit
4. **Calypso** - European Transit (Paris, Brussels)

### Phase 2B (Complete)
5. **Legic** - Swiss/German/Austrian Access
6. **SECURAKEY/Wiegand** - North American Access
7. **UltraLight C** - Global Transit Tickets

---

## 📂 Proposed Menu Structure

```
PREDATOR MAIN MENU
├── Car Attacks (existing)
│   └── ... (no changes)
│
├── WiFi Attacks (existing)
│   └── ... (no changes)
│
├── Bluetooth Attacks (existing)
│   └── ... (no changes)
│
├── RFID/NFC Attacks *** EXPANDED ***
│   ├── MIFARE Classic (existing)
│   ├── MIFARE DESFire *** NEW (Phase 1) ***
│   ├── iClass (existing header-only)
│   ├── EM4100 Read (existing)
│   ├── EM4305 Clone *** NEW (Phase 2A) ***
│   ├── HID Prox (existing)
│   ├── ISO 15693 *** NEW (Phase 2A) ***
│   └── UltraLight C *** NEW (Phase 2B) ***
│
├── Transit Cards *** NEW CATEGORY ***
│   ├── FeliCa (Japan/Asia) *** NEW (Phase 2A) ***
│   ├── Calypso (Europe) *** NEW (Phase 2A) ***
│   ├── UltraLight (Global) *** NEW (Phase 2B) ***
│   └── Legic (Switzerland) *** NEW (Phase 2B) ***
│
├── Access Control *** NEW CATEGORY ***
│   ├── Wiegand/SECURAKEY *** NEW (Phase 2B) ***
│   ├── HID Prox (existing, move here)
│   ├── MIFARE Classic (copy)
│   ├── DESFire (copy)
│   ├── ISO 15693 (copy)
│   └── Legic (copy)
│
├── SubGHz Attacks (existing)
│   └── ... (no changes)
│
├── Module Status (existing)
├── Board Selection (existing)
├── Settings (existing)
└── About (existing)
```

---

## 🎨 Scene Files to Create

### Priority 1: Critical New Categories

#### 1. Transit Cards Menu
**File**: `scenes/predator_scene_transit_cards_menu_ui.c`
```c
// Submenu with 4 items:
// - FeliCa (Japan/Asia)
// - Calypso (Europe)
// - UltraLight (Global)
// - Legic (Swiss)
```

#### 2. Access Control Menu
**File**: `scenes/predator_scene_access_control_menu_ui.c`
```c
// Submenu with 6 items:
// - Wiegand/SECURAKEY
// - HID Prox
// - MIFARE Classic
// - MIFARE DESFire
// - ISO 15693
// - Legic
```

---

### Priority 2: FeliCa Implementation (HIGHEST VALUE)

#### Scene 1: FeliCa Card Reader
**File**: `scenes/predator_scene_felica_read_ui.c`
```c
typedef struct {
    FeliCaCard card;
    bool card_detected;
    uint16_t balance;
    FeliCaTransaction transactions[10];
    uint32_t transaction_count;
    char station_names[10][32];
    uint32_t refresh_timer;
} FeliCaReadState;

// UI Elements:
// - Card detection status
// - Card type (Suica, Pasmo, ICOCA, etc.)
// - Current balance (¥xxx)
// - Last 10 transactions with station names
// - Real-time updates
```

#### Scene 2: FeliCa Transaction History
**File**: `scenes/predator_scene_felica_history_ui.c`
```c
// Scrollable list of transactions:
// - Date/Time
// - Station name (decoded from ID)
// - Transaction type (Entry/Exit/Purchase)
// - Amount
// - Balance after transaction
```

#### Scene 3: FeliCa Card Dump
**File**: `scenes/predator_scene_felica_dump_ui.c`
```c
// Full card dump interface:
// - IDm/PMm display
// - System codes
// - Service codes
// - Raw block data
// - Save to SD card option
```

---

### Priority 3: Calypso Implementation (PARIS METRO)

#### Scene 1: Calypso Card Reader
**File**: `scenes/predator_scene_calypso_read_ui.c`
```c
typedef struct {
    CalypsoCard card;
    bool card_detected;
    CalypsoContract contracts[4];
    uint32_t contract_count;
    CalypsoEvent events[20];
    uint32_t event_count;
    char station_names[20][32];
} CalypsoReadState;

// UI Elements:
// - Card type (Navigo, MOBIB, etc.)
// - Active contracts (tickets/passes)
// - Validity dates
// - Journey history with station names
```

#### Scene 2: Calypso Journey History
**File**: `scenes/predator_scene_calypso_history_ui.c`
```c
// Scrollable journey history:
// - Entry/Exit/Inspection events
// - Date/Time
// - Station/Stop name (Paris Metro decoder)
// - Contract used
// - Vehicle ID
```

---

### Priority 4: ISO 15693 Implementation (ENTERPRISE)

#### Scene 1: ISO 15693 Scanner
**File**: `scenes/predator_scene_iso15693_scan_ui.c`
```c
typedef struct {
    ISO15693Tag tag;
    bool tag_detected;
    uint8_t block_data[256];
    uint32_t blocks_read;
    bool password_protected;
    uint32_t found_password;
} ISO15693ScanState;

// UI Elements:
// - Tag detection
// - Tag type (Ti Tag-it, ICODE SLI/SLIX, etc.)
// - Memory size
// - Password protection status
// - Block contents viewer
```

#### Scene 2: ISO 15693 Password Attack
**File**: `scenes/predator_scene_iso15693_attack_ui.c`
```c
// Password attack interface:
// - Dictionary attack progress
// - Brute force option
// - Found password display
// - Success rate
```

---

### Priority 5: EM4305 Cloning (PRACTICAL)

#### Scene 1: EM4305 Clone Wizard
**File**: `scenes/predator_scene_em4305_clone_ui.c`
```c
typedef struct {
    uint64_t source_card_data;
    bool source_detected;
    EM4305Config target_config;
    bool target_ready;
    uint8_t clone_progress;
    char status_message[64];
} EM4305CloneState;

// Multi-step wizard:
// Step 1: Scan source card (EM4100/HID/Indala)
// Step 2: Place target EM4305 tag
// Step 3: Configure target
// Step 4: Write data
// Step 5: Verify clone
```

#### Scene 2: EM4305 Password Attack
**File**: `scenes/predator_scene_em4305_attack_ui.c`
```c
// Password recovery:
// - Dictionary attack
// - Brute force with progress
// - Found password display
```

---

### Priority 6: Wiegand/SECURAKEY (NORTH AMERICA)

#### Scene 1: Wiegand Card Reader
**File**: `scenes/predator_scene_wiegand_read_ui.c`
```c
typedef struct {
    WiegandCard card;
    bool card_detected;
    char format_name[32];
    char manufacturer_name[32];
    char bit_string[65];
    uint32_t cards_captured;
} WiegandReadState;

// UI Elements:
// - Card detection
// - Format (26-bit, 35-bit, etc.)
// - Facility code
// - Card number
// - Raw bit display
// - Manufacturer
```

#### Scene 2: Wiegand Emulator
**File**: `scenes/predator_scene_wiegand_emulate_ui.c`
```c
// Card emulation:
// - Input facility code
// - Input card number
// - Select format
// - Emulate continuously
// - Stop emulation
```

#### Scene 3: Wiegand Brute Force
**File**: `scenes/predator_scene_wiegand_bruteforce_ui.c`
```c
// Brute force attack:
// - Fixed facility + range of cards
// - OR range of facilities + fixed card
// - Progress display
// - Success counter
```

---

### Priority 7: Legic (SWISS/ALPINE)

#### Scene 1: Legic Card Reader
**File**: `scenes/predator_scene_legic_read_ui.c`
```c
typedef struct {
    LegicCard card;
    bool card_detected;
    LegicCredential credentials[4];
    uint32_t credential_count;
    char memory_type[32];
    uint16_t segments_found;
} LegicReadState;

// UI Elements:
// - Card type (Prime/Advant)
// - Memory size
// - Segments detected
// - Credentials (ski pass, access, etc.)
// - Validity dates
```

---

### Priority 8: UltraLight C (GLOBAL TRANSIT)

#### Scene 1: UltraLight Reader
**File**: `scenes/predator_scene_ultralight_read_ui.c`
```c
typedef struct {
    UltraLightCard card;
    bool card_detected;
    UltraLightTicket ticket;
    uint8_t memory_dump[924];  // Max NTAG216
    bool has_ticket_data;
    bool password_protected;
} UltraLightReadState;

// UI Elements:
// - Card type detection
// - Memory size
// - Ticket information
// - Balance/trips remaining
// - Validity period
```

#### Scene 2: UltraLight Password Attack
**File**: `scenes/predator_scene_ultralight_attack_ui.c`
```c
// Password recovery:
// - Dictionary attack
// - Brute force (32-bit, feasible)
// - Progress display
```

---

## 🔧 Implementation Steps

### Step 1: Update Main Menu
**File**: `scenes/predator_scene_main_menu_ui.c`

Add new menu items:
```c
submenu_add_item(submenu, "RFID/NFC Attacks", SceneRfidMenu, callback, app);
submenu_add_item(submenu, "Transit Cards", SceneTransitMenu, callback, app);  // NEW
submenu_add_item(submenu, "Access Control", SceneAccessControlMenu, callback, app);  // NEW
```

### Step 2: Register New Scenes
**File**: `predator_scene_config.h`

Add scene IDs:
```c
// Transit Cards
ADD_SCENE(predator, transit_menu, TransitMenu)
ADD_SCENE(predator, felica_read, FelicaRead)
ADD_SCENE(predator, felica_history, FelicaHistory)
ADD_SCENE(predator, calypso_read, CalypsoRead)
ADD_SCENE(predator, calypso_history, CalypsoHistory)
ADD_SCENE(predator, ultralight_read, UltralightRead)
ADD_SCENE(predator, legic_read, LegicRead)

// Access Control
ADD_SCENE(predator, access_control_menu, AccessControlMenu)
ADD_SCENE(predator, wiegand_read, WiegandRead)
ADD_SCENE(predator, wiegand_emulate, WiegandEmulate)
ADD_SCENE(predator, wiegand_bruteforce, WiegandBruteforce)

// RFID Extensions
ADD_SCENE(predator, iso15693_scan, ISO15693Scan)
ADD_SCENE(predator, iso15693_attack, ISO15693Attack)
ADD_SCENE(predator, em4305_clone, EM4305Clone)
ADD_SCENE(predator, em4305_attack, EM4305Attack)
```

### Step 3: Update Application Structure
**File**: `predator_i.h`

Add state variables:
```c
typedef struct {
    // ... existing fields ...
    
    // Phase 2 Protocol States
    FeliCaCard felica_card;
    CalypsoCard calypso_card;
    ISO15693Tag iso15693_tag;
    EM4305Tag em4305_tag;
    WiegandCard wiegand_card;
    LegicCard legic_card;
    UltraLightCard ultralight_card;
    
    // Attack states
    bool attack_in_progress;
    uint32_t attack_progress;
    uint32_t attack_total;
    
} PredatorApp;
```

---

## 📱 UI Design Guidelines

### Card Reader Screens (Standard Template)
```
┌─────────────────────────────┐
│ [CARD TYPE] READER          │
├─────────────────────────────┤
│                             │
│ Status: [Waiting/Detected]  │
│ Type:   [Card Name]         │
│ UID:    [XX XX XX XX XX]    │
│ Memory: [XXX bytes]         │
│                             │
│ ● Place card on reader      │
│                             │
│ [BACK] Press to return      │
└─────────────────────────────┘
```

### Transit Card Display (FeliCa/Calypso)
```
┌─────────────────────────────┐
│ SUICA CARD                  │
├─────────────────────────────┤
│ Balance: ¥2,450             │
│                             │
│ Recent Trips:               │
│ ▼ Shinjuku Sta. -¥165       │
│   → Shibuya Sta.            │
│   10/18 14:23               │
│                             │
│ ▼ Shibuya Sta.  -¥195       │
│   → Tokyo Sta.              │
│   10/18 09:15               │
│                             │
│ [◄] [DUMP] [▼]              │
└─────────────────────────────┘
```

### Attack Progress Screen
```
┌─────────────────────────────┐
│ PASSWORD ATTACK             │
├─────────────────────────────┤
│                             │
│ Progress: 45%               │
│ [██████████░░░░░░░░░░░]     │
│                             │
│ Tried: 45,230 / 100,000     │
│ Speed: 1,250 keys/sec       │
│ ETA:   00:44 remaining      │
│                             │
│ Status: Testing...          │
│                             │
│ [STOP] Press to cancel      │
└─────────────────────────────┘
```

---

## 🔌 Hardware Integration

### NFC/RFID Requirements
- **13.56 MHz NFC**: FeliCa, Calypso, ISO 15693, UltraLight C, Legic
- **125 kHz LF RFID**: EM4305, Wiegand (some variants)
- **GPIO Bit-banging**: Wiegand protocol (D0/D1 lines)

### Flipper Zero NFC Module
All Phase 2 protocols work with standard Flipper Zero NFC hardware:
- FeliCa: ISO 18092 (NFC-F) support
- Calypso: ISO 14443 Type B
- ISO 15693: Native support
- UltraLight: ISO 14443 Type A
- Legic: 13.56 MHz (requires Legic-specific timing)

---

## 📝 Implementation Priority Order

### Week 1: Transit Cards (Highest Value)
1. FeliCa reader scene ⭐⭐⭐⭐⭐
2. Calypso reader scene ⭐⭐⭐⭐⭐
3. Transit menu integration

### Week 2: Cloning & Enterprise
4. EM4305 clone wizard ⭐⭐⭐⭐
5. ISO 15693 scanner ⭐⭐⭐⭐
6. RFID menu expansion

### Week 3: Access Control
7. Wiegand reader/emulator ⭐⭐⭐⭐
8. Access Control menu
9. Legic reader scene ⭐⭐⭐

### Week 4: Advanced Features
10. UltraLight reader ⭐⭐⭐
11. Attack scenes (password/brute force)
12. Polish and testing

---

## 🎯 Quick Start: Minimal Implementation

For **immediate functionality**, implement these 3 scenes first:

1. **Transit Cards Menu** (5 minutes)
   - Simple submenu with 4 items
   
2. **FeliCa Reader** (2 hours)
   - Card detection + balance display
   - Most impactful feature for Asia-Pacific
   
3. **EM4305 Clone Wizard** (2 hours)
   - Practical cloning capability
   - High pentester value

**Total**: ~4 hours for basic Phase 2 functionality

---

## 📦 Code Generation Templates

### Template: Basic Reader Scene
```c
#include "../predator_i.h"

typedef struct {
    [CardType]Card card;
    bool card_detected;
    uint32_t last_update;
} [Protocol]ReadState;

static [Protocol]ReadState state;

void predator_scene_[protocol]_read_on_enter(void* context) {
    PredatorApp* app = context;
    memset(&state, 0, sizeof(state));
    
    // Initialize view
    view_dispatcher_switch_to_view(app->view_dispatcher, PredatorViewWidget);
    
    // Start detection
    [protocol]_detect_card(app, &state.card);
}

bool predator_scene_[protocol]_read_on_event(void* context, SceneManagerEvent event) {
    PredatorApp* app = context;
    bool consumed = false;
    
    if(event.type == SceneManagerEventTypeCustom) {
        // Handle custom events
        consumed = true;
    } else if(event.type == SceneManagerEventTypeBack) {
        scene_manager_previous_scene(app->scene_manager);
        consumed = true;
    }
    
    return consumed;
}

void predator_scene_[protocol]_read_on_exit(void* context) {
    // Cleanup
}
```

---

## ✅ Testing Checklist

### Phase 2A Testing
- [ ] ISO 15693 tag detection
- [ ] EM4305 read/write/clone
- [ ] FeliCa Suica card read (if available)
- [ ] Calypso Navigo simulation

### Phase 2B Testing
- [ ] Legic card detection
- [ ] Wiegand 26-bit encode/decode
- [ ] UltraLight C authentication
- [ ] Password attacks functional

### UI Testing
- [ ] All menus navigate correctly
- [ ] Back button works in all scenes
- [ ] No memory leaks
- [ ] Proper error handling
- [ ] Real-time updates smooth

---

## 🚀 Next Actions

1. ✅ **Choose implementation priority** (suggested: FeliCa first)
2. ✅ **Create basic scene template**
3. ✅ **Implement C code for crypto functions**
4. ✅ **Test on real cards** (if available)
5. ✅ **Polish UI**

---

**Status**: Ready for implementation  
**Estimated Total Time**: 2-4 weeks for full Phase 2 UI integration  
**Quick Start Time**: 4 hours for basic functionality  

---

*Document created: October 18, 2025 @ 4:05 AM UTC+2*  
*All 7 Phase 2 algorithms ready for menu integration*
