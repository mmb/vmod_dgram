#define _GNU_SOURCE

#include "vrt.h"
#include "cache/cache.h"
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

    AN(cache);

    cache->sockfd = -1;

    priv->priv = cache;
    priv->free = free_mc_vcl_cache;

    return 0;
}

VCL_VOID vmod_send(const struct vrt_ctx *ctx, struct vmod_priv *priv, VCL_STRING value, VCL_STRING host, VCL_INT port)
{
    struct sockaddr_in destaddr;

    cache_t *cache = (cache_t*)priv->priv;

    if (cache->sockfd == -1) {
        cache->sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    }

    bzero(&destaddr, sizeof(destaddr));

    destaddr.sin_family = AF_INET;
    destaddr.sin_addr.s_addr = inet_addr(host);
    destaddr.sin_port = htons(port);

    sendto(cache->sockfd, value, strlen(value), 0, (struct sockaddr *) &destaddr, sizeof(destaddr));

    return;
}
