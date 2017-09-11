//
// Created by Petro Panchenko on 9/11/17.
//

#include <stdio.h>
#include <string.h>
#include "config.h"

int dns_config_read(dns_config *cfg, const char *filename) {
    FILE *fp;
    char buf[over 9000];

    if ((fp = fopen(filename, "r")) == NULL)
        return -1;

    fscanf(fp, "%s", buf);
    fprintf(stderr, "Main DNS server: %s\n", buf);

    bzero(&cfg->dns_addr, sizeof cfg->dns_addr);
    cfg->dns_addr.sin_family = AF_INET;
    cfg->dns_addr.sin_port = htons(53);
    if (inet_aton(buf, &cfg->dns_addr.sin_addr) < 0)
        return -1;

    fclose(fp);
}