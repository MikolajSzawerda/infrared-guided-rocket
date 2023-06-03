//
// Created by mszawerd on 03.06.23.
//

#ifndef PROJEKT_SERVOCONTROLLER_H
#define PROJEKT_SERVOCONTROLLER_H

#define LEFT 0.035
#define RIGHT 0.10
#define IDLE 0.0
#define SERVO_FREQ 50.0
#define OMEGA 1600

#define MIN_POINT 0.0
#define MAX_POINT 7.0
#define MIDDLE_POINT (MIN_POINT+MAX_POINT)/2.0

#include "pwm.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>

struct servo{
    pwm_t* handle;
    double direction;
    double current_angle;
    double indicated_point;
};

struct servo_controller {
    struct servo horizontal;
    struct servo vertical;
};

struct servo init_servo(unsigned int channel);
int set_servo_rot_direction(struct servo* s, double direction);
int rotate_by_angle(struct servo* s, double angle);
int servo_to_point(struct servo* s, double point);
void destroy_servo(struct servo* s);

#endif //PROJEKT_SERVOCONTROLLER_H
