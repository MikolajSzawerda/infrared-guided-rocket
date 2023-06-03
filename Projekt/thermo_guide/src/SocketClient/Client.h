//
// Created by mszawerd on 03.06.23.
//

#ifndef PROJEKT_CLIENT_H
#define PROJEKT_CLIENT_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 64

struct client_package {
    float buffer[BUFFER_SIZE];
};

int init_server_connection(const char* host, uint16_t port);
int send_packet(int sockfd, struct client_package* package);
int close_server_connection(int sockfd);

#endif //PROJEKT_CLIENT_H
