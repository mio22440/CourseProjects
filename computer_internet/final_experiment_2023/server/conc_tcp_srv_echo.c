#include <stdio.h>
#include <strings.h>
#include <string.h>

#include <signal.h>
#include <wait.h> /* sigchld wait */

#include <unistd.h>

#include <netinet/in.h>//sockaddr_in

#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <errno.h>//errno

#define CLIENT_MSG_MAX_LEN 127
#define SERVER_MSG_MAX_LEN 127

typedef struct _req_packet_t
{
    uint16_t cid; /* Client ID */
    uint8_t  msg[CLIENT_MSG_MAX_LEN + 1];
}__attribute__((packed)) req_packet_t;

typedef struct _resp_packet_t
{
    uint16_t vcd; /* Veri-code */
    uint8_t  msg[SERVER_MSG_MAX_LEN + 1];
}__attribute__((packed)) resp_packet_t;

int sig_int_flag = 0;           /* SIGINT  发生标志 */
void sig_int_handler(int sig);  /* SIGINT  处理函数 */
void sig_chld_handler(int sig); /* SIGCHLD 处理函数 */
void sig_pipe_handler(int sig); /* SIGPIPE 处理函数 */

void srv_deal(int connfd, short verify_code);

int main(int argc, char **argv)
{
    int   verify_code_from_arg;         /* 从参数获取的 cid, 可能范围超出了 */
    short verify_code;                  /* 验证后确实长度在两字节内的 cid */

    /* 判断参数个数 */
    if(argc != 4){
        printf("srv:usage: ./srv <ip> <port> <verify-code>\n");
        return -1;
    }

    /* 限制在两个字节, 超过就爆炸 */
    verify_code_from_arg = atoi(argv[3]);
    if(
        (verify_code_from_arg < 0) ||
        (verify_code_from_arg > 0xffff)
    )
    {
        printf("[srv] invalid verify-code %d (%d < verify-code <= %d)\n", verify_code_from_arg, 0, 0xffff);
        return -1;
    }
    else
    {
        verify_code = verify_code_from_arg;
    }

    /* 安装信号处理函数 */
    /* SIGINT */
    struct sigaction sig_int_sa;
    sig_int_sa.sa_flags = 0;
    sig_int_sa.sa_handler = sig_int_handler;
    sigemptyset(&sig_int_sa.sa_mask);
    sigaction(SIGINT, &sig_int_sa, NULL);

    /* SIGCHLD */
    struct sigaction sig_chld_sa;
    sig_chld_sa.sa_flags = 0;
    sig_chld_sa.sa_handler = sig_chld_handler;
    sigemptyset(&sig_chld_sa.sa_mask);
    sigaction(SIGCHLD, &sig_chld_sa, NULL);

    /* SIGPIPE */
    struct sigaction sig_pipe_sa, old_sig_pipe_sa;
    sig_pipe_sa.sa_handler = sig_pipe_handler;
    sigemptyset(&sig_pipe_sa.sa_mask);
    sig_pipe_sa.sa_flags = 0;
    // sig_pipe_sa.sa_flags |= SA_RESTART;
    sigaction(SIGPIPE, &sig_pipe_sa, &old_sig_pipe_sa);

    /* 初始化监听 socket */
    int listenfd;                   /* 监听使用的文件描述符 */
    struct sockaddr_in srv_addr_in; /* 服务器 socket 地址 */

    /* 获取套接字文件描述符 */
    while((listenfd = socket(AF_INET,SOCK_STREAM,0)) == -1);

    /* 设置服务器(自己)地址信息 */
    bzero(&srv_addr_in, sizeof(srv_addr_in));
    srv_addr_in.sin_family = AF_INET;
    srv_addr_in.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &(srv_addr_in.sin_addr));

    /* 绑定该地址到监听套接字描述符 */
    if(bind(listenfd, (struct sockaddr*)&srv_addr_in, sizeof(struct sockaddr)) < 0){
        printf("[error] server (%d) fail to bind\n", getpid());
        return -1;
    }
    else
    {
        printf("[srv](%d)[srv_sa](%s:%s)[vcd](%s) Server has initialized!\n", getpid(), argv[1], argv[2], argv[3]);
    }

    /* 开始监听客户端的连接请求, 等待队列允许最多五个客户端排队 */
    listen(listenfd, 5);

    int connfd;                                 /* 连接使用的文件描述符 */
    struct sockaddr_in cli_addr_in;             /* 客户端 socket 地址 */
    int sin_size = sizeof(struct sockaddr_in);  /* socket 地址结构体大小 */
    int pid;                                    /* 用于判断主进程和子进程的进程 id */

    char cli_addr_str[16];                      /* 客户端地址(点分十进制字符串) */
    char cli_port_str[6];                       /* 客户端端口(十进制字符串) */

    /* 主循环 */
    while(0 == sig_int_flag)
    {
        connfd = accept(listenfd, (struct sockaddr*)&cli_addr_in, &sin_size);
        if(connfd < 0)
        {
            if(errno == EINTR)
            {
                continue;
            }
            else
            {
                break;
            }
        }

        /* 创建子进程 */
        pid = fork();
        if(0 != pid){
            /* 父进程 */
            /* 将客户端的 ip 地址和端口转换为字符串 */
            inet_ntop(AF_INET, &cli_addr_in.sin_addr, cli_addr_str, 16);
            sprintf(cli_port_str, "%d", ntohs(cli_addr_in.sin_port));

            printf("[srv](%d)[cli_sa](%s:%s) Client is accepted!\n", getpid(), cli_addr_str, cli_port_str);

            close(connfd);
            //waitpid(-1, NULL, 0);
        }
        else{
            /* 子进程 */
            close(listenfd);
            if(-1 == connfd){
                close(connfd);
                printf("[chd](%d) fail to accept!\n", getpid());
                break;
            }
            else{
                printf("[chd](%d) child process is created!\n", getpid());
            } /* if(-1 == connfd) */

            /* 处理和客户端通信 */
            srv_deal(connfd, verify_code);

            printf("[chd](%d)[ppid](%d)[cli_sa](%s:%s) Client is closed!\n", getpid(), getppid(), cli_addr_str, cli_port_str);

            /* 关闭文件描述符 */
            close(connfd);
            printf("[chd](%d)[ppid](%d) connfd is closed!\n", getpid(), getppid());
            printf("[chd](%d)[ppid](%d) Child process is to return!\n", getpid(), getppid());

            break;
        } /* if(0 != pid) */

    } /* while(0 == sig_int_flag) */

    /* 关闭监听描述符 */
    if(0 != pid)
    {
        close(listenfd);
        //printf("[srv](%d) listenfd is closed!\n", getpid());
        //printf("[srv](%d) parent process is going to exit!\n", getpid());
        //waitpid(-1, NULL, 0);
        //printf("[srv](%d)is closed!\n", getpid());
    }
    
    return 0;
}

