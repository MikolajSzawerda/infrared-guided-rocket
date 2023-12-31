
#include "Client.h"

int init_server_connection(const char* host, uint16_t port){
    int sockfd;
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("Error opening socket!\n");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(host);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Error connecting to server!\n");
        return -1;
    }
    return sockfd;
}

int send_packet(int sockfd, struct client_package* package){
    return write(sockfd, package, sizeof (float)*(BUFFER_SIZE+1));
}

int close_server_connection(int sockfd){
    return close(sockfd);
}