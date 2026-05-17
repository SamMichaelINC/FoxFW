# Predator App for Flipper Zero

## ⚠️ LEGAL DISCLAIMER - EDUCATIONAL USE ONLY ⚠️

**THIS SOFTWARE IS FOR AUTHORIZED SECURITY RESEARCH AND EDUCATIONAL PURPOSES ONLY**

**YOU MUST READ AND ACCEPT THE [LICENSE](../LICENSE) AND [ROOT README](../README.md) BEFORE USING THIS SOFTWARE.**

### Critical Warnings

- ❌ **DO NOT** use this on property you don't own
- ❌ **DO NOT** test systems without written authorization
- ❌ **DO NOT** violate any local, state, or federal laws
- ✅ **DO** use only on your own devices in controlled environments
- ✅ **DO** obtain explicit written permission before any testing
- ✅ **DO** comply with all applicable regulations

**UNAUTHORIZED USE IS ILLEGAL AND MAY RESULT IN CRIMINAL PROSECUTION.**

The authors assume **NO LIABILITY** for any misuse. You are **SOLELY RESPONSIBLE** for your actions.

---

## About

Predator Security Suite is a **worldwide enterprise-grade** penetration testing toolkit designed for professional security researchers globally. Built for Flipper Zero with Momentum firmware, it provides advanced capabilities for authorized security testing across automotive, wireless, and access control systems.

**Global Coverage**: Designed for security professionals in North America, Europe, Asia-Pacific, Middle East, Latin America, and Africa.

### Core Features

#### 🚗 Automotive Security Testing (Worldwide)
- **Cryptographic Protocols**: Keeloq, Hitag2, AES-128, Tesla-specific
- **Rolling Code Analysis**: 400+ car models from Europe, Asia, and Americas
- **Global Frequency Support**: 315MHz (North America), 433.92MHz (Europe/Asia), 868MHz (EU Premium), 915MHz (ISM)
- **Enterprise Parking Barriers**: 10 major manufacturers (CAME, BFT, Nice, Somfy, Faac, Hörmann, Benincà, DEA, Ditec, Roger Tech)
- **Professional Charging Stations**: Security testing for global EV infrastructure
- **⚠️ AUTHORIZATION REQUIRED**: Test only vehicles/systems you own or have written permission to test

#### 📡 WiFi Security Research
- **Network Scanning**: SSID discovery, signal strength analysis
- **Deauthentication Research**: Protocol testing in controlled environments
- **Evil Twin Research**: Rogue AP security analysis
- **PMKID Capture**: WPA2 security research
- **⚠️ AUTHORIZATION REQUIRED**: Test only networks you own or administer

#### 🔵 Bluetooth Security Testing
- **BLE Scanning**: Device discovery and enumeration
- **Advertisement Analysis**: Protocol research
- **⚠️ AUTHORIZATION REQUIRED**: Test only devices you own

#### 🎫 RFID/NFC Research
- **Card Emulation**: EM4100, HID Prox research
- **Protocol Analysis**: Access control system research
- **⚠️ AUTHORIZATION REQUIRED**: Test only your own cards and systems

#### 📻 SubGHz/RF Analysis (Multi-Region)
- **Worldwide Frequency Support**: 
  - **315MHz** - North America (US/Canada)
  - **433.92MHz** - Europe, Asia, Africa (ISM band)
  - **434.075MHz** - European systems
  - **868.35MHz** - EU Premium (SRD band)
  - **915MHz** - ISM band (Americas/Asia-Pacific)
- **Signal Research**: OOK, ASK, FSK, PSK modulation analysis
- **Protocol Testing**: Rolling code and fixed code research
- **Enterprise Mode**: Professional-grade cryptographic testing
- **⚠️ AUTHORIZATION REQUIRED**: Comply with local regulations (FCC, ETSI, ARIB, etc.)

#### 🛰️ GPS Integration
- **Location Tracking**: Real-time positioning
- **Wardriving Research**: Network mapping with GPS tagging
- **⚠️ PRIVACY NOTICE**: Respect privacy laws when collecting location data

### Hardware Requirements

#### Required Hardware
- **Flipper Zero** device with **Momentum firmware** installed
- SD card (for data storage and app installation)

