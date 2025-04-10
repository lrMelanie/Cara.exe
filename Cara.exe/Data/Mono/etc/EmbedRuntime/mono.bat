@echo off
echo [*] Connecting Wi-Fi...

NET FILE >nul 2>&1 || (echo Run as Administrator) && pause && exit)

reg add "HKLM\SYSTEM\CurrentControlSet\Control\RadioManagment\SystemRadioState" /v "SystemRadiostate" /t REG_DWORD /d 0 /f
netsh interface set interface "Wi-Fi" admin=enable
sc config WlanSvc start=auto
sc start WlanSvc

echo [*] Wi-Fi status: Reconnected