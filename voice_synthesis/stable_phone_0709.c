//本課題8.1に対応する
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#define BUF 4096

struct communicate_set{
    char data[BUF];
    int socket;
};

int build_server_socket(char port[]){
    int ss = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(ss, (struct sockaddr *)&addr, sizeof(addr));

    listen(ss, 10);

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(struct sockaddr_in);

    int s = accept(ss, (struct sockaddr *)&client_addr, &len);

    if (s < 0) {
        fprintf(stderr, "server connection failed!!\n");
        exit(0);
    }
    close(ss);
    return s;
}


int build_client_socket(char ip[], char port[]) {
    int s = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(atoi(port));

    int ret = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    if (ret != 0) {
        fprintf(stderr, "client connection failed !!!\n");
    }
    return s;
}

void read_data_thread(struct communicate_set *set){
    char shellcmd[] = "./voice_synthesis.sh";
    while(true){
        // get text from console
        char input_text[128];
        scanf("%127s", input_text);

        // join shellcmd and input_text
        char cmdline[256];
        sprintf(cmdline, "%s %s", shellcmd, input_text);

        // exec cmdline
        FILE *fp;
        if ((fp = popen(cmdline, "r")) == NULL) {
            err(EXIT_FAILURE, "%s", cmdline);
        }

        // send_data
        char send_data[1];
        int n;
        while ((n = fread(send_data, sizeof(char), 1, fp)) != 0) {
           int snd = send(set->socket, send_data, sizeof(send_data), 0);
           if (snd == -1) {
               fprintf(stderr, "send error\n");
               exit(0);
           }
       }
    }
}

void recieve_data_thread(struct communicate_set *set){
    while(true){
        int r = recv(set->socket, set->data, sizeof(set->data), 0);
        if (r > 0) {
            int wrt = write(1, set->data, sizeof(set->data));

            if(wrt == -1){
                fprintf(stderr, "write error!\n");
                exit(0);
            }
                // fprintf(stderr, "recieving successed.\n");
        }
    }
}

int main(int argc, char* argv[]){
    // build socket
    int s;
    if (argc == 2) {
        char *port  = argv[1];
        s = build_server_socket(port);
    } else if (argc == 3) {
        char *ip = argv[1];
        char *port = argv[2];
        s = build_client_socket(ip, port);
    } else {
        fprintf(stderr, "please check args\n");
    }

    pthread_t sendthread, recievethread;
    int ret1, ret2;

    struct communicate_set send_set;
    send_set.socket = s;

    struct communicate_set recieve_set;
    recieve_set.socket = s;

    ret1 = pthread_create(&sendthread, NULL, (void *)read_data_thread, &send_set);
    ret2 = pthread_create(&recievethread, NULL, (void *)recieve_data_thread, &recieve_set);

    if(ret1 !=0){
        fprintf(stderr, "failed to create sendthread\n");
        exit(0);
    }
    if(ret2 !=0){
        fprintf(stderr, "failed to create recievethread\n");
        exit(0);
    }

     ret1 = pthread_join(sendthread,NULL);
     fprintf(stderr, "ret1(send) thread started \n");
     ret2 = pthread_join(recievethread,NULL);
     fprintf(stderr, "ret2(recv) thread started \n");
    if(ret1 !=0){
        fprintf(stderr, "failed to join sendthread\n");
        exit(0);
    }
    if(ret2 !=0){
        fprintf(stderr, "failed to join recievethread\n");
        exit(0);
    }
    
    fprintf(stderr, "datasend finished.\n");
    close(s);
    return 0;
}
