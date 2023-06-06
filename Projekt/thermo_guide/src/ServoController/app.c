#include "ServoController.h"
#include <unistd.h>

int main(){
    struct servo s = init_servo(1);
//    rotate_by_angle(&s, 90.0);
//    sleep(2);
//    rotate_by_angle(&s, -90.0);
//    set_servo_rot_direction(&s, IDLE);
    for(int i=0;i<=180;i+=10){
        step_set_servo_angle(&s, (double)i);
        printf("ANGLE: %d\n", i);
        sleep(2);
    }
    destroy_servo(&s);
}
