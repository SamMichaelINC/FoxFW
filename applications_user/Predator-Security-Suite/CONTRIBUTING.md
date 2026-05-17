# Contributing to Predator Security Suite

Thank you for your interest in contributing to Predator Security Suite! This document provides guidelines for contributing to this project.

## ⚠️ **CRITICAL: Legal and Ethical Requirements**

**Before contributing, you MUST:**

1. ✅ Read and accept the [LICENSE](LICENSE) (EASRL)
2. ✅ Understand this is a **security research tool for authorized use only**
3. ✅ Agree to maintain **ethical standards** in all contributions
4. ✅ **Never** submit code that enables illegal activities
5. ✅ **Never** remove or weaken security disclaimers

**ALL CONTRIBUTIONS MUST:**
- Maintain legal disclaimers throughout
- Include authorization warnings for sensitive features
- Follow responsible disclosure practices
- Comply with international laws and regulations

---

## 🎯 **How to Contribute**

### **Types of Contributions Welcome**

We welcome contributions in these areas:

#### ✅ **Encouraged:**
- 🐛 **Bug fixes** - Stability and reliability improvements
- 📚 **Documentation** - Clarifications, translations, examples
- 🔒 **Security improvements** - Vulnerability fixes, hardening
- ⚡ **Performance optimizations** - Memory usage, speed improvements
- 🌍 **Localization** - UI translations (maintaining legal warnings)
- 🧪 **Testing** - Unit tests, integration tests, coverage
- 🎨 **UI/UX improvements** - Better user experience
- 📊 **Analytics** - Attack success rate tracking, statistics

#### ⚠️ **Requires Review:**
- 🔑 **New manufacturer keys** - Must be from legitimate research
- 📡 **New frequencies** - Must comply with regional regulations
- 🚗 **New car models** - Must be properly verified
- 🛠️ **New attack techniques** - Must be for defensive research only

#### ❌ **NOT Accepted:**
- Removal of legal disclaimers or warnings
- Features designed specifically for illegal use
- Code that bypasses authorization checks for malicious purposes
- Obfuscation of attack code to hide intent
- Backdoors or malware
- Exploits without responsible disclosure

---

## 🔄 **Contribution Process**

### **1. Fork the Repository**
```bash
git clone https://github.com/YOUR_USERNAME/MomentumSecuritySuite.git
cd MomentumSecuritySuite
```

### **2. Create a Feature Branch**
```bash
git checkout -b feature/your-feature-name
# or
git checkout -b bugfix/your-bugfix-name
```

### **3. Make Your Changes**

#### **Code Standards:**
- Follow existing code style and conventions
- Use descriptive variable and function names
- Add comments for complex logic
- Keep functions focused and modular
- Maintain memory efficiency (3KB stack, 6KB heap)

#### **Documentation Standards:**
- Update README.md if adding features
- Document new functions with clear comments
- Add examples for new functionality
- Update CHANGELOG.md with your changes

#### **Legal Standards:**
- Include authorization warnings for new attack features
- Maintain all existing legal disclaimers
- Add regional compliance notes if relevant
- Document any legal implications

### **4. Test Your Changes**

```bash
# Build and verify
cd predator_app
ufbt clean
ufbt

# Test on actual hardware if possible
ufbt launch

# Verify no memory leaks or crashes
# Test all affected features
```

**Required Tests:**
- ✅ Compiles without errors or warnings
- ✅ No memory leaks or stack overflows
- ✅ Existing functionality still works
- ✅ New features work as intended
- ✅ Legal disclaimers still display correctly

### **5. Commit Your Changes**

```bash
git add .
git commit -m "feat: Add description of your feature"
# or
git commit -m "fix: Description of bug fix"
# or
git commit -m "docs: Description of documentation change"
```

**Commit Message Format:**
```
<type>: <short description>

<longer description if needed>

- Detail 1
- Detail 2

Closes #issue_number (if applicable)
```

**Types:**
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation only
- `style`: Code style (formatting, no logic change)
- `refactor`: Code refactoring
- `perf`: Performance improvement
- `test`: Adding tests
- `chore`: Maintenance tasks

### **6. Push and Create Pull Request**

```bash
git push origin feature/your-feature-name
```

Then create a Pull Request on GitHub with:
- Clear description of changes
- Why the change is needed
- How it was tested
- Any breaking changes
- Screenshots (if UI changes)

---

## 📝 **Pull Request Guidelines**

### **PR Checklist:**

- [ ] Code compiles without errors or warnings
- [ ] All tests pass (if applicable)
- [ ] Documentation updated (README, comments, etc.)
- [ ] CHANGELOG.md updated
- [ ] Legal disclaimers maintained
- [ ] No removal of authorization warnings
- [ ] Follows existing code style
- [ ] Commit messages follow convention
- [ ] PR description is clear and complete

### **PR Review Process:**

1. **Automated Checks** - Build verification
2. **Code Review** - Maintainer review for quality/security
3. **Legal Review** - Ensure compliance with EASRL license
4. **Testing** - Verify on real hardware if needed
5. **Merge** - Once approved and all checks pass

---

## 🔒 **Security Considerations**

### **Reporting Security Vulnerabilities**

**DO NOT** open public issues for security vulnerabilities.

Instead:
1. Email: security@predator-security.com (if available)
2. Provide detailed description
3. Include proof of concept (if safe to share)
4. Wait for response before public disclosure

### **Responsible Disclosure:**
- Give maintainers reasonable time to fix (90 days recommended)
- Coordinate disclosure timeline
- Provide clear reproduction steps
- Document impact and severity

