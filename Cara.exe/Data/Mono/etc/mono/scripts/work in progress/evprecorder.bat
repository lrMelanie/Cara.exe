@echo off
color 0C
title Electronic Voice Phenomenon Recorder v5.0

for /f %%A in ('powershell -Command "[System.Windows.Forms.Screen]::PrimaryScreen.Bounds.Width"') do set "width=%%A"
for /f %%A in ('powershell -Command "[System.Windows.Forms.Screen]::PrimaryScreen.Bounds.Height"') do set "height=%%A"

if "%width%"=="" set "width=1920"
if "%height%"=="" set "height=1080"

set /a maxX=width-500
set /a maxY=height-300
if %maxX% lss 1 set "maxX=1"
if %maxY% lss 1 set "maxY=1"

powershell -Command "Add-Type -TypeDefinition 'using System;using System.Runtime.InteropServices;using System.Diagnostics;public class WinMover{[DllImport(\"user32.dll\")]public static extern bool MoveWindow(IntPtr hWnd,int X,int Y,int W,int H,bool bRepaint);public static void MoveMyWindow(int maxX,int maxY){IntPtr h=Process.GetCurrentProcess().MainWindowHandle;Random r=new Random();MoveWindow(h,r.Next(0,maxX),r.Next(0,maxY),500,300,true);}}';[WinMover]::MoveMyWindow(%maxX%,%maxY%)"

:matr
for /l %%i in (1,1,1000) do (
    set "line="
    for /l %%j in (1,1,80) do (
        set /a "rand=!random! %% 2"
        set "line=!line!!rand!"
    )
    echo !line!
)
goto matr