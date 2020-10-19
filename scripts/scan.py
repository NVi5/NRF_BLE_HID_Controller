import asyncio
from bleak import discover

async def run():
    return await discover()

loop = asyncio.get_event_loop()
device_list = loop.run_until_complete(run())
print(device_list)