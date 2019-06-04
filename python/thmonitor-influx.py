#!env python3
# -*- coding:utf-8 -*-

# 温湿度监控

import time
import sensor.dht11 as dht11
from socket import socket
from influxdb import InfluxDBClient
import time
import traceback
import os

INFLUX_HOST = os.getenv("INFLUX_HOST")
INFLUX_PORT = os.getenv("INFLUX_PORT")
INFLUX_USER = os.getenv("INFLUX_USER")
INFLUX_PASS = os.getenv("INFLUX_PASS")
INFLUX_DATABASE = os.getenv("INFLUX_DATABASE")
INFLUX_TABLE_TEMPERATURE = os.getenv("INFLUX_TABLE_TEMPERATURE")
INFLUX_TABLE_HUMIDITY = os.getenv("INFLUX_TABLE_HUMIDITY")

sensor_dht11 = dht11.Dht11(4)

while (True) :
    try:
        timestamp = int(time.time())
        th = sensor_dht11.show(10)

        if th.temperature_show and th.humidity_show :
            client = InfluxDBClient(INFLUX_HOST, INFLUX_PORT, INFLUX_USER, INFLUX_PASS, INFLUX_DATABASE)
            result = client.write_points([{
                "measurement": INFLUX_TABLE_TEMPERATURE,
                "fields": {"value": th.temperature_show}
            },
            {
                "measurement": INFLUX_TABLE_HUMIDITY,
                "fields": {"value": th.humidity_show}
            }])
            print("Write: %s" % result)
        else :
            print("Empty")

    except Exception as e:
        print(e)
        traceback.print_exc()
        pass

    finally :
        ''' 一分后再处理 '''
        current_time = int(time.time())
        next_time = max(current_time, timestamp + 60)
        sleep_time = next_time - current_time
        if (sleep_time > 0) :
            print("[sleep] %u" % sleep_time)
            time.sleep(sleep_time)
