@echo off
color 0A
title Eyes in the Static

for /f %%A in ('powershell -Command "[System.Windows.Forms.Screen]::PrimaryScreen.Bounds.Width"') do set "width=%%A"
for /f %%A in ('powershell -Command "[System.Windows.Forms.Screen]::PrimaryScreen.Bounds.Height"') do set "height=%%A"

if "%width%"=="" set "width=1920"
if "%height%"=="" set "height=1080"

set /a maxX=width-500
set /a maxY=height-300
if %maxX% lss 1 set "maxX=1"
if %maxY% lss 1 set "maxY=1"

powershell -Command "Add-Type -TypeDefinition 'using System;using System.Runtime.InteropServices;using System.Diagnostics;public class WinMover{[DllImport(\"user32.dll\")]public static extern bool MoveWindow(IntPtr hWnd,int X,int Y,int W,int H,bool bRepaint);public static void MoveMyWindow(int maxX,int maxY){IntPtr h=Process.GetCurrentProcess().MainWindowHandle;Random r=new Random();MoveWindow(h,r.Next(0,maxX),r.Next(0,maxY),500,300,true);}}';[WinMover]::MoveMyWindow(%maxX%,%maxY%)"

:glitch
set "colors=0A 0C 0E 09 0B"
for %%c in (%colors%) do (
    color %%c
    for /l %%i in (1,1,7) do (
        set /p "=■▒╬▄±≡"<nul
    )
    echo.
)
ping -n 1 localhost >nul
goto glitch