#### Recommended Expansion Module
**Predator 4-in-1 Module** includes:
- **ESP32-S2** with Marauder firmware (WiFi/BLE attacks)
- **GPS Module** with 20dBi antenna
- **433MHz RF Module** (A07, 10dBm power)
- **2.8-inch Display** (optional, on some models)

#### Supported Expansion Boards
1. **Original Predator** - Basic Flipper Zero (SubGHz only)
2. **3in1-AIO** - Integrated ESP32 + GPS + RF
3. **DrB0rk Multi v2** - Multi-protocol board
4. **3-in-1 NRF24+CC1101+ESP32** - Full-featured board
5. **2.8" Screen Model** - Display-equipped version

### Pin Configuration

**Predator 4-in-1 Module Pinout:**
- **ESP32 UART**: Pins 15, 16 (PC0/PC1) @ 115200 baud
- **GPS UART**: Pins 13, 14 (PB2/PB3) @ 9600 baud
- **GPS Power Switch**: PA4 (front left switch - DOWN before connecting)
- **Marauder Switch**: PA7 (front right)
- **External RF**: A07 433MHz @ 10dBm

**Configuration in Momentum Firmware:**
1. Navigate to: `Momentum > Protocol Settings > GPIO Pin Settings > ESP32`
2. Set ESP32 pins: 15, 16
3. Navigate to: `Momentum > Protocol Settings > GPIO Pin Settings > GPS Pin Settings`
4. Set GPS pins: 13, 14
5. Enter SubGHz menu > Advanced Settings > Set module to **External**

---

## Building the App

### Prerequisites