---

## 🌍 **Adding Worldwide Support**

### **New Manufacturers:**

When adding barrier/car manufacturers:

```c
// 1. Add to enum in proper regional group
typedef enum {
    // ... existing ...
    BarrierManufacturerYourNew,  // YourManufacturer (Country)
} BarrierManufacturer;

// 2. Add cryptographic key (from legitimate research)
static const uint64_t barrier_manufacturer_keys[] = {
    // ... existing ...
    0xYOURKEYHERE123456,  // YourManufacturer - researched key
};

// 3. Add display name
static const char* barrier_manufacturer_names[] = {
    // ... existing ...
    "YourManufacturer (Country)",
};
```

**Requirements:**
- Keys must be from legitimate security research
- Include country/region
- Document source of key data
- Ensure legal to publish

### **New Frequencies:**

When adding frequencies:

```c
// Add to predator_frequencies.h with proper documentation
433123000,  // 433.123 MHz - Description (Region/Standard)
```

**Requirements:**
- Document regulatory region (FCC/ETSI/ARIB/etc.)
- Note legal restrictions
- Verify frequency is legitimate
- Include use case

---

## 📚 **Documentation Guidelines**

### **Code Comments:**

```c
// GOOD:
// Initialize Keeloq engine for worldwide barrier manufacturers
// Uses 64-bit manufacturer-specific keys with 528-round encryption
bool init_keeloq_engine(uint64_t mfr_key) {
    // ...
}

// BAD:
// init keeloq
bool init_keeloq_engine(uint64_t k) {
    // ...
}
```

### **README Updates:**

- Keep legal disclaimers prominent
- Document new features clearly
- Include usage examples
- Note any breaking changes
- Update feature counts (manufacturers, frequencies, etc.)

---

## 🐛 **Reporting Bugs**

### **Bug Report Template:**

```markdown
**Description:**
Clear description of the bug

**Steps to Reproduce:**
1. Go to...
2. Click on...
3. See error

**Expected Behavior:**
What should happen

**Actual Behavior:**
What actually happens

**Environment:**
- Flipper Zero firmware version:
- Predator version:
- Expansion board:
- OS (for build issues):

**Logs:**
```
Paste relevant logs here
```

**Screenshots:**
If applicable
```

---

## ✨ **Feature Requests**

### **Feature Request Template:**

```markdown
**Feature Description:**
Clear description of proposed feature

**Use Case:**
Why is this needed? What problem does it solve?

**Proposed Implementation:**
How might this work?

**Legal Considerations:**
Any authorization/compliance issues?

**Alternatives:**
Other ways to achieve this?

**Additional Context:**
Any other relevant information
```

---

## 🧪 **Testing Guidelines**

### **Manual Testing:**

For hardware changes:
1. Test on actual Flipper Zero
2. Verify with expansion boards (if applicable)
3. Test memory usage (stack/heap)
4. Verify no crashes or freezes
5. Test all affected features

### **Automated Testing:**

If adding tests:
```c
// Use existing test framework
#include "test_framework.h"

static TestResult test_your_feature(void* context) {
    // Setup
    
    // Execute
    
    // Verify
    
    return TestResultPass;
}
```

---

## 📞 **Getting Help**

### **Questions?**

- Check existing documentation first
- Search closed issues for similar questions
- Ask in discussions (if available)
- Be specific and provide context

### **Community Guidelines:**

- Be respectful and professional
- Follow code of conduct
- Help others when possible
- Share knowledge ethically
- Report inappropriate behavior

---

## ⚖️ **Legal Compliance**

### **By Contributing, You Agree:**

1. Your contributions are your original work
2. You have the right to submit the contribution
3. Your contributions will be licensed under EASRL
4. You will not contribute illegal or malicious code
5. You accept all terms of the LICENSE file
6. You will use contributions only for authorized research

### **Prohibited:**

- Contributions that violate laws
- Stolen or proprietary code
- Malicious or harmful code
- Copyright infringement
- Contributions without authorization

---

## 🎓 **Code of Conduct**

### **Our Standards:**

✅ **Positive Behavior:**
- Being respectful and inclusive
- Accepting constructive criticism
- Focusing on what's best for security research
- Showing empathy and kindness
- Helping others learn

❌ **Unacceptable Behavior:**
- Harassment or discrimination
- Trolling or insulting comments
- Publishing others' private information
- Promoting illegal activities
- Other unprofessional conduct

### **Enforcement:**

Violations may result in:
1. Warning
2. Temporary ban
3. Permanent ban
4. Legal action (if applicable)

---

## 📋 **Contributor Agreement**

By submitting a contribution, you certify that:

- [x] I have read and agree to the LICENSE (EASRL)
- [x] My contribution is my original work
- [x] I have the legal right to submit this contribution
- [x] My contribution will not enable illegal activities
- [x] I understand this is a security research tool
- [x] I will use contributions only for authorized purposes
- [x] I accept full responsibility for my contributions

---

## 🙏 **Thank You!**

We appreciate your contributions to Predator Security Suite. Your help makes this tool better for the **worldwide professional security research community**.

**Remember:**
- Use responsibly
- Test legally
- Research ethically
- Help others
- Be professional

---

**Questions about contributing?**
- Open a discussion
- Check existing documentation
- Contact maintainers

**Predator Security Suite v2.0 - Worldwide Enterprise Edition**  
**For Authorized Professional Security Research Only**

⚠️ **CONTRIBUTE RESPONSIBLY. CODE ETHICALLY. RESEARCH LEGALLY.** ⚠️
