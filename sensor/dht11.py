#!env python3
# -*- coding:utf-8 -*-

import RPi.GPIO as GPIO
import time

''' 结构体 '''
class Struct:
    data = []
    temperature = 0
    temperature_point = 0
    humidity = 0
    humidity_point = 0
    temperature_show = 0.0
    humidity_show = 0.0
    check = 0
    right = None

    def __init__(self, data):
        self.data = data
        humidity_bit = data[0:8]
        humidity_point_bit = data[8:16]
        temperature_bit = data[16:24]
        temperature_point_bit = data[24:32]
        check_bit = data[32:40]

        for i in range(8):
            self.humidity += humidity_bit[i] * 2 ** (7-i)
            self.humidity_point += humidity_point_bit[i] * 2 ** (7-i)
            self.temperature += temperature_bit[i] * 2 ** (7-i)
            self.temperature_point += temperature_point_bit[i] * 2 ** (7-i)
            self.check += check_bit[i] * 2 ** (7-i)

        tmp = self.humidity + self.humidity_point + self.temperature + self.temperature_point
        self.right = (self.check == tmp)


''' 传感器异常 '''
class SesorError(Exception)
    pass

''' 核心处理方法 '''
class Dht11:
    channel = 4

    ''' 构建方法 '''
    def __init__(self, channel):
        self.channel = channel

    def show(self, repeat = 0):
        i = 0
        while (i <= repeat)
            result = self._fetch()
            if (result.right)
                break;
            i++

        if (!result.right)
            raise SesorError("sensor return wrong data")

    ''' 核心获取数据方法 '''
    def _fetch(self):
        data = []
        j = 0
        GPIO.setmode(GPIO.BCM)

        GPIO.setup(channel, GPIO.OUT)
        GPIO.output(channel, GPIO.LOW)
        time.sleep(0.02)
        GPIO.output(channel, GPIO.HIGH)
        GPIO.setup(channel, GPIO.IN)

        while GPIO.input(channel) == GPIO.LOW:
            continue
        while GPIO.input(channel) == GPIO.HIGH:
            continue

        while j < 40:
            k = 0
            while GPIO.input(channel) == GPIO.LOW:
                continue
            while GPIO.input(channel) == GPIO.HIGH:
                k += 1
                if k > 100:
                    break
            if k < 8:
                data.append(0)
            else:
                data.append(1)

            j += 1

        GPIO.cleanup()
        result = Struct(data)
        return result


