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
void sig_int_handler(int sig);
void cli_deal(int sockfd, short client_id);

int main(int argc, char **argv)
{
    int   client_id_from_arg;         /* 从参数获取的 cid, 可能范围超出了 */
    short client_id;                  /* 验证后确实长度在两字节内的 cid */

    /* 判断参数个数 */
    if(argc != 4){
        printf("[cli] usage: ./cli <ip> <port> <client-id>\n");
        return -1;
    }

    /* 限制在两个字节, 超过就爆炸 */
    client_id_from_arg = atoi(argv[3]);
    if(
        (client_id_from_arg < 0) ||
        (client_id_from_arg > 0xffff)
    )
    {
        printf("[cli] invalid client-id %d (%d < client-id <= %d)\n", client_id_from_arg, 0, 0xffff);
        return -1;
    }
    else
    {
        client_id = client_id_from_arg;
    }

    /* 安装信号处理函数 */
    /* SIGINT */
    struct sigaction sig_int_sa;
    sig_int_sa.sa_flags = 0;
    sig_int_sa.sa_handler = sig_int_handler;
    sigemptyset(&sig_int_sa.sa_mask);
    sigaction(SIGINT, &sig_int_sa, NULL);

    /* 初始化 socket 套接字 */
    int sockfd;                       /* 用于通信的文件描述符 */
    struct sockaddr_in srv_addr_in;   /* 服务器地址 */

    /* 获取套接字文件描述符 */
    while((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1);

    /* 设置服务器地址信息 */
    bzero(&srv_addr_in, sizeof(srv_addr_in));
    srv_addr_in.sin_family = AF_INET;
    srv_addr_in.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &(srv_addr_in.sin_addr));

    /* 连接到服务器 */
    while(0 != connect(sockfd, (struct sockaddr*)&srv_addr_in, sizeof(srv_addr_in)));
    printf("[cli](%d)[srv_sa](%s:%s) Server is connected!\n", getpid(), argv[1], argv[2]);

    /* 处理和服务器的通信 */
    cli_deal(sockfd, client_id);

    /* 关闭描述符 */
    close(sockfd);
    printf("[cli](%d) Client is closed!\n", getpid());

    printf("[cli](%d) Client is to return!\n", getpid());

    return 0;
}

void sig_int_handler(int sig)
{
    sig_int_flag = 1;
}

void cli_deal(int sockfd, short client_id)
{
    char buff[100];                 /* 存放从键盘获取数据的缓冲区 */
    char *p = buff;                 /* 发送缓冲区索引(用来访问缓冲区) */

    req_packet_t  req_buff = {0};   /* 发送用的数据包缓冲区 */
    resp_packet_t resp_buff = {0};  /* 接收服务端数据包的缓冲区 */

    unsigned int read_size = 0;     /* 读取描述符的返回值 */
    unsigned int total_size = 0;    /* 读取到的 msg 的累计长度 */

    short verify_code = 0;          /* 收到服务端的验证码 vcd */

    /* 设置 cid (转换为网络字节序) */
    req_buff.cid = htons(client_id);

    while(1)
    {
        /* 这里用 scanf 的话空格好像会被识别为 0x0a 0x00 */
        fgets(buff, 100, stdin);

        if(strncmp(buff, "EXIT", 4) == 0){
            break;
        }

        memcpy(req_buff.msg, buff, strlen(buff) + 1);

        printf("[cli](%d)[cid](%d)[ECH_RQT] %s", getpid(), client_id, req_buff.msg);

        /* 发送 req 数据包 */
        write(sockfd, &req_buff, 2 + CLIENT_MSG_MAX_LEN + 1);

        /* 接收服务端发回的 resp 数据包 */
        /* 接收头部 */
        read_size = read(sockfd, &(resp_buff.vcd), 2);
        if(0 == read_size)
        {
            break;
        }
        verify_code = ntohs(resp_buff.vcd);

#if 0
        /* 接收数据部分 */
        total_size = 0;
        while(1)
        {
            read_size = read(sockfd, resp_buff.msg + total_size, 1);
            if(0 == read_size)
            {
                break;
            }

            if(
                ('\0' == resp_buff.msg[total_size]) &&
                ('\n' == resp_buff.msg[total_size - 1])
            )
            {
                printf("[cli](%d)[vcd](%d)[ECH_REP] %s", getpid(), verify_code, resp_buff.msg);
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
        read_size = read(sockfd, resp_buff.msg, SERVER_MSG_MAX_LEN + 1);
        printf("[cli](%d)[vcd](%d)[ECH_REP] %s", getpid(), verify_code, resp_buff.msg);
#endif


    } /* while(1) */
}
