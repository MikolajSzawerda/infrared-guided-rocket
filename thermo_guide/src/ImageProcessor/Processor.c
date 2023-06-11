#include <stdlib.h>
#include "Processor.h"
#include <stdio.h>


int manhattanDist(int x1, int x2, int y1, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}


struct HotSpot getHottestSpot(float* buffer){
    struct HotSpot hotSpot = {0, 0, -1};
    float curr_max = -1;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){

            if(buffer[8*i+j] < 27.5)
                buffer[8*i+j] = 0;

            if(buffer[8*i+j]>hotSpot.val){
                hotSpot.x = i;
                hotSpot.y = j;
                hotSpot.val = buffer[8*i+j];
            }
        }
    }
    return hotSpot;
}


struct HotSpot getHottestSpot2(float* buffer, struct HotSpot* prevHotSpot) {
    struct HotSpot hotSpot = {0, 0, 0};
    for(int i=0;i<BUFFER_SIZE;i++){
        if(buffer[i] < 27)
            buffer[i] = 0.0;
        if(buffer[i] > 33)
            buffer[i] = 33;
        buffer[i]=pow(1.2, buffer[i]);
    }

    for(int row=0; row<8; row++){
        for(int col=0; col<8; col++){
            float heatVal = 0;
            float weightsSum = 0;

            for(int i=row-CONV_MATRIX_SIZE; i<=row+CONV_MATRIX_SIZE; ++i) {
                for(int j=col-CONV_MATRIX_SIZE; j<=col+CONV_MATRIX_SIZE; ++j) {
                    if(i >= 0 && i < 8 && j >= 0 && j < 8) {
                        float weight = 1 / (1 + manhattanDist(row, i, col, j));
                        heatVal += buffer[8*i+j] * weight;
                        weightsSum += weight;
                    }
                }
            }
            heatVal /= weightsSum;

            if(heatVal > hotSpot.val){
                hotSpot.x = col;
                hotSpot.y = row;
                hotSpot.val = heatVal;
            }
        }
    }
    printf("X: %d Y: %d VAL: %f\n", hotSpot.x, hotSpot.y, hotSpot.val);
    if(prevHotSpot != NULL && hotSpot.val < (prevHotSpot->val + PREV_HOTSPOT_EPSILON)) {
        hotSpot.x = prevHotSpot->x;
        hotSpot.y = prevHotSpot->y;
        hotSpot.val = prevHotSpot->val;
    }

    return hotSpot;
}

int flattenHotSpot(struct HotSpot* hotSpot){
    return 8*hotSpot->y+hotSpot->x;
}

void oldHotSpotDecay(struct HotSpot* oldHotSpot){
    oldHotSpot->val*=DECAY_CONSTANT;
}