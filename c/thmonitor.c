/*
 * thmonitor.c
 *
 *  Created on: 2017年4月23日
 *      Author: 李枨煊
 */
#include "dht11.c"

int main( void ) {
    struct dht11 data;
    printf( "Raspberry Pi wiringPi DHT11 Temperature test program\n" );

    if ( wiringPiSetup() == -1 ) {
        exit( 1 );
    }

    while ( 1 ) {
        data = dht11_show(7, 100);
        if (data.success) {
            printf("Humidity = %d, Temperature = %d\n", data.humidity, data.temperature);
        }
        printf("ok\n");
        delay( 1000 ); /* wait 1sec to refresh */
    }

    return(0);
}


