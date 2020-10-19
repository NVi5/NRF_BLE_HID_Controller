# -*- coding: utf-8 -*-
"""
Notifications
-------------

Example showing how to add notifications to a characteristic and handle the responses.

Updated on 2019-07-03 by hbldh <henrik.blidh@gmail.com>

"""

import logging
import asyncio
import platform
from bleak import discover
from bleak import BleakClient
from bleak import _logger as logger


CHARACTERISTIC_UUID = "00002a19-0000-1000-8000-00805f9b34fb"  # <--- Change to the characteristic you want to enable notifications from.


def notification_handler(sender, data):
    """Simple notification handler which prints the data received."""
    print("{0}: {1}".format(sender, int.from_bytes(data, byteorder='big')))


async def run(address, debug=False):
    if debug:
        import sys

        l = logging.getLogger("asyncio")
        l.setLevel(logging.DEBUG)
        h = logging.StreamHandler(sys.stdout)
        h.setLevel(logging.DEBUG)
        l.addHandler(h)
        logger.addHandler(h)

    async with BleakClient(address) as client:
        x = await client.is_connected()
        logger.info("Connected: {0}".format(x))

        await client.start_notify(CHARACTERISTIC_UUID, notification_handler)
        await asyncio.sleep(100.0)
        await client.stop_notify(CHARACTERISTIC_UUID)

async def run1():
    return await discover()

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
