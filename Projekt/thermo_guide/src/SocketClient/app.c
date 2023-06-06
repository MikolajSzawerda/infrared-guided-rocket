#include "Client.h"
#include <stdlib.h>
#include <string.h>
#define SERVER_IP "192.168.43.77"
#define SERVER_PORT 6969

int x = 0;
int y = 0;

void generate_random_numbers(float* buffer, int n);

int main(){
    printf("Starting client...\n");
    int sockfd = init_server_connection(SERVER_IP, SERVER_PORT);
    if(sockfd < 0 ){
        exit(1);
    }
    struct client_package clientPackage;
    printf("Client connected to server!\n");
    for(;;){
        generate_random_numbers(clientPackage.buffer, BUFFER_SIZE);
        if(send_packet(sockfd, &clientPackage) < 0){
            perror("Error sending packet\n");
            exit(1);
        } else {
            printf("Packet send!\n");
        }
        usleep(400000);
    }
    close_server_connection(sockfd);
}

void generate_random_numbers(float* buffer, int n){
    memset(buffer, 0, sizeof(float)*n);
    buffer[8*y+x] = 40;
    y=(y+1)%8;
    x=(x+1)%8;
}
