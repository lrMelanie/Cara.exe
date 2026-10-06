## ⚠️ Important Notes
Academic Project - Not production-ready code

Requires Caution:
Contains experimental system operations
Some features modify registry/network settings
Always run in controlled environment

Future Potential:
Machine learning integration
Cross-platform support
GUI interface development





# Cara.exe - Experimental Virtual Assistant 🖥️✨

**An academic prototype of a Windows-based virtual assistant with extended system integration capabilities**  
*Developed as a university project - Proof of Concept stage*

---

## 🚀 Features

- **Interactive CLI** with typewriter-style output (`print_slowly` effect)
- **System integration** (Airplane mode control, Bluetooth management, Admin operations)
- **Productivity tools**:
  - Smart reminders with Scroll Lock trigger
  - Schedule management (`schedule add/list/remove`)
  - Motivational quotes database (`vol1.txt`, `vol2.txt`)
  - Network recovery (`fix me`) - restores Wi-Fi/Ethernet/Bluetooth via `guardian_angel.bat`
- **Coderunner Minigame** ⌨️:
  - Timed code-typing challenges
  - Highscore system (`hscore.txt`)
  - Progressive difficulty (8 repository levels)
- **Experimental modules**:
  - Phantom protocol (HTTP request generator)
  - "Black Mirror" visual effects sequence
  - Audio manipulation (MP3/Beep integration)

---

## ⚙️ Installation

1. **Requirements**:
   - Windows 10/11
   - Visual Studio 2022 with C++17 support
   - Admin privileges (for full functionality)

2. **Build**:
```text
git clone https://github.com/lrMelanie/Cara.exe
Open Cara.exe.sln in Visual Studio 2022
Select the x64 configuration
Build (Ctrl+Shift+B)
Run Cara.exe/Cara.exe.exe from the Cara.exe/Cara.exe folder so the resources/ paths resolve
```
probably should work

### ▶ Quick launch (no Visual Studio needed each time)
After building once, just double-click **`Cara.exe/Start Cara.bat`**. It asks for
administrator rights (UAC), sets the working directory so `resources/` resolve,
prefers the Release build (falls back to Debug), and starts the program. Build
again in Visual Studio only when you change the code.

**Sharing with other people:** build in the **Release / x64** configuration. The
runtime is linked statically (`/MT`), so the resulting `Cara.exe.exe` is
self-contained and runs on any Windows 10/11 without installing any Visual C++
redistributable. The Debug build needs Visual Studio's debug runtime DLLs and is
not meant for distribution.



## 🕹️ Basic Usage
```bash
# Core functionality
> schedule add 2025-12-31 23:59 "New Year Countdown"
> motto
> say
> help
> fix me          # recovery: re-enables network if an experimental command cut it off

# Minigame activation
> minigame 

# Experimental commands
> ???
> ???
> ???
> ???
> ???
```




Disclaimer: Contains intentional Easter eggs and prototype-grade code. Not affiliated with any commercial entities. Use at own risk, or not :)