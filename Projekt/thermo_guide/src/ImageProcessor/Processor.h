//
// Created by mszawerd on 03.06.23.
//

#ifndef PROJEKT_PROCESSOR_H
#define PROJEKT_PROCESSOR_H

#define BUFFER_SIZE 64

struct HotSpot {
    int x;
    int y;
};

struct HotSpot getHottestSpot(float* buffer);

#endif //PROJEKT_PROCESSOR_H
