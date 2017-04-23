/*
 *  dht11.c:
 *      Simple test program to test the wiringPi functions
 *      DHT11 test
 */

#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAXTIMINGS      85

// dht11 结构体
struct dht11 {
    int humidity;
    int humidity_point;
    int temperature;
    int temperature_point;
    short success;
};


/**
 * 读取一次dht11数据
 */
struct dht11 dht11_read(unsigned short dhtpin) {
    uint8_t laststate       = HIGH;
    uint8_t counter  = 0;
    uint8_t j          = 0, i;
    int dht11_dat[5] = { 0, 0, 0, 0, 0 };
    struct dht11 data;

    dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

    /* pull pin down for 18 milliseconds */
    pinMode( dhtpin, OUTPUT );
    digitalWrite( dhtpin, LOW );
    delay( 18 );
    /* then pull it up for 40 microseconds */
    digitalWrite( dhtpin, HIGH );
    delayMicroseconds( 40 );
    /* prepare to read the pin */
    pinMode( dhtpin, INPUT );

    /* detect change and read data */
    for ( i = 0; i < MAXTIMINGS; i++ ) {
        counter = 0;
        while ( digitalRead( dhtpin ) == laststate ) {
            counter++;
            delayMicroseconds( 1 );
            if ( counter == 255 ) {
                break;
            }
        }
        laststate = digitalRead( dhtpin );

        if ( counter == 255 )
            break;

        /* ignore first 3 transitions */
        if ( (i >= 4) && (i % 2 == 0) ) {
            /* shove each bit into the storage bytes */
            dht11_dat[j / 8] <<= 1;
            if ( counter > 16 )
                dht11_dat[j / 8] |= 1;
            j++;
        }
    }

    /*
     * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
     * print it out if data is good
     */
    if ( (j >= 40) && (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) ) {
        data.humidity = dht11_dat[0];
        data.humidity_point = dht11_dat[1];
        data.temperature = dht11_dat[2];
        data.temperature_point = dht11_dat[3];
        data.success = 1;
    } else {
        data.success = 0;
    }
    return data;
}

/**
 * 获取dht11数据，如果失败，则重试
 */
struct dht11 dht11_show(unsigned short dhtpin, unsigned short repeat) {
    struct dht11 result;
    unsigned short i;
    for (i = 0; i < repeat; ++i) {
        result = dht11_read(dhtpin);
        if (result.success) {
            break;
        }
    }
    return result;
}


