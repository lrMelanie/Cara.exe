@echo off
title Cara.exe launcher
cd /d "%~dp0"

net session >nul 2>&1
if %errorlevel% neq 0 (
    echo Requesting administrator privileges...
    powershell -Command "Start-Process -Verb RunAs -FilePath '%~f0'"
    exit /b
)

set "EXE=%~dp0..\x64\Release\Cara.exe.exe"
if not exist "%EXE%" set "EXE=%~dp0..\x64\Debug\Cara.exe.exe"
if not exist "%EXE%" (
    echo [ERROR] Cara.exe.exe not found. Build the solution in Visual Studio once first.
    pause
    exit /b 1
)

start "" "%EXE%"
