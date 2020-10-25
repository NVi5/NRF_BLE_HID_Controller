mingw32-make.exe clean
nrfjprog --recover
mingw32-make.exe flash -j 12
mingw32-make.exe flash_softdevice
pause