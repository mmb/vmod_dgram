#define _GNU_SOURCE

#include "vrt.h"
#include "vcc_if.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct cache {
  int sockfd;
} cache_t;


static void free_mc_vcl_cache(void *data)
{
    cache_t *cache = (cache_t*)data;

    if (cache->sockfd != -1) {
        close(cache->sockfd);
    }

    free(cache);
}

int init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
    cache_t *cache;

    cache = calloc(1, sizeof(cache_t));

    AN(cache)

    cache->sockfd = -1;

    priv->priv = cache;
    priv->free = free_mc_vcl_cache;

    return 0;
}

void vmod_send(struct sess *sp,  struct vmod_priv *priv, const char *s, const char *host, int port)
{
    cache_t *cache = priv->priv;
    struct sockaddr_in destaddr;

    if (cache->sockfd == -1) {
        cache->sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    }

    bzero(&destaddr, sizeof(destaddr));

    destaddr.sin_family = AF_INET;
    destaddr.sin_addr.s_addr = inet_addr(host);
    destaddr.sin_port = htons(port);

    sendto(cache->sockfd, s, strlen(s), 0, (struct sockaddr *) &destaddr, sizeof(destaddr));

    return;
}