void sig_int_handler(int sig)
{
    printf("[srv] SIGINT is coming!\n");
    sig_int_flag = 1;
}

void sig_chld_handler(int sig)
{
    pid_t pid_chld;
    int stat;
    
    while((pid_chld = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        printf("[srv](%d)[chd](%d) Child has terminated!\n", getpid(), pid_chld);
    }
}

void sig_pipe_handler(int sig){
    printf("[srv](%d) SIGPIPE is coming!\n", getpid());
}

void srv_deal(int connfd, short verify_code)
{
    unsigned int read_size = 0;
    unsigned int total_size = 0;
    char *p = NULL;

    req_packet_t  req_buff = {0};   /* 发送用的数据包缓冲区 */
    resp_packet_t resp_buff = {0};  /* 接收服务端数据包的缓冲区 */

    short client_id = 0;            /* 收到客户端的标识 cid */

    /* 设置 vcd (转换为网络字节序) */
    resp_buff.vcd = htons(verify_code);

    while(1)
    {
        /* 接收客户端发送的 req 数据包 */
        /* 接收头部 */
        read_size = read(connfd, &(req_buff.cid), 2);
        if(0 == read_size)
        {
            break;
        }
        client_id = ntohs(req_buff.cid);

        /* 接收数据部分 */
#if 0
        total_size = 0;
        while(1)
        {
            read_size = read(connfd, req_buff.msg + total_size, 1);
            if(0 == read_size)
            {
                break;
            }

            if(
                ('\0' == req_buff.msg[total_size]) &&
                ('\n' == req_buff.msg[total_size - 1])
            )
            {
                printf("[chd](%d)[cid](%d)[ECH_RQT] %s", getpid(), client_id, req_buff.msg);
                break;
            }
            else
            {
                total_size += read_size;
            }
        }
        if(0 == read_size)
        {
            break;
        }
#else
        read_size = read(connfd, req_buff.msg, CLIENT_MSG_MAX_LEN + 1);
        printf("[chd](%d)[cid](%d)[ECH_RQT] %s", getpid(), client_id, req_buff.msg);
#endif

        /* 发送应答数据包 */
        memcpy(resp_buff.msg, req_buff.msg, strlen(req_buff.msg) + 1);

        write(connfd, &resp_buff, 2 + SERVER_MSG_MAX_LEN + 1);
    }
}
