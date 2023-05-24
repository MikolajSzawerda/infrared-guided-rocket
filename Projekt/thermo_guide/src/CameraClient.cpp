
#include "Camera.h"
#define BUFFER_SIZE 64
int main(){
    Camera camera;
    camera.begin();
    float buffer[BUFFER_SIZE];
    camera.readPixels(buffer);
    for(auto p:buffer)
        printf("%f ", p);
    printf("\n");
}