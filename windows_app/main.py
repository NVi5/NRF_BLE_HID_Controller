import ctypes
import time

nus = ctypes.cdll.LoadLibrary('./NordicNUS_win32.dll')
nus.OpenBleNusHandle.restype = ctypes.c_int
nus.SendNusMessage.argtypes = [ctypes.c_char_p, ctypes.c_uint32]

while(nus.OpenBleNusHandle() == -1):
    print("Trying to connect...")
    time.sleep(0.5)
print("Connected.")

lib = ctypes.cdll.LoadLibrary('./Dll2.dll')
while(lib.xOpenProcess("NFSC.exe") == -1):
    nus.SendNusMessage(ctypes.c_char_p("Ready".encode('utf-8')), 16)
    time.sleep(0.5)
lib.xgetSpeed.restype = ctypes.c_float
lib.xgetRpm.restype = ctypes.c_float

while(True):
    text = f"{lib.xgetSpeed():3.0f}KMH  {lib.xgetRpm():5.0f}RPM"
    nus.SendNusMessage(ctypes.c_char_p(text.encode('utf-8')), 16)
    time.sleep(0.2)
