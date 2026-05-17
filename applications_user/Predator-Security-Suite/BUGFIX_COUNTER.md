# 🔧 BUGFIX: Counter Not Incrementing

## 🐛 **Issue Reported**
Rolling attack counter stays at 0 - no attempts being counted.

## 🔍 **Root Cause**
When dictionary mode was integrated, the counter increment logic conflicted:
1. Dictionary mode manages its own counter (`current_key_index`)
2. Normal mode increments by 10 per tick
3. Both were running simultaneously, causing conflicts

## ✅ **Fix Applied**

### **1. Conditional Counter Increment**
```c
// OLD (line 422):
carkey_state.codes_tried += 10; // Always incremented

// NEW:
if(!carkey_state.use_dictionary) {
    carkey_state.codes_tried += 10; // Only increment in normal mode
}
```

### **2. Dictionary Mode Counter**
- **Keeloq**: Counter updates when moving to next key (after all seeds tested)
- **Hitag2**: Counter updates after each key tested
- **Normal mode**: Increments by 10 every 100ms tick

## 📊 **How It Works Now**

### **Dictionary Mode (Keeloq/Hitag2)**
```
codes_tried = current_key_index
```
- Updates once per key
- Shows: "1/480", "2/480", etc.

### **Normal Mode (Fixed code)**
```
codes_tried += 10 per tick
```
- Increments by 10 every 100ms
- Shows: "10/65536", "20/65536", etc.

## 🎯 **Testing**

### **To Test Dictionary Mode**:
1. Select Honda, VW, or BMW
2. Go to "Key Bruteforce"
3. Press OK → Should see "[DICT] Keeloq key 1/480"
4. Counter should increment: 1, 2, 3...

### **To Test Normal Mode**:
1. Select a non-Keeloq car (or use fixed code)
2. Go to "Key Bruteforce"
3. Press OK
4. Counter should increment: 10, 20, 30...

## ✅ **Status**
**FIXED** - Counter now increments properly in both modes!
