#include "Processor.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define BUFFER_SIZE 64

int x=0;
int y=0;
void generate_example_image(float* buffer, int n);
int main(){
    float buffer[BUFFER_SIZE];
    struct HotSpot oldSpot={0, 0, -1};
    for(;;){
        generate_example_image(buffer, BUFFER_SIZE);
        struct HotSpot hotSpot = getHottestSpot2(buffer,&oldSpot);
        printf("X: %d Y: %d val: %f\n", hotSpot.x, hotSpot.y, hotSpot.val);
        oldHotSpotDecay(&hotSpot);
        oldSpot = hotSpot;
        x=(x+1)%8;
        y=(y+1)%8;
        sleep(1);
    }
    return 0;
}

void generate_example_image(float* buffer, int n){
    memset(buffer, 0, sizeof(float)*n);
    buffer[8*y+x] = 40;
}