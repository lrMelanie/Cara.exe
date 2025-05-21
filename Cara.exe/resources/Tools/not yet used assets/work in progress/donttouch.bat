@echo off
color 4B
title Waiting Room: Overwatch Console

for /f %%A in ('powershell -Command "[System.Windows.Forms.Screen]::PrimaryScreen.Bounds.Width"') do set "width=%%A"
for /f %%A in ('powershell -Command "[System.Windows.Forms.Screen]::PrimaryScreen.Bounds.Height"') do set "height=%%A"

if "%width%"=="" set "width=1920"
if "%height%"=="" set "height=1080"

set /a maxX=width-500
set /a maxY=height-300
if %maxX% lss 1 set "maxX=1"
if %maxY% lss 1 set "maxY=1"

powershell -Command "Add-Type -TypeDefinition 'using System;using System.Runtime.InteropServices;using System.Diagnostics;public class WinMover{[DllImport(\"user32.dll\")]public static extern bool MoveWindow(IntPtr hWnd,int X,int Y,int W,int H,bool bRepaint);public static void MoveMyWindow(int maxX,int maxY){IntPtr h=Process.GetCurrentProcess().MainWindowHandle;Random r=new Random();MoveWindow(h,r.Next(0,maxX),r.Next(0,maxY),500,300,true);}}';[WinMover]::MoveMyWindow(%maxX%,%maxY%)"

echo Initializing neural interface...
ping -n 3 localhost >nul

:dialog
set "responses=ACCESS DENIED|SYSTEM BREACH|OVERRIDE ACCEPTED|CRYPTO LOCKED|DATA STREAM CORRUPT"
set /a "idx=!random! %% 5 + 1"
for /f "tokens=%idx%" %%r in ("%responses%") do echo [AI] %%r
ping -n 2 localhost >nul
goto dialog