# Security Policy

## Supported Versions
This is an **academic prototype** with no official production support. Experimental versions may contain intentional vulnerabilities for research purposes.

| Version | Supported          |
| ------- | ------------------ |
| 0.1.x   | :warning: Limited |

## Reporting Vulnerabilities

⚠️ **Important**: This project performs experimental system operations. Many "vulnerabilities" are intentional design choices for academic research.


### Known Risks
```text
1. SYSTEM() COMMAND INJECTION
   - Location: Multiple modules (enable_airplane_mode.cpp, etc.)
   - Risk: High (Arbitrary command execution)
   - Mitigation: Will be replaced with CreateProcess() in future versions

2. ADMIN PRIVILEGE ESCALATION
   - Location: Core permission checks
   - Risk: Medium (Requires existing admin context)
   - Note: Intentional for system integration experiments

3. UNSAFE REGISTRY MODIFICATIONS
   - Location: Bluetooth/airplane mode modules
   - Risk: Critical (Potential system instability)
   - Academic Justification: Windows API interaction research
