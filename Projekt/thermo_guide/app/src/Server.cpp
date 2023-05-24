#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 6969
#define BUFFER_SIZE 64

int init_server();

int main() {
    int sockfd, newsockfd, client_len;
    struct sockaddr_in client_addr;
    sockfd = init_server();
    client_len = sizeof(client_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, (socklen_t *)&client_len);
    if (newsockfd < 0) {
        perror("Error accepting connection");
        exit(1);
    }

    printf("Client connected\n");
    int buffer[BUFFER_SIZE];
    for(;;){
        read(newsockfd, buffer, sizeof(buffer));
        printf("Client request: ");
        for(int k : buffer){
            printf("%d ", k);
        }
        printf("\n");
    }

    return 0;
}

int init_server(){
    int sockfd;
    struct sockaddr_in server_addr;
    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Set up the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    // Listen for client connections
    listen(sockfd, 1);

    printf("Server listening on port %d...\n", PORT);
    return sockfd;
}

