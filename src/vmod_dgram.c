#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>

#include "vcc_if.h"

void
vmod_send(struct sess *sp, const char *s, const char *host,
    int port) {
    int sockfd;
    struct sockaddr_in destaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&destaddr, sizeof(destaddr));

    destaddr.sin_family = AF_INET;
    destaddr.sin_addr.s_addr = inet_addr(host);
    destaddr.sin_port = htons(port);

    sendto(sockfd, s, strlen(s), 0,
        (struct sockaddr *) &destaddr, sizeof(destaddr));

    close(sockfd);

    return;
}
