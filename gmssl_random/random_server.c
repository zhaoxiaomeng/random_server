#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdlib.h>

#define SEND_BUF_SIZE 128
int startup()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        exit(1); //退出进程
    }

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(60443); // 指定固定端口

    int ret = bind(sock, (struct sockaddr *)&local, sizeof(local));
    if (ret < 0)
    {
        exit(2);
    }

    if (listen(sock, 5) < 0)
    {
        exit(3);
    }
    return sock;
}

int running_command(const char *command,char *result)
{
    FILE *fp = NULL;
    char buffer[SEND_BUF_SIZE] = {0};
    if (!command || !(fp = popen(command,"r"))){
        fprintf(stderr,"%s %s %d was error\n",__FILE__,__func__,__LINE__);
        return -1; 
    }   
    fread(buffer,SEND_BUF_SIZE,1,fp);
    strcpy(result,buffer);
    fclose(fp);
    return 0;
}
void *handler_request(void *arg)
{
    int sock = (int)arg;
    char buf[4096];
    size_t s = read(sock, buf, sizeof(buf) - 1);
    if (s > 0)
    {
        char sendbuffer[SEND_BUF_SIZE] ;
		printf("random buffer size:%d\n",sizeof(sendbuffer));
        running_command("gmssl rand 128", sendbuffer);
        write(sock, sendbuffer, SEND_BUF_SIZE);
    }
    close(sock);
}

int main()
{
    int listen_sock = startup();
    while (1)
    {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int sock = accept(listen_sock, (struct sockaddr *)&client, &len);
        if (sock < 0)
        {
            continue;
        }
        pthread_t tid;
        pthread_create(&tid, NULL, handler_request, (void *)sock);
        pthread_detach(tid);
    }
    return 0;
}
