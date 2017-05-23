/*
 * help.c
 *
 *  Created on: 2017年5月23日
 *      Author: chengxuan
 */

// 显示帮助
void help_show() {
    printf("--host -c\tCarbon host name or ip address, default 127.0.0.1\n");
    printf("--port -p\tCarbon port, default 2003\n");
    printf("--dhtpin -d\tDht11 goio pin number, default 7\n");
    printf("--repeat -r\tGet dht11 data repeat number, default 100\n");
    printf("--help -h\tShow this help\n");
}
