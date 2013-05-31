#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "vcc_if.h"

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf) {
    return 0;
}

void dgram_send(struct sess *sp, const char *s, const char *host, const int port) {
    int sockfd;
    struct sockaddr_in destaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&destaddr, sizeof(destaddr));

    destaddr.sin_family = AF_INET;
    destaddr.sin_addr.s_addr = inet_addr(host);
    destaddr.sin_port = htons(port);

    sendto(sockfd, s, strlen(s), 0,
        (struct sockaddr *) &destaddr, sizeof(destaddr));

    return;
}
