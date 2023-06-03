#include "Camera.h"
#include <unistd.h>
#define BUFFER_SIZE 64

void print_buffer(float* buffer){
    for(int i=0;i<BUFFER_SIZE;i++)
        printf("%f ", buffer[i]);
    printf("\n");
}

int main(){
    i2c_t* i2c_dev = begin();
    float buffer[BUFFER_SIZE];
    for(int i=0;i<10;i++){
        readPixels(i2c_dev, buffer, BUFFER_SIZE);
        print_buffer(buffer);
        sleep(1);
    }

}

