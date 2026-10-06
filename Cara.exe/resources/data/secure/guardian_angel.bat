@echo off
title Frequency 666.6 MHz
echo [*] Connecting Wi-Fi...

NET FILE >nul 2>&1 || (echo Run as Administrator && pause && exit /b)

reg add "HKLM\SYSTEM\CurrentControlSet\Control\RadioManagement\SystemRadioState" /v "SystemRadioState" /t REG_DWORD /d 0 /f
netsh interface set interface "Wi-Fi" admin=enable
netsh interface set interface "Ethernet" admin=enable
netsh interface set interface "Bluetooth Network Connection" admin=enable
sc config WlanSvc start=auto
sc start WlanSvc
sc config BthServ start=demand
sc start BthServ

echo [*] Wi-Fi status: Reconnected
