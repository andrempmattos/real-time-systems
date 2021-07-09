
#include "controller.h"

struct controller {
    char *prefix;
    float overflow;
    float underflow;
    float ku;
    float pu;
    float kp;
    float ki;
};

struct controller controller_init(char *prefix, float overflow, float underflow, float ku, float pu) {
	struct controller cont;
    cont.prefix = prefix;
    cont.overflow = overflow;
    cont.underflow = underflow;
    cont.ku = ku;
    cont.pu = pu;

    cont.kp = 0.45*cont.ku;
    cont.ki = 1.2*cont.kp/cont.pu;
    return cont;
}


void pi_algorithm(struct controller *cont, float reference, const int interval) {
    float control_variable;
    float error;
    float control_action;

    control_variable = get_sensor();
    error = reference - control_variable;
    
    control_action = cont->ki*(error*interval/1000000000) + cont->kp*error;

    if(control_action > cont->overflow){
        control_action = cont->overflow;
    } else if(control_action < cont->underflow){
        control_action = cont->underflow;
    }

    set_actuator(control_action, cont);

}

float get_sensor(void) {
	
}

void set_actuator(float control_action, struct controller *cont) {
	
}