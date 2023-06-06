
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../Camera/Camera.h"
#include "../SocketClient/Client.h"
#include "../ServoController/ServoController.h"
#define BUFFER_SIZE 64
#define SERVER_IP "192.168.43.77"
#define SERVER_PORT 6969

int x = 0;
int y = 0;

double t = 0;

void generate_random_numbers(float* buffer, int n);
void draw_circle(float* buffer);
void print_buffer(float* buffer);

int main(){
    int sockfd = init_server_connection(SERVER_IP, SERVER_PORT);
    struct client_package clientPackage;
    memset(clientPackage.buffer, 0, sizeof(float)*BUFFER_SIZE);
    struct servo servoX = init_servo(1);
    struct servo servoY = init_servo(0);
    for(;;){
//        generate_random_numbers(clientPackage.buffer, BUFFER_SIZE);
        draw_circle(clientPackage.buffer);
        if(send_packet(sockfd, &clientPackage) < 0){
            perror("Error sending packet\n");
            exit(1);
        } else {
            printf("X: %d Y: %d\n", x, y);
        }
        step_set_servo_pixel(&servoX, y);
        step_set_servo_pixel(&servoY, x);

        t = fmod(t+0.3, 2*M_PI);
        usleep(500000);

    }
    close(sockfd);

    return 0;
}

void generate_random_numbers(float* buffer, int n){
    memset(buffer, 0, sizeof(float)*n);
    buffer[8*y+x] = 40;
}

void draw_circle(float* buffer){
    memset(buffer, 0, sizeof(float)*BUFFER_SIZE);
    double x_d = 3*cos(t)+3.0;
    double y_d = 3*sin(t)+3.0;
    x = (int)(x_d+0.5);
    y = (int)(y_d+0.5);
    buffer[8*x+y]=40;
}

void print_buffer(float* buffer){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            printf("%f ", buffer[8*i+j]);
        }
        printf("\n");
    }
}