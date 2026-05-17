# Building and Compiling Predator App for Flipper Zero

This document provides comprehensive instructions for building, compiling, and deploying the Predator app for Flipper Zero with Momentum firmware.

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Understanding the Build System](#understanding-the-build-system)
3. [Quick Start Build Guide](#quick-start-build-guide)
4. [Detailed Build Process](#detailed-build-process)
5. [Build Configuration](#build-configuration)
6. [Deployment Methods](#deployment-methods)
7. [Advanced Build Options](#advanced-build-options)
8. [Troubleshooting](#troubleshooting)
9. [Development Workflow](#development-workflow)

---

## Prerequisites

### Required Software

1. **Python 3.6 or higher**
   - Download from: https://www.python.org/downloads/
   - Verify installation: `python --version`

2. **Git**
   - Download from: https://git-scm.com/downloads
   - Verify installation: `git --version`

3. **ufbt (micro Flipper Build Tool)**
   - Official Flipper Zero build tool for external applications
   - Installation: `pip install --upgrade ufbt`
   - Verify installation: `ufbt --version`

### Hardware Requirements

- **Flipper Zero** device with **Momentum firmware** installed
- USB cable for connection
- SD card inserted in Flipper Zero (for manual deployment)
- **Predator 4-in-1 module** (for full functionality):
  - 433MHz RF module with A07 (10dBm)
  - ESP32S2 with Marauder firmware
  - GPS module
  - 2.8-inch display

---

## Understanding the Build System

### What is ufbt?

`ufbt` (micro Flipper Build Tool) is a lightweight tool for building Flipper Zero applications without requiring the full firmware source code. It:
- Downloads the necessary SDK automatically
- Compiles your app against the firmware API
- Generates `.fap` (Flipper Application Package) files
- Can deploy directly to connected devices

### Project Structure

```
predator_app/
├── .ufbt                    # SDK configuration (firmware version, branch)
├── .ufbt.user              # Local build settings
├── application.fam         # App metadata and build configuration
├── Makefile               # Build rules (legacy, ufbt preferred)
├── predator.c             # Main application entry point
├── predator_i.h           # Internal headers
├── scenes/                # UI scenes
├── helpers/               # Helper functions
├── images/                # Icons and graphics
├── data/                  # Static data files
└── dist/                  # Build output (generated)
```

### SDK Configuration (.ufbt)

The `.ufbt` file specifies which firmware SDK to use:

```
FIRMWARE_API_VERSION=af67a99d
SDK_BRANCH=dev
SDK_ORIGIN=https://github.com/Next-Flip/Momentum-Firmware.git
```

This ensures your app is compiled against the correct Momentum firmware version.

---

## Quick Start Build Guide

### For First-Time Build

```powershell
# 1. Install ufbt
pip install --upgrade ufbt

# 2. Navigate to app directory
cd c:\Projects\MomentumSecuritySuite\predator_app

# 3. Build the app
ufbt

# 4. Deploy to connected Flipper Zero
ufbt launch
```

### For Subsequent Builds

```powershell
# Navigate to app directory
cd c:\Projects\MomentumSecuritySuite\predator_app

# Clean previous build (optional but recommended)
ufbt clean

# Build
ufbt

# Launch on device
ufbt launch
```

---

## Detailed Build Process

### Step 1: Install ufbt

```powershell
# Install or upgrade ufbt
pip install --upgrade ufbt

# Verify installation
ufbt --version
```

**Expected Output:**
```
uFBT v0.x.x
```

### Step 2: Update SDK (First Time or After Firmware Update)

```powershell
cd c:\Projects\MomentumSecuritySuite\predator_app
ufbt update
```

This will:
- Download the Momentum firmware SDK specified in `.ufbt`
- Set up the build environment
- Cache SDK files for faster subsequent builds

**Expected Output:**
```
Updating SDK...
Downloading from https://github.com/Next-Flip/Momentum-Firmware.git
SDK updated successfully
```

### Step 3: Build the Application

```powershell
ufbt
```

**Build Process:**
1. Reads `application.fam` for app configuration
2. Compiles all `.c` source files
3. Links against Flipper Zero SDK libraries
4. Generates icon resources
5. Creates `.fap` file in `dist/` directory

**Expected Output:**
```
Building predator
Compiling predator.c
Compiling scenes/...
Compiling helpers/...
Linking...
Creating FAP: dist/predator.fap
Build complete!
```

### Step 4: Verify Build Output

```powershell
# Check dist directory
dir dist
```

You should see:
- `predator.fap` - The compiled application
- `predator.fap.debug` - Debug symbols (optional)

---

## Build Configuration

### Application Metadata (application.fam)

The `application.fam` file defines your app's properties:

```python
App(
    appid="predator",
    name="Predator",
    apptype=FlipperAppType.EXTERNAL,
    entry_point="predator_app",
    requires=["gui", "storage", "notification"],
    stack_size=4 * 1024,
    fap_category="Tools",
    fap_icon="predator_icon.png",
    fap_version="1.0",
)
```

**Key Configuration Options:**
- `appid`: Unique identifier
- `name`: Display name in Flipper Zero menu
- `entry_point`: Main function name
- `requires`: Required system services
- `stack_size`: Memory allocation (increase if app crashes)
- `fap_category`: Menu category (Tools, GPIO, Sub-GHz, etc.)
- `fap_icon`: App icon (10x10 pixels)

### Modifying Build Settings

**Increase Stack Size (if app crashes):**
```python
stack_size=8 * 1024,  # Increase to 8KB
```

**Add Dependencies:**
```python
requires=["gui", "storage", "notification", "subghz", "bt"],
```

**Change Category:**
```python
fap_category="GPIO",  # Apps, GPIO, Sub-GHz, 125kHz RFID, NFC, Infrared, iButton, Bad USB, U2F, Tools
```

---

## Deployment Methods

### Method 1: Direct USB Launch (Recommended for Development)

**Requirements:**
- Flipper Zero connected via USB
- Device unlocked and on main menu

```powershell
cd c:\Projects\MomentumSecuritySuite\predator_app
ufbt launch
```

**What happens:**
1. Copies `.fap` to Flipper Zero SD card
2. Automatically launches the app
3. Shows app logs in terminal

**To stop:** Press `Ctrl+C` in terminal

### Method 2: Manual SD Card Installation

**Steps:**
1. Build the app:
   ```powershell
   ufbt
   ```

2. Locate the `.fap` file:
   ```
   c:\Projects\MomentumSecuritySuite\predator_app\dist\predator.fap
   ```

3. Copy to Flipper Zero SD card:
   - **Via USB:** Access SD card through qFlipper or file manager
   - **Direct SD card reader:** Remove SD card, copy file, reinsert
   
4. Destination path on SD card:
   ```
   /ext/apps/Tools/predator.fap
   ```

5. On Flipper Zero:
   - Navigate to: **Apps** → **Tools** → **Predator**
   - Launch the app

### Method 3: qFlipper Installation

**Using qFlipper GUI:**
1. Open qFlipper application
2. Connect Flipper Zero via USB
3. Go to **File Manager**
4. Navigate to `/ext/apps/Tools/`
5. Upload `predator.fap` from `dist/` directory

### Method 4: Integration with Firmware Build

**For permanent integration into Momentum firmware:**

```powershell
# Clone Momentum firmware
git clone https://github.com/Next-Flip/Momentum-Firmware.git
cd Momentum-Firmware

# Create user applications directory
mkdir applications_user

# Copy Predator app
cp -r c:\Projects\MomentumSecuritySuite\predator_app applications_user\predator

# Build firmware with integrated app
.\fbt COMPACT=1 updater_package

# Flash to Flipper Zero
.\fbt flash_usb_full
```

**Benefits:**
- App is built-in to firmware
- Faster load times
- No SD card space used
- App available even if SD card is removed

---

## Advanced Build Options

### Clean Build

Remove all build artifacts and start fresh:

```powershell
ufbt clean
ufbt
```

**Use when:**
- Build fails unexpectedly
- After modifying `application.fam`
- After updating SDK

### Debug Build

Build with debug symbols and verbose output:

```powershell
ufbt DEBUG=1
```

**Enables:**
- Detailed error messages
- Stack traces
- Debug symbols in `.fap.debug` file

### Verbose Build

See detailed compilation steps:

```powershell
ufbt VERBOSE=1
```

### Custom Build Directory

```powershell
ufbt BUILD_DIR=custom_build
```

### Build with Specific SDK Version

Edit `.ufbt` file:

```
FIRMWARE_API_VERSION=specific_commit_hash
SDK_BRANCH=release
SDK_ORIGIN=https://github.com/Next-Flip/Momentum-Firmware.git
```

Then update and build:

```powershell
ufbt update
ufbt
```

### Generate VS Code Configuration

Set up VS Code for development:

```powershell
ufbt vscode_dist
```

**Creates:**
- `.vscode/c_cpp_properties.json` - IntelliSense configuration
- `.vscode/launch.json` - Debug configuration
- `.vscode/tasks.json` - Build tasks

### Cross-Platform Builds

**Windows (PowerShell):**
```powershell
ufbt
```

**Linux/macOS:**
```bash
ufbt
```

**Git Bash (Windows):**
```bash
ufbt
```

---

## Troubleshooting

### Common Build Errors

#### Error: "ufbt: command not found"

**Cause:** ufbt not installed or not in PATH

**Solution:**
```powershell
# Reinstall ufbt
pip install --upgrade ufbt

# Verify Python Scripts directory is in PATH
# On Windows: C:\Users\YourName\AppData\Local\Programs\Python\PythonXX\Scripts
```

#### Error: "SDK not found"

**Cause:** SDK not downloaded

**Solution:**
```powershell
ufbt update
```

#### Error: "API version mismatch"

**Cause:** Firmware on device doesn't match SDK version

**Solution:**
```powershell
# Option 1: Update SDK to match device firmware
ufbt update

# Option 2: Update device firmware to match SDK
# Use qFlipper to update Flipper Zero firmware
```

#### Error: "undefined reference to..."

**Cause:** Missing function implementation or library

**Solution:**
1. Check if function is declared in headers
2. Verify all source files are included in build
3. Check `application.fam` for missing dependencies:
   ```python
   requires=["gui", "storage", "notification", "missing_service"],
   ```

#### Error: "Stack overflow detected"

**Cause:** Insufficient stack memory

**Solution:**
Edit `application.fam`:
```python
stack_size=8 * 1024,  # Increase from default 4KB
```

#### Error: "Icon file not found"

**Cause:** Missing or incorrectly named icon file

**Solution:**
1. Verify icon file exists: `predator_icon.png`
2. Check icon dimensions: should be 10x10 pixels
3. Verify path in `application.fam`

### Build Warning Messages

#### Warning: "Unused variable"

**Not critical** - Clean up code to remove unused variables

#### Warning: "Implicit function declaration"

**May cause issues** - Add proper `#include` statements

#### Warning: "Format string mismatch"

**May cause crashes** - Fix printf-style format strings

### Runtime Issues

#### App crashes on launch

**Debugging steps:**
1. Build with debug symbols:
   ```powershell
   ufbt DEBUG=1
   ```

2. Check logs via USB:
   ```powershell
   ufbt launch
   ```

3. Increase stack size in `application.fam`

4. Verify all resources (icons, data files) are present

#### App doesn't appear in menu

**Check:**
1. `.fap` file is in correct location: `/ext/apps/Tools/`
2. Firmware supports external apps
3. SD card is properly inserted
4. File isn't corrupted (rebuild and recopy)

#### Features not working

**For Predator-specific issues:**
1. Verify Predator module is connected
2. Check GPIO pin configuration in Momentum settings
3. Ensure switches on module are in correct positions
4. Update Marauder firmware on ESP32 module

---

## Development Workflow

### Iterative Development

```powershell
# 1. Make code changes
# 2. Build and test
ufbt clean && ufbt && ufbt launch

# 3. View logs in terminal
# 4. Press Ctrl+C to stop
# 5. Repeat
```

### Testing Changes

```powershell
# Quick test without clean
ufbt && ufbt launch

# Full rebuild test
ufbt clean && ufbt && ufbt launch

# Test on device without auto-launch
ufbt
# Then manually launch from Flipper Zero menu
```

### Version Control Workflow

```powershell
# After making changes
git add .
git commit -m "Description of changes"
git push

# Build release version
ufbt clean
ufbt
# Test thoroughly before release
```

### Creating Releases

```powershell
# 1. Update version in application.fam
# 2. Clean build
ufbt clean
ufbt

# 3. Copy FAP for distribution
cp dist\predator.fap releases\predator_v1.0.fap

# 4. Create release notes
# 5. Tag version in git
git tag -a v1.0 -m "Release version 1.0"
git push --tags
```

### Debugging with Logs

Add logging to your code:

```c
#include <furi_hal.h>

// In your code
FURI_LOG_D("PREDATOR", "Debug message: %d", value);
FURI_LOG_I("PREDATOR", "Info message");
FURI_LOG_W("PREDATOR", "Warning message");
FURI_LOG_E("PREDATOR", "Error message");
```

View logs:
```powershell
ufbt launch  # Logs appear in terminal
```

### Performance Profiling

Monitor resource usage:
- Check stack usage in logs
- Monitor memory allocation
- Time critical operations
- Test on actual hardware regularly

---

## Additional Resources

### Documentation Links

- **Flipper Zero Official Docs:** https://docs.flipperzero.one/
- **Momentum Firmware:** https://github.com/Next-Flip/Momentum-Firmware
- **ufbt Documentation:** https://pypi.org/project/ufbt/
- **Flipper Application API:** https://github.com/flipperdevices/flipperzero-firmware/tree/dev/documentation

### Community Resources

- **Flipper Zero Discord:** Official community support
- **Reddit:** r/flipperzero
- **GitHub Issues:** Report bugs and request features

### Build System Commands Reference

```powershell
ufbt                    # Build the application
ufbt clean              # Clean build artifacts
ufbt launch             # Build and launch on device
ufbt cli                # Open Flipper CLI
ufbt update             # Update SDK
ufbt create APPID=name  # Create new app from template
ufbt vscode_dist        # Generate VS Code config
ufbt --help             # Show all commands
```

---

## Summary

This document covers everything needed to build and deploy the Predator app for Flipper Zero. For most users, the quick start guide is sufficient. Advanced users can explore custom build configurations and firmware integration.

**Quick Reference:**
```powershell
cd c:\Projects\MomentumSecuritySuite\predator_app
ufbt clean && ufbt && ufbt launch
```

For additional help, see the main README.md or open an issue on GitHub.

---

**Last Updated:** October 2025  
**Predator App Version:** 1.0  
**Compatible Firmware:** Momentum (Next-Flip) dev branch
