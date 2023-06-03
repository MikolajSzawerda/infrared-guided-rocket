#include "ServoController.h"

struct servo init_servo(unsigned int channel){
    pwm_t *pwm;
    pwm = pwm_new();
    struct servo s = {pwm, IDLE, 0.0f, MIDDLE_POINT};
    if (pwm_open(pwm, 0, channel) < 0) {
        fprintf(stderr, "pwm_open(): %s\n", pwm_errmsg(pwm));
    }

    if (pwm_set_frequency(pwm, SERVO_FREQ) < 0) {
        fprintf(stderr, "pwm_set_frequency(): %s\n", pwm_errmsg(pwm));
    }

    if (pwm_set_duty_cycle(pwm, IDLE) < 0) {
        fprintf(stderr, "pwm_set_duty_cycle(): %s\n", pwm_errmsg(pwm));
    }

    if (pwm_enable(pwm) < 0) {
        fprintf(stderr, "pwm_enable(): %s\n", pwm_errmsg(pwm));
    }
    return s;
}

int set_servo_rot_direction(struct servo* s, double direction){
    if (pwm_set_duty_cycle(s->handle, direction) < 0) {
        fprintf(stderr, "pwm_set_duty_cycle(): %s\n", pwm_errmsg(s->handle));
        return -1;
    }
    return 0;
}

int rotate_by_angle(struct servo* s, double angle){
    unsigned int time = floor(fabs((angle/OMEGA)*1e6));
    printf("TIME: %d ", time);
    if(angle>0){
        set_servo_rot_direction(s, RIGHT);
        printf("RIGHT\n");
    } else {
        set_servo_rot_direction(s, LEFT);
        printf("LEFT\n");
    }
    usleep(time);
    set_servo_rot_direction(s, IDLE);
    return 0;
}
int servo_to_point(struct servo* s, double point){
    return 0;
}
void destroy_servo(struct servo* s){
//    pwm_close(s->handle);
    pwm_free(s->handle);
}