#!env python3
# -*- coding:utf-8 -*-

# 温湿度监控

import sensor.dht11 as dht11;

sensor_dht11 = dht11.Dht11(4)
print sensor_dht11.show();

