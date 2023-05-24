
#include <stdio.h>
#include "Camera.h"
#define BUFFER_SIZE 64

int main(){
    i2c_t* i2c_dev = begin();
    float buffer[BUFFER_SIZE];
    readPixels(i2c_dev, buffer, BUFFER_SIZE);
    for(int i=0;i<BUFFER_SIZE;i++)
        printf("%f ", buffer[i]);
    printf("\n");
}