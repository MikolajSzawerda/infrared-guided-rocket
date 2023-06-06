#include "Client.h"
#include <stdlib.h>
#include <string.h>
#include "../ImageProcessor/Processor.h"
#define SERVER_IP "192.168.43.77"
#define SERVER_PORT 6969

int x = 0;
int y = 0;

void generate_example_image(float* buffer, int n);

int main(int argc, char* argv[]){
    if(argc<2){
        perror("To few arguments passed!\n");
        exit(1);
    }
    const char* ip = argv[1];
    const int port = atoi(argv[2]);
    printf("Starting client on %s:%d...\n", ip, port);
    int sockfd = init_server_connection(ip, port);
    if(sockfd < 0 ){
        exit(1);
    }
    struct client_package clientPackage;
    struct HotSpot hotSpot={3,3, -1};
    printf("Client connected to server!\n");
    for(;;){
        generate_example_image(clientPackage.buffer, BUFFER_SIZE);
        struct HotSpot currentHotSpot = getHottestSpot2(clientPackage.buffer, &hotSpot);
        printf("CLIENT: X: %d Y: %d VAL: %f\n", currentHotSpot.x, currentHotSpot.y, currentHotSpot.val);
        clientPackage.hottestSpot = flattenHotSpot(&currentHotSpot);
        if(send_packet(sockfd, &clientPackage) < 0){
            perror("Error sending packet\n");
            exit(1);
        } else {
            printf("Packet send!\n");
        }
        x=(x+1)%8;
        y=(y+1)%8;
        oldHotSpotDecay(&currentHotSpot);
        hotSpot = currentHotSpot;
        usleep(400000);
    }
    close_server_connection(sockfd);
}

void generate_example_image(float* buffer, int n){
    memset(buffer, 0, sizeof(float)*n);
    buffer[8*y+x] = 40;
}
