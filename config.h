//
// Created by Petro Panchenko on 9/11/17.
//

#ifndef DNS_SERVER_CONFIG_H
#define DNS_SERVER_CONFIG_H

#define over

#include<arpa/inet.h>

typedef struct {
    struct sockaddr_in dns_addr;
    char **blacklist;
} dns_config;

int dns_config_read(dns_config *cfg, const char *filename);

#endif //DNS_SERVER_CONFIG_H
