# X派家庭环境采集

通过dht11传感器采集温度与湿度，并将数据写入graphite carbon中，可在graphite中查看数据

## 依赖

* libpthread
* wiringPi

## 编译安装方法

```bash
make
```

生成可执行文件 `thnomitor`


## 使用方法

```bash
./thnomitor -c 127.0.0.1 -p 2003 -d 7 -r 100
```

### 执行参数
```
--host -c   Carbon host name or ip address, default 127.0.0.1
--port -p   Carbon port, default 2003
--dhtpin -d Dht11 goio pin number, default 7
--repeat -r Get dht11 data repeat number, default 100
--help -h   Show this help
```
