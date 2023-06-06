#include "Processor.h"

struct HotSpot getHottestSpot(float* buffer){
    struct HotSpot hotSpot ={0, 0};
    float curr_max = -1;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(buffer[8*i+j]>curr_max){
                hotSpot.x = i;
                hotSpot.y = j;
                curr_max = buffer[8*i+j];
            }
        }
    }
    return hotSpot;
}