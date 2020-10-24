import asyncio
from bleak import BleakClient

address = "24:71:89:cc:09:05"
MODEL_NBR_UUID = "00002aa6-0000-1000-8000-00805f9b34fb"

async def run(address):
    async with BleakClient(address) as client:
        await client.write_gatt_char(MODEL_NBR_UUID,"test")

loop = asyncio.get_event_loop()
loop.run_until_complete(run(address))

if __name__ == "__main__":
    loop1 = asyncio.get_event_loop()
    device_list = loop1.run_until_complete(run1())
    for device in device_list:
        try:
            print(device.address)
            loop = asyncio.get_event_loop()
            loop.run_until_complete(run(device.address, True))
            break
        except Exception as e:
            print(e)
        print("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%")