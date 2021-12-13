# 随机数实现

本代码功能为，在本地打开60443端口，在收到socket请求的时候，返回128byte的二进制随机数。
有两种实现：

* 基于GmSSL Random的随机数

* 基于SDF接口的随机数

## 基于GMSSL Random的软件随机数

要求必须安装GmSSL环境

### 编译

在gmssl_random目录下直接运行make即可


## 基于SDF的硬件随机数

要求必须安装SDF设备，并且将sdf的接口库(本代码为libswsds.so)放在/lib等可以查找到的目录下

注意，本代码编写时由于SDF设备不在，没有做实际测试

## 环境配置

```
root@ubuntu:~/random_server/sdf_random# cp libswsds.so /lib
root@ubuntu:~/random_server/sdf_random# ldconfig
```

### 编译

在gmssl_random目录下直接运行make即可

```
root@ubuntu:~/random_server/sdf_random# make
```


## 测试

### 测试环境配置

首先开启随机数服务端

对于GMSSL软件随机数，运行如下命令

```
root@ubuntu:~/random_server/gmssl_random# ./random_server 
```

对于SDF硬件随机数，运行如下命令

```
root@ubuntu:~/random_server/sdf_random# ./random_server 
```

然后将测评中心随机数测试程序复制到对应目录下（测评中心为/root/)

```
root@ubuntu:~/random_server/random_test_suite# cp gather_rand random rand.sh  /root/
```

### 运行测试

```
root@ubuntu:~/random_server# /root/rand.sh 127.0.0.1 60443 koal               
```