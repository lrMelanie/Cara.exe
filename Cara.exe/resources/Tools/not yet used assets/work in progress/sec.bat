@echo off
setlocal enabledelayedexpansion
title Static Echo Chamber
powershell -Command "$Host.UI.RawUI.BackgroundColor = 'Black'; $Host.UI.RawUI.ForegroundColor = 'DarkCyan'"

for /f %%A in ('powershell -Command "[System.Windows.Forms.Screen]::PrimaryScreen.Bounds.Width"') do set "width=%%A"
for /f %%A in ('powershell -Command "[System.Windows.Forms.Screen]::PrimaryScreen.Bounds.Height"') do set "height=%%A"

if "%width%"=="" set "width=1920"
if "%height%"=="" set "height=1080"

set /a maxX=width-500
set /a maxY=height-300
if %maxX% lss 1 set "maxX=1"
if %maxY% lss 1 set "maxY=1"

powershell -Command "Add-Type -TypeDefinition 'using System;using System.Runtime.InteropServices;using System.Diagnostics;public class WinMover{[DllImport(\"user32.dll\")]public static extern bool MoveWindow(IntPtr hWnd,int X,int Y,int W,int H,bool bRepaint);public static void MoveMyWindow(int maxX,int maxY){IntPtr h=Process.GetCurrentProcess().MainWindowHandle;Random r=new Random();MoveWindow(h,r.Next(0,maxX),r.Next(0,maxY),500,300,true);}}';[WinMover]::MoveMyWindow(%maxX%,%maxY%)"

:loop
set /a "char=!RANDOM! %% 94 + 33"
cmd /c exit !char!
for /f "skip=1 delims=;" %%A in ('echo prompt $E^| cmd') do set "escape=%%A"
set "ascii=!escape![38;5;!char!m■"
echo !ascii! !ascii! !ascii! !ascii! !ascii! !ascii! !ascii!
ping -n 1 127.0.0.1 > nul
goto loop