![ntop][ntopng_logo] ![ntop][ntop_logo]
# nDPI

[![Build Status](https://travis-ci.org/ntop/nDPI.png?branch=dev)](https://travis-ci.org/ntop/nDPI)

## What is nDPI ?

nDPI is an open source LGPLv3 library for deep-packet inspection. Based on OpenDPI it includes ntop extensions. We have tried to push them into the OpenDPI source tree but nobody answered emails so we have decided to create our own source tree

### How To Compile nDPI

In order to compile this library do

- ./autogen.sh
- ./configure
- make

To run tests do additionally:

- make check

Please note that the pre-requisites for compilation include:
- GNU tools (autogen, automake, autoconf, libtool)
- GNU C compiler (gcc)

### How To Add A New Protocol Dissector

The entire procedure of adding new protocols in detail:

1. Add new protocol together with its unique ID to: src/include/ndpi_protocol_ids.h
2. Create a new protocol in: src/lib/protocols/
3. Variables to be kept for the duration of the entire flow (as state variables) needs to be placed in: /include/ndpi_structs.h in ndpi_flow_tcp_struct (for TCP only), ndpi_flow_udp_struct (for UDP only), or ndpi_flow_struct (for both).
4. Add a new entry for the search function for the new protocol in: src/include/ndpi_protocols.h
5. Choose (do not change anything) a selection bitmask from: src/include/ndpi_define.h
6. Add a new entry in ndpi_set_protocol_detection_bitmask2 in: src/lib/ndpi_main.c
7. Set protocol default ports in ndpi_init_protocol_defaults in: src/lib/ndpi_main.c
8. Add the new protocol file to: src/lib/Makefile.am
9.  ./autogen.sh
10. ./configure
11. make
12. make check

### Creating A Source File Tar Ball

If you want to distribute a source tar file of nDPI do:

- make dist

To ensure that a tar file includes all necessary files and to run tests on distribution do:

- make distcheck

[ntopng_logo]: https://camo.githubusercontent.com/0f789abcef232035c05e0d2e82afa3cc3be46485/687474703a2f2f7777772e6e746f702e6f72672f77702d636f6e74656e742f75706c6f6164732f323031312f30382f6e746f706e672d69636f6e2d313530783135302e706e67

[ntop_logo]: https://camo.githubusercontent.com/58e2a1ecfff62d8ecc9d74633bd1013f26e06cba/687474703a2f2f7777772e6e746f702e6f72672f77702d636f6e74656e742f75706c6f6164732f323031352f30352f6e746f702e706e67

### 过滤特定应用层数据包

1. 引入了过滤特定应用层数据包的功能，将对应的ip包转发给指定服务器
例如 `./ndpiReader -a xx.xx.xx.xx -b port -c 100 -e yy.yy.yy.yy` 指的是将100对应的应用层协议(SIP, 通过-h查看)的IP包转发到-a -b指定的ip、port的socket上

2. 加入了缓存unknown protocol数据包的功能，在乱序到达的情况下不丢失检测出应用层协议的数据包(上面的-y指定了redis服务器)
该功能依赖于[redis](https://github.com/antirez/redis)和[hiredis](https://github.com/redis/hiredis)(redis的c client), 即运行ndpiReader的服务器需要安装hiredis
需要将`.so`文件放到`/usr/local/lib`中, 并将`.h`文件放到`/usr/local/include/hiredis`中(这一步可能由hiredis的Makefile完成)
在ndpiReader的Makefile中 修改`LDFLAGS = -L/usr/local/lib -lhiredis`
安装redis的服务器需要修改`redis.conf`文件，注释掉`bind 127.0.0.1` 并修改`protected-mode no`
