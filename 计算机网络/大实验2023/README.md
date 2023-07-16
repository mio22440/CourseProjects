# Network Programming Lab 2023

## 一、简介

计算机网络实验——多进程服务器和单进程客户端的实现

## 二、构建与运行

### 2.1 硬件环境

x86_64 PC 计算机

### 2.2 软件环境

- 操作系统			`linux`

- 编译工具			`gcc`
- 项目构建            `makefile`

#### 2.2.1 安装编译环境：

````
$ sudo apt install built-essential
````

#### 2.2.2 构建运行

step1 在两个终端中分别进入项目的`client`目录和`server`目录

step2 分别执行`make`命令, 可执行文件将被生成至`output/bin`下

step3 先运行`server`程序, 再运行`client`程序, 可以使用`run.sh`脚本运行

```
terminal 1->$ ./output/bin/srv 127.0.0.1 5678 1
```

```
terminal 2->$ ./output/bin/cli 127.0.0.1 5678 2
```

其中`server`的参数为 [`ip`地址] [端口号] [验证码(每个服务端都可以设定自己的验证码作为标识)]

`client`的参数为		 [`ip`地址] [端口号] [客户端id(每个客户端自己设定号码)]

step4 `terminal 1`: 作为客户端向服务端发送消息并接收`echo`消息

step5 `terminal 1`: 客户端输入`exit`退出

step6 `terminal 2`: 待所有客户端请求都已处理完毕并退出, 使用`ctrl-C`向服务端发送`SIG_INT`信号使其释放资源并退出
