import ctypes
import time

lib = ctypes.cdll.LoadLibrary('./Dll2.dll')
lib.xOpenProcess(ctypes.c_char_p("Need for Speed".encode('utf-8')))
lib.xgetSpeed.restype = ctypes.c_float
lib.xgetRpm.restype = ctypes.c_float

nus = ctypes.cdll.LoadLibrary('./NordicNUS_win32.dll')
nus.OpenBleNusHandle.restype = ctypes.c_int
nus.SendNusMessage.argtypes = [ctypes.c_char_p, ctypes.c_uint32]

while(nus.OpenBleNusHandle() == -1):
    print("Trying to connect...")
    time.sleep(0.5)
while(True):
    xd = "{:3.0f}".format(lib.xgetSpeed()) + "{:5.0f}".format(lib.xgetRpm())
    nus.SendNusMessage(ctypes.c_char_p(xd.encode('utf-8')), 3+1+5)
    time.sleep(0.033)
