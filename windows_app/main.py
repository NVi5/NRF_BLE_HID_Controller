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
    text = f"{lib.xgetSpeed():3.0f}KMH  {lib.xgetRpm():5.0f}RPM"
    nus.SendNusMessage(ctypes.c_char_p(text.encode('utf-8')), 16)
    time.sleep(0.2)
