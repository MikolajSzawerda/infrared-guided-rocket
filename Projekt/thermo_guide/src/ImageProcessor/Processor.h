//
// Created by mszawerd on 03.06.23.
//

#ifndef PROJEKT_PROCESSOR_H
#define PROJEKT_PROCESSOR_H

#define BUFFER_SIZE 64

#define PREV_HOTSPOT_EPSILON 0.5
#define CONV_MATRIX_SIZE 1
#define CONV_WEIGHT_ALPHA 1.0

struct HotSpot {
    int x;
    int y;
    float val;
};

inline int manhattanDist(int x1, int x2, int y1, int y2);

struct HotSpot getHottestSpot(float* buffer);

struct HotSpot getHottestSpot2(float* buffer, struct HotSpot* prevHotSpot);

#endif //PROJEKT_PROCESSOR_H
