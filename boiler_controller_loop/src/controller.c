
#include "controller.h"

struct controller controller_init(char *manipulated_variable, char *process_variable, float overflow, float underflow, float ku, float pu) {
	struct controller cont = {
        .manipulated_variable = manipulated_variable,
        .process_variable = process_variable,
        .overflow = overflow,
        .underflow = underflow,
        .ku = ku,
        .pu = pu,
        .kp = 0.45*ku,
        .ki = 1.2*0.45*ku/pu
    };

    return cont;
}


float pi_algorithm(struct controller *cont, float reference, float control_variable) {
    float error;
    float control_action;

    error = reference - control_variable;
    control_action = cont->ki*(error*0.03) + cont->kp*error;

    if(control_action > cont->overflow){
        control_action = cont->overflow;
    } else if(control_action < cont->underflow){
        control_action = cont->underflow;
    }

    return control_action;
}

float get_sensor(char *sensor) {
	
}

void set_actuator(float control_action, char *actuator) {
	
}