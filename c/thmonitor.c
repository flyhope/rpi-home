/*
 * thmonitor.c
 *
 *  Created on: 2017年4月23日
 *      Author: 李枨煊
 */
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include "dht11.c"
#include "carbon.c"
#include "help.c"

int main(int argc, char *argv[]) {
    struct dht11 data;
    short show_help = 0;

    // 参数结构体
    struct params_t {
        unsigned short dhtpin;
        unsigned short repeat;
        char *host;
        unsigned short port;

    };
    struct params_t params = {7, 100, "127.0.0.1", 2003};

    // 参数选项
    struct option long_options[] = {
         { "host",   1, NULL, 'c' },
         { "port",   1, NULL, 'p' },
         { "dhtpin", 1, NULL, 'd' },
         { "repeat", 1, NULL, 'r' },
         { "help",   0, NULL, 'h' },
         {  NULL,    0, NULL, 0   },
    };
    const char * const short_options = "c:p:d:r:h";

    // 获取参数
    int c;
    while((c = getopt_long (argc, argv, short_options, long_options, NULL)) != -1) {
        switch (c) {
        case 'h' :
            show_help = 1;
            break;
        case 'c' :
            params.host = optarg;
            break;
        case 'p' :
            params.port = atoi(optarg);
            break;
        case 'd' :
            params.dhtpin = atoi(optarg);
            break;
        case 'r' :
            params.repeat = atoi(optarg);
            break;

        }
    }

    // 显示软件名称
    printf("Pi wiringPi DHT11 Temperature home monitor\n" );

    // 显示帮助
    if (show_help) {
        help_show();
        exit(1);
    }

    // 打印参数
    printf("host=%s, port=%d, dhtpin=%d, repeat=%d\n", params.host, params.port, params.dhtpin, params.repeat);

    // Gpio未准备好退出
    if ( wiringPiSetup() == -1 ) {
        exit( 1 );
    }

    // 获取当前日期时间
    time_t t;
    int timestamp;
    timestamp = time(&t);

    // 获取dht11数据
	data = dht11_show(params.dhtpin, params.repeat);
	if (data.success) {
		printf("Humidity = %d, Temperature = %d \n", data.humidity, data.temperature);
		int ret_humidity = carbon_write(params.host, params.port, "home_env.humidity", data.humidity, timestamp);
		int ret_temperature = carbon_write(params.host, params.port, "home_env.temperature", data.temperature, timestamp);
		printf("Carbon write %d:%d\n", ret_humidity, ret_temperature);
	}

    return(0);
}
