
#include <stdio.h>
#include <unistd.h>
#include "../Camera/Camera.h"
#include "../SocketClient/Client.h"
#define BUFFER_SIZE 64
#define SERVER_IP "192.168.43.77"
#define SERVER_PORT 6969


int main(){
    i2c_t* i2c_dev = begin();
    int sockfd = init_server_connection(SERVER_IP, SERVER_PORT);
    struct client_package clientPackage;
    for(;;){
        readPixels(i2c_dev, clientPackage.buffer, BUFFER_SIZE);
        for(int i=0;i<BUFFER_SIZE;i++)
            printf("%f ", clientPackage.buffer[i]);
        printf("\n");
        if(send_packet(sockfd, &clientPackage) < 0){
            perror("Error sending packet\n");
            exit(1);
        } else {
            printf("Packet send!\n");
        }
        sleep(1);
    }

    close(sockfd);

    return 0;
}