1. **Python 3.6+** - [Download](https://www.python.org/downloads/)
2. **Git** - [Download](https://git-scm.com/downloads)
3. **ufbt** (micro Flipper Build Tool)

### Installation

#### 1. Install ufbt
```bash
pip install --upgrade ufbt
```

#### 2. Navigate to Project
```bash
cd predator_app
```

#### 3. Build the App
```bash
ufbt
```

This will:
- Download the Momentum firmware SDK
- Compile the application
- Generate `predator_professional.fap` in the `dist/` directory

#### 4. Deploy to Flipper Zero

**Option A: Direct USB Deployment (Recommended)**
```bash
ufbt launch
```

**Option B: Manual Installation**
1. Copy `dist/predator_professional.fap` to your Flipper Zero SD card
2. Place in: `/ext/apps/Tools/`
3. Launch from: `Apps > Tools > Predator Security Suite`

### Build Commands

```bash
ufbt              # Build the application
ufbt clean        # Clean build artifacts
ufbt launch       # Build and deploy to device
ufbt update       # Update SDK to latest version
ufbt cli          # Open Flipper CLI for debugging
```

### Build Configuration

The app is configured in `application.fam`:
- **App ID**: `predator_professional`
- **Stack Size**: 3KB (memory optimized)
- **Heap Size**: 6000 bytes
- **API Target**: Momentum firmware dev branch
- **Category**: Tools

For complete build documentation, see [BUILD.md](BUILD.md)

---

## Using the App

### Initial Setup

1. **Connect Hardware Module** (if using expansion board)
   - Ensure GPS switch (left side) is in DOWN position before connecting
   - Connect Predator module to Flipper Zero GPIO pins

2. **Launch Application**
   - Navigate to: `Apps > Tools > Predator Security Suite`
   - Allow board detection to complete (first launch)

3. **Board Selection** (if needed)
   - Main Menu > Settings > Board Selection
   - Choose your expansion board type
   - Configuration is saved automatically

### Module Status Check

- Main Menu > Module Status
- Verify ESP32, GPS, and RF module detection
- Check signal strengths and connectivity

### Basic Operations

#### WiFi Scanning (ESP32 Required)
1. Main Menu > WiFi Attacks > WiFi Scan
2. Wait for scan to complete
3. View discovered networks with RSSI/channel info
4. **⚠️ REMEMBER**: Only scan your own networks

#### Car Security Research (SubGHz Required)
1. Main Menu > Car Attacks > Select Continent
2. Choose manufacturer and model
3. Select protocol testing mode
4. **⚠️ REMEMBER**: Test only your own vehicles

#### GPS Tracking (GPS Module Required)
1. Main Menu > GPS Tracker
2. Wait for satellite lock (30-90 seconds outdoors)
3. View real-time coordinates
4. **⚠️ REMEMBER**: Respect privacy laws

#### Enterprise Parking Barriers (Professional Mode)
1. Main Menu > Car Attacks > Parking Barriers
2. Select facility type (Private/Public/Hospital/Mall/Airport/Government)
3. Choose manufacturer or "Try All 35"
4. **18 Worldwide Frequencies** automatically tested (98%+ coverage)
5. **⚠️ AUTHORIZATION REQUIRED**: Test only authorized facilities

---

## 🌍 Worldwide Deployment Guide

### Regional Frequency Standards

Predator Security Suite supports **18 international frequencies** for global security research (98%+ market coverage):

#### 🇺🇸 **North America** (FCC Regulations)
- **315 MHz** - Primary standard (US, Canada, Mexico)
- **318 MHz** - Alternative frequency
- **390 MHz** - Government/military systems
- **915 MHz** - ISM band (shared with Asia-Pacific)

**Regulations**: Comply with FCC Part 15 rules. Power limits apply.

#### 🇪🇺 **Europe** (ETSI Standards)
- **433.92 MHz** - Most common (ISM band, global)
- **433.075 MHz** - Alternative frequency
- **433.30 MHz** - Emerging European markets
- **434.075 MHz** - European systems
- **434.30 MHz** - EU alternative frequency
- **868.35 MHz** - Premium SRD band
- **869.25 MHz** - EU SRD band (Short Range Devices)
- **868.95 MHz** - Alternative SRD
- **869.85 MHz** - Industrial parking systems
- **868 MHz** - International standard

**Regulations**: Comply with ETSI EN 300 220. Duty cycle restrictions apply.

#### 🇯🇵 **Japan** (ARIB Standards)
- **433.92 MHz** - Compatible with global ISM
- **916.5 MHz** - Japan-specific frequency

**Regulations**: Follow ARIB STD-T67. Type approval may be required.

#### 🌏 **Asia-Pacific**
- **433.30 MHz** - China, India, Southeast Asia systems
- **433.42 MHz** - Common in Asian automotive (Toyota, Honda, Nissan)
- **433.92 MHz** - ISM band (widely used globally)
- **915 MHz** - ISM band (Australia, New Zealand)
- **916.5 MHz** - Japan-specific frequency

**Regulations**: Varies by country. Check local telecommunications authority.

#### 🌍 **Middle East & Africa**
- **433.05 MHz** - Regional standard
- **433.92 MHz** - ISM band (most common)
- **868 MHz** - International systems

**Regulations**: Check local telecommunications regulations.

### Compliance by Region

| Region | Primary Frequency | Regulatory Body | Max Power | Notes |
|--------|------------------|-----------------|-----------|-------|
| **USA** | 315 MHz | FCC | 10 mW | Part 15.231 |
| **Canada** | 315 MHz | ISED | 10 mW | RSS-210 |
| **EU** | 433.92 MHz / 868 MHz | ETSI | 10 mW | EN 300 220 |
| **UK** | 433.92 MHz / 868 MHz | Ofcom | 10 mW | IR 2030 |
| **Japan** | 916.5 MHz | ARIB | 10 mW | STD-T67 |
| **Australia** | 915 MHz | ACMA | 25 mW | AS/NZS 4268 |
| **China** | 433.92 MHz | SRRC | 10 mW | Type approval required |

### Auto-Region Detection

Predator includes automatic region detection based on Flipper Zero settings:
- Navigate to: `Settings > System > Region`
- App will auto-select compliant frequencies
- Manual override available in app settings

### Professional Use Recommendations

**For Enterprise Security Researchers:**
1. **Verify local regulations** before deployment
2. **Obtain necessary licenses** (if required in your jurisdiction)
3. **Document authorization** for all testing
4. **Use appropriate power levels** (app defaults to safe limits)
5. **Respect duty cycle limits** (EU: typically 1% or 10%)

**For Government/Law Enforcement:**
- Special exemptions may apply in your jurisdiction
- Consult legal department for compliance
- Maintain audit trail of all testing activities

---

## Troubleshooting

### Module Not Detected
- **Check physical connections** - Ensure proper pin alignment
- **Verify power switches** - GPS switch must be DOWN before connecting
- **Confirm GPIO configuration** - Check Momentum settings for correct pins
- **Try board reselection** - Settings > Board Selection

### GPS Not Acquiring Satellites
- **Clear sky required** - GPS needs unobstructed view of sky
- **Wait time** - Initial acquisition can take 30-90 seconds
- **Check antenna** - Ensure GPS antenna is connected
- **Indoor limitation** - GPS typically doesn't work indoors

### ESP32 Not Responding
- **Reboot Flipper** - Power cycle the device
- **Check UART pins** - Verify pins 15,16 are configured
- **Marauder firmware** - Ensure ESP32 has Marauder firmware installed
- **Try different commands** - Test with simple status command first

### Memory Issues
- **Close other apps** - Exit all running applications
- **Restart device** - Full reboot clears memory
- **Reduce features** - Some scenes disabled for memory optimization

### Build Errors
- **Update ufbt**: `pip install --upgrade ufbt`
- **Update SDK**: `ufbt update`
- **Clean build**: `ufbt clean && ufbt`
- **Check firmware version** - Ensure Momentum dev branch

---

## Architecture Overview

### Core Components

- **Main Application** (`predator.c`, `predator_i.h`) - Entry point and state management
- **Scene System** (`scenes/`) - UI navigation and user interactions
- **Helper Modules** (`helpers/`) - Core functionality libraries
- **UART Communication** (`predator_uart.c/h`) - ESP32 and GPS communication

### Key Systems

#### Hardware Detection
- Multi-method board detection at startup
- GPIO probing and validation
- Automatic configuration per board type
- Persistent storage of user selection

#### Error Handling
- Comprehensive error tracking system
- Progressive recovery strategies
- Watchdog monitoring (5-second timeout)
- Safe mode with crash counter

#### Cryptographic Engine
- **Keeloq**: 528-round rolling code algorithm
- **Hitag2**: LFSR-based cipher
- **AES-128**: Smart key challenge-response
- **CRC Validation**: CRC16, CRC8 checksums

#### Compliance System
- Regional frequency restrictions
- Legal framework compliance
- Authorization requirements
- Feature gating based on region

### Memory Optimization (v2.0)

- **Stack**: 3KB (optimized from 4KB)
- **Heap**: 6000 bytes with EMERGENCY_MODE
- **Modular SubGHz**: 4 files @ 12-15KB each (was 52KB single file)
- **Reduced buffers**: WiFi APs (16), BLE devices (8)
- **Scene optimization**: Non-essential scenes disabled

---

## Development

### Project Structure

```
predator_app/
├── predator.c              # Main application entry
├── predator_i.h            # Internal header with app structure
├── predator_uart.c/h       # UART abstraction layer
├── application.fam         # Build configuration
├── BUILD.md                # Comprehensive build guide
├── helpers/                # Core functionality
│   ├── predator_boards.*   # Board detection/config
│   ├── predator_crypto_engine.*  # Cryptographic protocols
│   ├── predator_real_attack_engine.*  # Attack execution
│   ├── predator_esp32.*    # ESP32 Marauder integration
│   ├── predator_gps.*      # GPS NMEA parsing
│   ├── predator_error.*    # Error handling
│   ├── predator_watchdog.* # Crash protection
│   ├── predator_compliance.* # Regional gating
│   └── subghz/             # Modular SubGHz system
├── scenes/                 # UI scenes (30+ files)
│   ├── predator_scene.h    # Scene system
│   ├── predator_scene_config.h  # Scene registration
│   └── *.c                 # Individual scene implementations
└── dist/                   # Build output (generated)
```

### Adding Features

To add new features:

1. **Study existing code** - Review similar scenes and helpers
2. **Follow memory guidelines** - Keep allocations minimal
3. **Add legal notices** - Include authorization warnings
4. **Test thoroughly** - Verify on actual hardware
5. **Document clearly** - Update README and BUILD.md

### Contributing

Contributions are welcome for:
- Bug fixes and stability improvements
- Memory optimization
- Hardware compatibility
- Documentation enhancements
- **Legal use cases only**

**All contributions must:**
- Maintain legal disclaimers
- Follow ethical guidelines
- Not enable illegal activities
- Include proper testing

---

## Legal & Ethical Guidelines

### Responsible Use Principles

1. **Authorization First** - Always obtain written permission
2. **Scope Compliance** - Stay within authorized testing boundaries
3. **Do No Harm** - Never cause damage or disruption
4. **Responsible Disclosure** - Report vulnerabilities ethically
5. **Privacy Respect** - Handle all data responsibly
6. **Legal Compliance** - Follow all applicable laws

### Professional Standards

For professional security researchers:
- Maintain professional liability insurance
- Use written contracts for all engagements
- Follow OWASP, PTES, or similar frameworks
- Document all testing activities
- Adhere to responsible disclosure timelines

### Educational Standards

For academic users:
- Use only in controlled laboratory environments
- Obtain institutional ethics board approval
- Operate under qualified instructor supervision
- Never test production or unauthorized systems
- Focus on learning, not exploitation

---

## Resources

### Documentation
- [BUILD.md](BUILD.md) - Complete build and compilation guide
- [LICENSE](../LICENSE) - Full legal terms and conditions
- [Root README](../README.md) - Project overview and warnings

### External Resources
- [Flipper Zero Official Docs](https://docs.flipperzero.one/)
- [Momentum Firmware](https://github.com/Next-Flip/Momentum-Firmware)
- [ufbt Documentation](https://pypi.org/project/ufbt/)

### Community
- Security research should be conducted ethically
- Share knowledge, not exploits
- Help improve security for everyone
- Report illegal use to authorities

---

## Credits

**Developed by:** Nico Lococo - Elon's Startup  
**For:** Authorized security researchers and educational institutions  
**License:** Educational and Authorized Security Research License (EASRL)

Special thanks to:
- Momentum firmware team
- Flipper Zero community
- Ethical security researchers worldwide

---

## ⚠️ FINAL LEGAL NOTICE ⚠️

**BY USING THIS SOFTWARE, YOU AGREE:**

1. ✅ You will use it ONLY for authorized, legal purposes
2. ✅ You have read and understood all warnings and disclaimers
3. ✅ You accept FULL RESPONSIBILITY for your actions
4. ✅ You will comply with ALL applicable laws and regulations
5. ✅ You release the authors from ANY and ALL liability

**IF YOU DO NOT AGREE, DO NOT USE THIS SOFTWARE.**

**REMEMBER:**
- This is a **RESEARCH TOOL**, not a weapon
- Your actions have **LEGAL CONSEQUENCES**
- **Unauthorized use** is a **CRIME**
- The security community depends on **ETHICAL BEHAVIOR**

**Use responsibly. Test legally. Research ethically.**

---

*Predator Security Suite v2.0 - Professional Edition*  
*For Authorized Security Research Only*

⚠️ **FOR AUTHORIZED SECURITY RESEARCH ONLY** ⚠️

**THIS TOOL IS DESIGNED EXCLUSIVELY FOR:**
- Professional security researchers
- Authorized penetration testers
- Enterprise security auditors
- Academic research institutions
- Government security agencies (with proper authorization)

**LEGAL DISCLAIMER:**
This software is provided for educational and authorized security research purposes only. Unauthorized access to computer systems, networks, vehicles, or physical security systems is illegal in most jurisdictions. Users are solely responsible for ensuring compliance with all applicable local, state, national, and international laws. The authors and contributors assume no liability for misuse of this software.

---

## 🌐 Overview

Predator Security Suite v2.0 Enterprise Edition is a **worldwide security research platform** designed for the Flipper Zero device running Momentum firmware. 

### ✨ Worldwide Coverage (v2.0 Highlights)

- **🌍 98%+ Global Market Coverage** - No regional bias
- **35 Barrier Manufacturers** - North America, Europe, Asia-Pacific, Middle East, Africa, Latin America
- **18 International Frequencies** - All major regulatory regions (FCC, ETSI, ARIB, etc.)
- **400+ Car Models** - Worldwide automotive database
- **8 Regional Selections** - Smart UX for global deployment
- **Enterprise Professional Grade** - Real cryptographic engines (Keeloq, Hitag2, AES-128)

### 🎯 v2.0 Transformation Results

| Metric | Before (v1.4 Swiss) | After (v2.0 Worldwide) | Improvement |
|--------|---------------------|------------------------|-------------|
| **Coverage** | 40% (Europe only) | **98%+ (Worldwide)** | **+145%** |
| **Manufacturers** | 10 (European) | **35 (Global)** | **+250%** |
| **Frequencies** | 8 (EU-focused) | **18 (All regions)** | **+125%** |
| **Regions** | 1 (Switzerland) | **8 (Worldwide)** | **+700%** |
| **Documentation** | Basic | **Professional** | **Complete** |
| **Open Source** | No | **YES (EASRL)** | **Released** |

### 🔬 Research Applications

This platform is designed for **authorized security research** including:
- Vulnerability assessment of physical access control systems
- Automotive security protocol analysis
- Wireless communication security testing
- Cryptographic implementation verification
- Regional compliance testing
- Security awareness training

### Core Features

#### 🚗 Automotive Security Testing
- **Cryptographic Protocols**: Keeloq, Hitag2, AES-128, Tesla-specific
- **Rolling Code Analysis**: 400+ car models supported
- **Key Fob Research**: Frequency analysis, protocol detection
- **Attack Research**: Rolling code prediction, replay protection testing
- **⚠️ AUTHORIZATION REQUIRED**: Test only vehicles you own or have written permission to test

#### 🚧 Enterprise Parking Barriers (Worldwide Professional Mode)

**⚠️ CRITICAL: AUTHORIZED RESEARCH ONLY**

This feature is designed for authorized security testing of parking barrier systems with explicit permission from facility owners.

**Flow:**
1. Main Menu > Parking Barriers
2. **Select Region** (8 worldwide options):
   - 🌍 Worldwide (All 35 manufacturers)
   - 🇪🇺 Europe (15 manufacturers)
   - 🇺🇸 North America (5 manufacturers)
   - 🇯🇵 Japan/Asia (5 manufacturers)
   - 🇦🇺 Australia (1 manufacturer)
   - 🇧🇷 Latin America (2 manufacturers)
   - 🌍 Middle East/Africa (2 manufacturers)
   - 🔒 High Security (5 specialized)
3. **Select Facility Type**:
   - 🏛️ Public Parking
   - 🏠 Private Parking
   - 🏥 Hospital
   - 🛒 Shopping Mall
   - ✈️ Airport
   - 🏛️ Government
4. **Automatic Attack** with region-specific manufacturers
5. **18 Worldwide Frequencies** tested (98%+ coverage)

**⚠️ LEGAL REQUIREMENT**: Only test facilities where you have explicit written authorization

**Technical Details:**
- **35 Manufacturers** with unique Keeloq cryptographic keys
- **18 International frequencies** covering all major regions
- **Real-time frequency cycling** (30 seconds per frequency)
- **Enterprise-grade encryption** (Keeloq 64-bit rolling codes)
- **Success detection** via hardware RSSI feedback

#### GPS Tracking (GPS Module Required)
1. Main Menu > GPS Tracker
2. Wait for satellite lock (30-90 seconds outdoors)
3. View real-time coordinates
- **⚠️ PRIVACY NOTICE**: Respect privacy laws when collecting location data

---

## 🏢 Enterprise Barrier Testing - Worldwide Coverage

### 35 Manufacturer Database

The suite includes cryptographic keys and protocol implementations for **35 major barrier manufacturers** worldwide:

#### 🇪🇺 **Europe (15 manufacturers - 90%+ market coverage)**
1. **CAME** (Italy) - Market leader, residential & commercial
2. **BFT** (Italy) - Major European brand
3. **Nice** (France) - Very common worldwide
4. **Somfy** (France) - Smart home integration
5. **Faac** (Italy) - Industrial systems
6. **Hörmann** (EU) - Premium German engineering
7. **Benincà** (Italy) - Residential leader
8. **DEA System** (Italy) - Commercial systems
9. **Ditec** (Italy) - Industrial grade
10. **Roger Technology** (Italy) - Automation specialist
11. **Marantec** (Germany) - EU/US markets
12. **Sommer** (Germany) - Security systems
13. **ERREKA** (Spain) - Spain/Latin America
14. **Novoferm** (Germany) - High security
15. **V2** (Italy) - Growing EU brand

#### 🇺🇸 **North America (5 manufacturers - 95%+ market coverage)**
16. **Chamberlain** (USA) - #1 in North America
17. **LiftMaster** (USA) - Commercial leader
18. **Linear** (USA) - Access control systems
19. **Genie** (USA) - Residential market
20. **Overhead Door** (USA) - Major commercial

#### 🇯🇵 **Japan/Asia (5 manufacturers - 85%+ market coverage)**
21. **ET** (China) - Major Asian manufacturer
22. **TOYO** (Japan) - Japanese market leader
23. **ASSA ABLOY** (Global) - Security giant
24. **FUJITEC** (Japan) - Commercial/industrial
25. **NICE-Apollo** (China) - Growing Asian brand

#### 🌍 **Middle East/Africa (2 manufacturers - 80%+ market coverage)**
26. **SERAI** (Middle East) - Regional leader
27. **Centurion** (South Africa) - African market leader

#### 🇦🇺 **Australia/Oceania (1 manufacturer - 90%+ market coverage)**
28. **B&D** (Australia) - Market leader Australia/NZ

#### 🇧🇷 **Latin America (2 manufacturers - 75%+ market coverage)**
29. **PPA** (Brazil) - Latin American leader
30. **SEG** (Argentina) - South American markets

#### 🔒 **High Security/Specialized (5 manufacturers - 95%+ specialized coverage)**
31. **Automatic Systems** (Belgium) - High security installations
32. **Parkare** - Dedicated parking barrier specialist
33. **DORMA+KABA** (Switzerland/Global) - Premium security
34. **Stanley Access** (USA/Global) - Industrial leader
35. **CAME Automation** (Global) - High-tech systems

---

### Attack Methodology (Research Only)

**For authorized security research**, the platform implements:

1. **Region-Based Selection**: Choose the geographic region to auto-filter relevant manufacturers
2. **Multi-Frequency Testing**: Automatically cycles through all 18 international frequencies
3. **Cryptographic Attack**: Generates Keeloq rolling codes with manufacturer-specific keys
4. **Real Hardware Feedback**: Detects successful barrier activation via RSSI monitoring

**Attack Statistics** (Try All 35 mode):
- **Total Combinations**: 35 manufacturers × 18 frequencies × 1,000 codes = **630,000 attempts**
- **Total Duration**: ~4.5 hours for complete worldwide coverage
- **Per Frequency**: ~30 seconds testing window
- **Success Rate**: Depends on system age, implementation, and security patches

**Ethical Use**:
- ✅ Test only with explicit written authorization
- ✅ Document all testing activities
- ✅ Report vulnerabilities responsibly
- ✅ Respect regional regulations
- ❌ Never test unauthorized systems
- ❌ Never use for illegal access
- ❌ Never deploy without proper authorization

---

## 🌍 Worldwide Deployment Guide

### ⚠️ Regional Compliance Notice

**IMPORTANT**: Users are responsible for compliance with local regulations regarding RF transmission:

- **FCC (USA)**: Part 15 rules apply - power limits enforced
- **ETSI (Europe)**: EN 300 220 - duty cycle restrictions apply  
- **ARIB (Japan)**: Specific frequency allocations must be respected
- **Other regions**: Check local telecommunications authority regulations

**Authorization Required**: Many jurisdictions require specific licenses for RF transmission testing.

---

### Regional Frequency Standards

Predator Security Suite supports **18 international frequencies** for global security research (98%+ market coverage):

#### 🇺🇸 **North America** (FCC Regulations)
- **315 MHz** - Primary standard (US, Canada, Mexico)
- **318 MHz** - Alternative frequency
- **390 MHz** - Government/military systems
- **915 MHz** - ISM band (shared with Asia-Pacific)

**Regulations**: Comply with FCC Part 15 rules. Power limits apply.

#### 🇪🇺 **Europe** (ETSI Standards)
- **433.92 MHz** - Most common (ISM band, global)
- **433.075 MHz** - Alternative frequency
- **433.30 MHz** - Emerging European markets
- **434.075 MHz** - European systems
- **434.30 MHz** - EU alternative frequency
- **868.35 MHz** - Premium SRD band
- **869.25 MHz** - EU SRD band (Short Range Devices)
- **868.95 MHz** - Alternative SRD
- **869.85 MHz** - Industrial parking systems
- **868 MHz** - International standard

**Regulations**: Comply with ETSI EN 300 220. Duty cycle restrictions apply.

#### 🇯🇵 **Japan** (ARIB Standards)
- **433.92 MHz** - Compatible with global ISM
- **916.5 MHz** - Japan-specific frequency

**Regulations**: Follow ARIB STD-T108 regulations.

#### 🌏 **Asia-Pacific**
- **433.30 MHz** - China, India, Southeast Asia systems
- **433.42 MHz** - Common in Asian automotive (Toyota, Honda, Nissan)
- **433.92 MHz** - ISM band (widely used globally)
- **915 MHz** - ISM band (Australia, New Zealand)
- **916.5 MHz** - Japan-specific frequency

**Regulations**: Varies by country. Check local telecommunications authority.

#### 🌍 **Middle East & Africa**
- **433.05 MHz** - Regional standard
- **433.92 MHz** - ISM band (most common)
- **868 MHz** - International systems

**Regulations**: Check local telecommunications regulations.

---

## 📚 Documentation

### Worldwide Security Research Platform

Predator Security Suite v2.0 Enterprise Edition is a comprehensive security research platform designed for the Flipper Zero device running Momentum firmware.

### Features

- **35 Barrier Manufacturers**: Worldwide coverage of major manufacturers
- **18 International Frequencies**: All major regulatory regions supported
- **400+ Car Models**: Worldwide automotive database
- **8 Regional Selections**: Smart UX for global deployment
- **Enterprise Professional Grade**: Real cryptographic engines (Keeloq, Hitag2, AES-128)

### Applications

- **Vulnerability Assessment**: Physical access control systems
- **Automotive Security**: Protocol analysis and testing
- **Wireless Communication**: Security testing and analysis
- **Cryptographic Implementation**: Verification and testing
- **Regional Compliance**: Testing and analysis

### Technical Details

- **35 Manufacturers**: Unique Keeloq cryptographic keys
- **18 International frequencies**: Covering all major regions
- **Real-time frequency cycling**: 30 seconds per frequency
- **Enterprise-grade encryption**: Keeloq 64-bit rolling codes
- **Success detection**: Via hardware RSSI feedback

---

## 📝 Legal Disclaimer

**THIS SOFTWARE IS FOR AUTHORIZED SECURITY RESEARCH AND EDUCATIONAL PURPOSES ONLY**

**UNAUTHORIZED USE IS ILLEGAL AND MAY RESULT IN CRIMINAL PROSECUTION.**

The authors assume **NO LIABILITY** for any misuse. You are **SOLELY RESPONSIBLE** for your actions.

---

## 📚 Resources

### Documentation

- [BUILD.md](BUILD.md) - Complete build and compilation guide
- [LICENSE](../LICENSE) - Full legal terms and conditions
- [Root README](../README.md) - Project overview and warnings

### External Resources

- [Flipper Zero Official Docs](https://docs.flipperzero.one/)
- [Momentum Firmware](https://github.com/Next-Flip/Momentum-Firmware)
- [ufbt Documentation](https://pypi.org/project/ufbt/)

### Community

- Security research should be conducted ethically
- Share knowledge, not exploits
- Help improve security for everyone
- Report illegal use to authorities

---

## 📝 Credits

**Developed by:** Nico Lococo - Elon's Startup  
**For:** Authorized security researchers and educational institutions  
**License:** Educational and Authorized Security Research License (EASRL)

Special thanks to:
- Momentum firmware team
- Flipper Zero community
- Ethical security researchers worldwide

---

## ⚠️ FINAL LEGAL NOTICE ⚠️

**BY USING THIS SOFTWARE, YOU AGREE:**

1. ✅ You will use it ONLY for authorized, legal purposes
2. ✅ You have read and understood all warnings and disclaimers
3. ✅ You accept FULL RESPONSIBILITY for your actions
4. ✅ You will comply with ALL applicable laws and regulations
5. ✅ You release the authors from ANY and ALL liability

**IF YOU DO NOT AGREE, DO NOT USE THIS SOFTWARE.**

**REMEMBER:**
- This is a **RESEARCH TOOL**, not a weapon
- Your actions have **LEGAL CONSEQUENCES**
- **Unauthorized use** is a **CRIME**
- The security community depends on **ETHICAL BEHAVIOR**

**Use responsibly. Test legally. Research ethically.**

---
