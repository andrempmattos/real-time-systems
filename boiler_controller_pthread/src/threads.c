/**
 * \brief Threads implementation.
 * 
 * \date 2021/08/22
 * 
 * \addtogroup threads
 * \{
 */

#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#include "threads.h"
#include "timer.h"
#include "controller.h"
#include "logger.h"
#include "user_interface.h"

/* Threads functions */
void thread_temp_controller(void);
void thread_level_controller(void);
void thread_warning_alarm(void);
void thread_user_input(void);
void thread_user_info(void);
void thread_session_logger(void);

/* Threads handlers */
pthread_t thread_temp_controller_handler;
pthread_t thread_level_controller_handler;
pthread_t thread_warning_alarm_handler;
pthread_t thread_user_input_handler;
pthread_t thread_user_info_handler;
pthread_t thread_session_logger_handler;

void threads_init(void) {

    int status = 0;

    status |= pthread_create(&thread_temp_controller_handler, NULL, (void *)thread_temp_controller, NULL);
    status |= pthread_create(&thread_level_controller_handler, NULL, (void *)thread_level_controller, NULL);
    status |= pthread_create(&thread_warning_alarm_handler, NULL, (void *)thread_warning_alarm, NULL);
    status |= pthread_create(&thread_user_input_handler, NULL, (void *)thread_user_input, NULL);
    status |= pthread_create(&thread_user_info_handler, NULL, (void *)thread_user_info, NULL);
    status |= pthread_create(&thread_session_logger_handler, NULL, (void *)thread_session_logger, NULL);

    if (status != 0) {
        printf("CRITICAL: Error creating threads!\n");
    }
}

void thread_temp_controller(void) {

    /* Variables to */
    float boiler_water_temp, input_water_temp;

    /* Variables to hold the controller structures for each control loop */
    float control_na, control_q, control_ni;

    /* Boiler temperature controllers initialization */
    controller_t na_control = controller_init("Na", "temperature", 10.0, 0.0, 500.0, 0.5);
    controller_t ni_control = controller_init("Ni", "temperature", 100.0, 0.0, -500.0, 0.5);
    controller_t q_control = controller_init("Q", "temperature", 1000000.0, 0.0, 10000000.0, 0.5);

    while(1) {

        /* Get sensor values */
        boiler_water_temp = get_sensor(BOILER_WATER_TEMP_SENSOR);
        input_water_temp = get_sensor(INPUT_SUPPLY_WATER_TEMP_SENSOR);

        /* Get control action */
        control_na = pi_algorithm(&na_control, TEMP_SET_POINT, boiler_water_temp);
        control_q = pi_algorithm(&q_control, TEMP_SET_POINT, boiler_water_temp);
        if(input_water_temp < boiler_water_temp){
            control_ni = pi_algorithm(&ni_control, TEMP_SET_POINT, boiler_water_temp);
        } else {
            control_ni = 0;
        }

        /* Set actuators based on the control action */
        set_actuator(control_na, INPUT_SUPPLY_HOT_WATER_FLOW_ACTUATOR);
        set_actuator(control_q, INPUT_HEAT_FLOW_ACTUATOR);
        set_actuator(control_ni, INPUT_SUPPLY_WATER_FLOW_ACTUATOR);
        
        timer_delay(CONVERT_MS_TO_NS(THREAD_TEMP_CONTROLLER_PERIOD_MS));
    }

}

void thread_level_controller(void) {

    /* Initialization */
    float boiler_water_height;

    /* Variables to hold the controller structures for each control loop */
    float control_ni, control_nf;

    /* Boiler temperature controllers initialization */
    controller_t ni_control = controller_init("Na", "height", 100.0, 0.0, 500.0, 0.1);
    controller_t nf_control = controller_init("Nf", "height", 100.0, 0.0, -500.0, 0.1);

    while(1) {
        
        /* Get sensor values */
        boiler_water_height = get_sensor(BOILER_WATER_HEIGHT_SENSOR);
        printf("Boiler water height test: %f \n", boiler_water_height);

        /* Get control action */
        control_ni = pi_algorithm(&ni_control, HEIGHT_SET_POINT, boiler_water_height);
        control_nf = pi_algorithm(&nf_control, HEIGHT_SET_POINT, boiler_water_height);

        /* Set actuators based on the control action */
        set_actuator(control_ni, INPUT_SUPPLY_WATER_FLOW_ACTUATOR);
        set_actuator(control_nf, OUTPUT_DUMP_WATER_FLOW_ACTUATOR);

        timer_delay(CONVERT_MS_TO_NS(THREAD_LEVEL_CONTROLLER_PERIOD_MS));
    }
}

void thread_warning_alarm(void) {

    bool alert_sent = false;
    
    float init_temp   = get_sensor(BOILER_WATER_TEMP_SENSOR);
    float init_height = get_sensor(BOILER_WATER_HEIGHT_SENSOR);

    if((init_temp > 70) || (init_temp < 0)) {
        /* Call critical temp alert/routine */
    }

    if((init_height > 5) || (init_height < 0.1)) {
        /* Call critical height alert/routine */
    }

    while(1) {

        if(get_sensor(BOILER_WATER_TEMP_SENSOR) >= 30) {
            if(!alert_sent) {
                /* Call warning temp alert */
                alert_sent = true;
            }
        }
        else {
            alert_sent = false;
        }

        timer_delay(CONVERT_MS_TO_NS(THREAD_WARNING_ALERT_PERIOD_MS));
    }
}

void thread_user_input(void) {

    while(1) {
        user_input_handler();
    }
}

void thread_user_info(void) {
    
    while(1) {
        user_output_handler();
        timer_delay(CONVERT_MS_TO_NS(THREAD_USER_INFO_PERIOD_MS));
    }
}

void thread_session_logger(void) {
    
    /* Initialization */

    while(1) {
        timer_delay(CONVERT_MS_TO_NS(THREAD_SESSION_LOGGER_PERIOD_MS));
    }
}

 

/** \} End of threads group */