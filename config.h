//
// Created by Petro Panchenko on 9/11/17.
//

#ifndef DNS_SERVER_CONFIG_H
#define DNS_SERVER_CONFIG_H

#include<arpa/inet.h>

typedef struct      str_list{
    char            *str;
    struct str_list *next;
}                   str_list;

typedef struct {
    struct          sockaddr_in dns_addr;
    str_list        *string_list;
}                   dns_config;

int dns_config_read(dns_config *cfg, const char *filename);

#endif //DNS_SERVER_CONFIG_H
