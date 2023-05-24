
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Camera.h"
#define BUFFER_SIZE 64
#define SERVER_IP "192.168.43.77"
#define SERVER_PORT 6969

int init_server_connection();

int main(){
    i2c_t* i2c_dev = begin();
    float buffer[BUFFER_SIZE];

    int sockfd = init_server_connection();
    // Send a request to the server
    int request[BUFFER_SIZE];

    for(;;){
        readPixels(i2c_dev, buffer, BUFFER_SIZE);
        for(int i=0;i<BUFFER_SIZE;i++)
            printf("%f ", buffer[i]);
        printf("\n");
        write(sockfd, request, sizeof (request));
        printf("Send packet\n");
        sleep(1);
    }

    close(sockfd);

    return 0;
}


int init_server_connection(){
    int sockfd;
    struct sockaddr_in server_addr;


    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket!");
        exit(1);
    }

    // Set up the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }
    return sockfd;
}