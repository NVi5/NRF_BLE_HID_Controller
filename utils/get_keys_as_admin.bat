sc create cmdsvc binpath= "REG EXPORT HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\services\BTHPORT\Parameters\Keys %~dp0keys.reg"
sc start cmdsvc
sc delete cmdsvc