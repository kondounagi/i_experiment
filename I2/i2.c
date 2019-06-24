#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

int s = socket(PF_INET, SOCK_STREAM, 0);

struct sockadder = AF_INET;
