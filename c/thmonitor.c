/*
 * thmonitor.c
 *
 *  Created on: 2017年4月23日
 *      Author: 李枨煊
 */
#include "dht11.c"
#include "carbon.c"
#include <time.h>

int main( void ) {
    struct dht11 data;
    printf( "Raspberry Pi wiringPi DHT11 Temperature test program\n" );

    if ( wiringPiSetup() == -1 ) {
        exit( 1 );
    }

    // 获取当前日期时间
    time_t t;
    int timestamp;
    timestamp = time(&t);

	data = dht11_show(7, 100);
	if (data.success) {
		printf("Humidity = %d, Temperature = %d\n", data.humidity, data.temperature);
		carbon_write("home_env.humidity", data.humidity, timestamp);
	}
	printf("OK%u\n");
    return(0);
}


