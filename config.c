//
// Created by Petro Panchenko on 9/11/17.
//

#include <stdio.h>
#include <string.h>
#include "config.h"
#include "get_next_line.h"

int dns_config_read(dns_config *cfg, const char *filename) {
    FILE        *fp;
    char        *buf = 0;
    int         ret;
    str_list    *list;

    list = malloc(sizeof list);
    bzero(list, sizeof list);
    cfg->string_list = list;
    if ((fp = fopen(filename, "r")) == NULL) {
        return -1;
    }

    if ((ret = get_next_line(fp->_fileno, &buf)) <= 0) {
        return -1;
    }

    fprintf(stderr, "Main DNS server: %s\n", buf);
    bzero(&cfg->dns_addr, sizeof cfg->dns_addr);
    cfg->dns_addr.sin_family = AF_INET;
    cfg->dns_addr.sin_port = htons(53);
    if (inet_aton(buf, &cfg->dns_addr.sin_addr) < 0) {
        return -1;
    }
    free(buf);

    if ((ret = get_next_line(fp->_fileno, &buf)) <= 0)
        return -1;
    list->str = strdup(buf);
    list->next = 0;
    while ((ret = get_next_line(fp->_fileno, &buf)) > 0){
        list->next = malloc(sizeof list);
        list->next->str = strdup(buf);
        list->next->next = 0;
        list = list->next;
        free(buf);
    }
    fclose(fp);
}