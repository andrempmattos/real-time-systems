/**
 * \brief Controller implementation.
 * 
 * \date 2021/08/09
 * 
 * \addtogroup controller
 * \{
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "controller.h"
#include "threads.h"

/* Mutex handler */
pthread_mutex_t socket_mut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t control_mut = PTHREAD_MUTEX_INITIALIZER;

/* Set points for temperature and height */
float TEMP_SET_POINT = 30;
float HEIGHT_SET_POINT = 2;

controller_t controller_init(char *manipulated_variable, char *process_variable, float overflow, float underflow, float ku, float pu) {
	controller_t cont = {
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

float pi_algorithm(controller_t *cont, float reference, float control_variable) {

    pthread_mutex_lock(&control_mut);

    float error;
    float control_action;

    error = reference - control_variable;
    control_action = cont->ki*(error*0.03) + cont->kp*error;

    if(control_action > cont->overflow){
        control_action = cont->overflow;
    } else if(control_action < cont->underflow){
        control_action = cont->underflow;
    }

    pthread_mutex_unlock(&control_mut);

    return control_action;
}

float get_sensor(char *sensor) {

    pthread_mutex_lock(&socket_mut);

    char buffer[MAX_BUFFER_SIZE]; 
    float value = 0;
    int received_size = 0;

    send_message(sensor);
    received_size = receive_message(buffer);

    if(received_size > 0) {
        buffer[received_size] = '\0';
        memcpy(buffer, buffer+3, received_size+1-3); 
        value = atof(buffer);
    }
    else {
        printf("Get sensor value failed!\n");
    }

    pthread_mutex_unlock(&socket_mut);

    return value;
}

void set_actuator(float value, char *actuator) {

    pthread_mutex_lock(&socket_mut);
	
    char buffer[MAX_BUFFER_SIZE];
    char value_buffer[30];
    int received_size = 0;
    float confirm_value = 0;

    sprintf(value_buffer, "%f", value); 

    memcpy(buffer, actuator, sizeof(actuator));
    strcat(buffer, value_buffer); 
    
    send_message(buffer);
    received_size = receive_message(buffer);

    pthread_mutex_unlock(&socket_mut);

    //if(received_size > 0) {
    //    buffer[received_size] = '\0';
    //    memcpy(buffer, buffer+3, received_size+1-3); 
    //    confirm_value = atof(buffer);
    //}
    //if(value != confirm_value) {
    //    printf("Server did not receive the correct command!\n");
    //}
}

/** \} End of controller group */