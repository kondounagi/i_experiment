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
#define BUF 256


int main(int argc, char* argv[]){
    // build socket
    int s;
    if (argc == 2) {
        int ss = socket(PF_INET, SOCK_STREAM, 0);
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(atoi(argv[1]));
        addr.sin_addr.s_addr = INADDR_ANY;
        bind(ss, (struct sockaddr *)&addr, sizeof(addr));
        listen(ss, 10);
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(struct sockaddr_in);
        s = accept(ss, (struct sockaddr *)&client_addr, &len);
        if (s < 0) {
            fprintf(stderr, "connection failed!!\n");
            exit(0);
        }
        close(ss);
    } else if (argc == 3) {
        s = socket(PF_INET, SOCK_STREAM, 0);
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(argv[1]);
        addr.sin_port = htons(atoi(argv[2]));
        int ret = connect(s, (struct sockaddr *)&addr, sizeof(addr));
        if (ret != 0) {
            fprintf(stderr, "connection failed !!!\n");
        }
    } else {
        fprintf(stderr, "please check args\n");
    }

    char send_data[BUF];
    char recieved_data[BUF];
    int n, r;
    while (true) {
        // sending 1 bite
        n = read(0, send_data, sizeof(send_data));
        if (n > 0) {
            int snd = send(s, send_data, sizeof(send_data), 0);
            if(snd == -1) {
                fprintf(stderr, "send error\n");
                exit(0);
            }
            // fprintf(stderr, "sending successed.\n");
        }
        // recieving 1 bite
        r = recv(s, recieved_data, sizeof(recieved_data), 0);
        if (r > 0) {
            int wrt = write(1, recieved_data, sizeof(recieved_data));
            if(wrt == -1){
                fprintf(stderr, "write error!\n");
                exit(0);
            }
            // fprintf(stderr, "recieving successed.\n");
        }
    }
    fprintf(stderr, "datasend finished.\n");
    close(s);
    return 0;
}
