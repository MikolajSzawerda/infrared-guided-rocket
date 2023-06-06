
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../Camera/Camera.h"
#include "../SocketClient/Client.h"
#include "../ServoController/ServoController.h"
#include "../ImageProcessor/Processor.h"
#define BUFFER_SIZE 64
#define SERVER_IP "192.168.43.77"
#define SERVER_PORT 6969

double t = 0;

void print_buffer(float* buffer);

int main(){
    int sockfd = init_server_connection(SERVER_IP, SERVER_PORT);
    struct client_package clientPackage;
    struct HotSpot hotSpot;
    memset(clientPackage.buffer, 0, sizeof(float)*BUFFER_SIZE);
    struct servo servoX = init_servo(1);
    struct servo servoY = init_servo(0);
    for(;;){
        generate_fake_circle(clientPackage.buffer, t);
        hotSpot = getHottestSpot(clientPackage.buffer);
        //hotSpot = getHottestSpot2(clientPackage.buffer, &hotSpot);
        // clientPackage.hottestSpot = 8 * hotSpot.y + hotSpot.x;

        if(send_packet(sockfd, &clientPackage) < 0){
            perror("Error sending packet\n");
            exit(1);
        } else {
            printf("X: %d Y: %d\n", hotSpot.x, hotSpot.y);
        }
        step_set_servo_pixel(&servoX, hotSpot.y);
        step_set_servo_pixel(&servoY, hotSpot.x);

        t = fmod(t+0.3, 2*M_PI);
        usleep(500000);

    }
    close(sockfd);

    return 0;
}


void print_buffer(float* buffer){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            printf("%f ", buffer[8*i+j]);
        }
        printf("\n");
    }
}