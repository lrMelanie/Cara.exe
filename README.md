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
```bash
git clone https://github.com/lrMelanie/Cara.exe
cd Cara.exe
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```
probably should work



## 🕹️ Basic Usage
```bash
# Core functionality
> schedule add 2025-12-31 23:59 "New Year Countdown"
> motto
> say
> help

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