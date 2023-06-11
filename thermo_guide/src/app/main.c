
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../Camera/Camera.h"
#include "../SocketClient/Client.h"
#include "../ServoController/ServoController.h"
#include "../ImageProcessor/Processor.h"
#define BUFFER_SIZE 64
#define SERVER_IP "10.42.0.1"
#define SERVER_PORT 6969

double t = 0;

void print_buffer(float* buffer);

int main(){
    int sockfd = init_server_connection(SERVER_IP, SERVER_PORT);
    struct client_package clientPackage;
    struct HotSpot hotSpot={3,3, -1};
    memset(clientPackage.buffer, 0, sizeof(float)*BUFFER_SIZE);
    i2c_t* i2c_dev = begin();
    struct servo servoX = init_servo(1);
    struct servo servoY = init_servo(0);
    for(;;){
        //generate_fake_circle(clientPackage.buffer, t);
        readPixels(i2c_dev, clientPackage.buffer, BUFFER_SIZE);
        // hotSpot = getHottestSpot(clientPackage.buffer);
        struct HotSpot currentHotSpot = getHottestSpot2(clientPackage.buffer, &hotSpot);
        clientPackage.hottestSpot = flattenHotSpot(&currentHotSpot);

        if(send_packet(sockfd, &clientPackage) < 0){
            perror("Error sending packet\n");
            exit(1);
        } else {
            printf("X: %d Y: %d\n", hotSpot.x, hotSpot.y);
        }
        step_set_servo_pixel(&servoX, hotSpot.y);
        step_set_servo_pixel(&servoY, hotSpot.x);

        // t = fmod(t+0.3, 2*M_PI);
        oldHotSpotDecay(&currentHotSpot);
        hotSpot = currentHotSpot;
        usleep(100000);

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