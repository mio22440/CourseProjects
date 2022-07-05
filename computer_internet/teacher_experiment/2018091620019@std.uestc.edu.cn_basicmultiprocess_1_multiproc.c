#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*to use open*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*to use read*/
#include <unistd.h>

/*to use sigaction and waitpid*/
#include <signal.h>
#include <sys/wait.h>


void handle_sigChld(int sigArg);

int main(int argc, char **argv){
    if((argc != 3)||(0 != strcmp(argv[1], "-c"))){
        printf("bm: usage: ./bm -c [procNum]\n");
        return -1;
    }
    
    /**************DEBUG
    int i=0;
    for(i=0; i < 3; i++){
        printf("%s\n", argv[i]);
    }
    **/
    int procNum = argv[2][0]-'0';//the process number

    int fd;
    fd = open("multiproc_td.txt", O_RDWR);
    if(fd == -1){
        printf("--fail to open the file--\n");
        return -1;
    }

    /*set signal*/
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = handle_sigChld;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD, &act, 0);

    int i=0;
    int pidRet = -1;
    printf("%d start\n", getpid());//father
    for(i=0; i<procNum-1; i++){
        pidRet = fork();
        
        if(0 == pidRet){    
            printf("%d start\n", getpid());
            break;
        }
        if(-1 == pidRet){
            printf("--proc create fail--\n");
            return -1;
        }
    }

    char a[6];
    int readLen;
    readLen = read(fd, &a, 5);

    if(readLen > 0){
        a[readLen] = '\0';
        printf("%d read [%s]\n", getpid(), a);
    }
    if(0 == pidRet){
        sleep(1);
        printf("%d end\n", getpid());
        exit(0);
    }
    sleep(5);
    close(fd);//only father do ?
    printf("%d end\n", getpid());

    return 0;
}

void handle_sigChld(int sigArg){
    while(waitpid(-1, NULL, WNOHANG));
}