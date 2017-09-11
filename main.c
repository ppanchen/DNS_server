#include <stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "config.h"

const uint16_t PORT = 12345;

int main(int argc, const char* const argv[]) {
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof client_addr;
    int server_socket;
    char buf_in[1024], buf_out[1024];
    int len_in;
    dns_config cfg;

    if (dns_config_read(&cfg, argv[1]) < 0) {
        perror("config file");
        exit(1);
    }

    if ((server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("socket");
        exit(2);
    }

    bzero(&server_addr, sizeof server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof server_addr) < 0) {
        perror("bind");
        exit(2);
    }

    for (;;) {
        printf("... "); fflush(stdout);

        if ((len_in = recvfrom(server_socket, buf_in, sizeof buf_in, 0, (struct sockaddr*)&client_addr, &client_addr_len)) < 0)
            continue;

        printf("%s:%d ->\n", inet_ntoa(client_addr.sin_addr), htons(client_addr.sin_port)); fflush(stdout);

        sendto(server_socket, buf_in, len_in, 0, (struct sockaddr*)&client_addr, client_addr_len);
    }

    close(server_socket);

    return 0;
}