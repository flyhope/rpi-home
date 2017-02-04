#!env python3
# -*- coding:utf-8 -*-

# 温湿度监控

import time
import sensor.dht11 as dht11
from socket import socket

CARBON_SERVER = "127.0.0.1"
CARBON_PORT = 2003

sensor_dht11 = dht11.Dht11(4)

while (True) :
    try:
        timestamp = int(time.time())
        th = sensor_dht11.show(10)

        monitor_datas = (
            "house.temperature " + str(th.temperature_show) + " " + str(timestamp),
            "house.humidity " + str(th.humidity_show) + " " + str(timestamp)
        )

        message = ""
        for monitor_data in monitor_datas :
            message += monitor_data + "\n";

        print(message)
        sock = socket()
        sock.connect((CARBON_SERVER, CARBON_PORT))
        sock.sendall(bytes(message, encoding="utf8"))
        sock.close()

    except :
        pass

    finally :
        ''' 一分后再处理 '''
        current_time = int(time.time())
        next_time = max(current_time, timestamp + 60)
        sleep_time = next_time - current_time
        if (sleep_time > 0) :
            print("[sleep] %u" % sleep_time)
            time.sleep(sleep_time)

