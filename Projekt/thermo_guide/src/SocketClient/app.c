#include "Client.h"
#include <stdlib.h>
#define SERVER_IP "192.168.0.185"
#define SERVER_PORT 6969

void generate_random_numbers(float* buffer, int n);

int main(){
    printf("Starting client...\n");
    int sockfd = init_server_connection(SERVER_IP, SERVER_PORT);
    if(sockfd < 0 ){
        exit(1);
    }
    struct client_package clientPackage;
    printf("Client connected to server!\n");
    for(int i=0;i<10;i++){
        generate_random_numbers(clientPackage.buffer, BUFFER_SIZE);
        if(send_packet(sockfd, &clientPackage) < 0){
            perror("Error sending packet\n");
            exit(1);
        } else {
            printf("Packet send!\n");
        }
        sleep(1);
    }
    close_server_connection(sockfd);
}

void generate_random_numbers(float* buffer, int n){
    for(int i=0;i<n;i++){
        buffer[i] = 40.0*(float)rand()/(float)RAND_MAX;
    }
}
