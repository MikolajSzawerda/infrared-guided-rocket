#include "ServoController.h"
#include <unistd.h>

int main(){
    struct servo s = init_servo(1);
    rotate_by_angle(&s, 90.0);
    sleep(2);
    rotate_by_angle(&s, -90.0);
    set_servo_rot_direction(&s, IDLE);
    destroy_servo(&s);
}
