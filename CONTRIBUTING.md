
### CONTRIBUTING.md
```markdown
# Contribution Guidelines

## Academic Project Notice
This repository is part of university coursework. Contribution opportunities are limited but welcome for:
- Documentation improvements
- Non-core feature experiments
- Educational code samples

## Getting Started

### Prerequisites
1. Windows development environment
2. Visual Studio 2022
3. CMake 3.20+
4. Academic affiliation (preferred)

### Setup
```bash
git clone https://github.com/yourusername/DeltaFoxtrot.git
cd DeltaFoxtrot
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
