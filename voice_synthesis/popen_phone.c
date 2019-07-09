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
#define BUF 256


int main(int argc, char* argv[]){
    // check argv[] and set get port number
    if (argc != 2) {
        fprintf(stderr, "don't input port number\n");
        exit(0);
    }
    int port_number = atoi(argv[1]);

    int ss = socket(PF_INET, SOCK_STREAM, 0);

    // bind server socket
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_number);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(ss, (struct sockaddr *)&addr, sizeof(addr));

    // listen
    listen(ss, 10);

    // accept
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    int s = accept(ss, (struct sockaddr *)&client_addr, &len);

    if (s < 0) {
        fprintf(stderr, "connection failed!!\n");
        exit(0);
    }
    fprintf(stderr, "accepted\n");
    close(ss);

    // send data

    while (1) {
        char input_text[128];
        scanf("%127s", input_text);

        char shellcmd[] = "./voice_synthesis.sh";
        char cmdline[256];
        sprintf(cmdline, "%s %s", shellcmd, input_text);
        FILE *fp;
        if ((fp = popen(cmdline, "r")) == NULL) {
            err(EXIT_FAILURE, "%s", cmdline);
        }

       char send_data[1];
       int n;
       while ((n = fread(send_data, sizeof(char), 1, fp)) != 0) {
           int snd = send(s, send_data, sizeof(send_data), 0);
           if(snd == -1) {
               fprintf(stderr, "send error\n");
               exit(0);
           }
       }
   }
   fprintf(stderr, "datasend finished.\n");
   close(s);
    /*
    char received_data[1];
    int r;
    fprintf(stderr, "start receiving\n");
    while( r = recv(s, received_data, sizeof(received_data), 0) >0 ){
        int wrt = write(1, received_data, sizeof(received_data));
        if(wrt == -1){
            fprintf(stderr, "write error!\n");
            exit(0);
        }
    }
    fprintf(stderr, "receiving finished.\n");
    */
    return 0;
}
