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

    /* Variable to hold the water temperature */
    float boiler_water_temp;

    /* Variables to hold the controller structures for each control loop */
    float control_na, control_q;

    /* Boiler temperature controllers initialization */
    controller_t na_control = controller_init("Na", "temperature", 10.0, 0.0, 500.0, 0.5);
    controller_t q_control = controller_init("Q", "temperature", 1000000.0, 0.0, 10000000.0, 0.5);

    while(1) {

        /* Get sensor values */
        boiler_water_temp = get_sensor(BOILER_WATER_TEMP_SENSOR);

        /* Get control action */
        pthread_mutex_lock(&user_mut);
        control_na = pi_algorithm(&na_control, temp_set_point, boiler_water_temp);
        control_q = pi_algorithm(&q_control, temp_set_point, boiler_water_temp);
        pthread_mutex_unlock(&user_mut);

        /* Set actuators based on the control action */
        set_actuator(control_na, INPUT_SUPPLY_HOT_WATER_FLOW_ACTUATOR);
        set_actuator(control_q, INPUT_HEAT_FLOW_ACTUATOR);
        
        timer_delay(CONVERT_MS_TO_NS(THREAD_TEMP_CONTROLLER_PERIOD_MS));
    }
}

void thread_level_controller(void) {

    /* Variables to hold the water height and temp */
    float boiler_water_height, boiler_water_temp;

    /* Variables to hold the controller structures for each control loop */
    float control_ni, control_nf;

    /* Boiler temperature controllers initialization */
    controller_t ni_control = controller_init("Na", "height", 100.0, 0.0, 500.0, 0.1);
    controller_t nf_control = controller_init("Nf", "height", 100.0, 0.0, -500.0, 0.1);

    while(1) {
        
        /* Get sensor values */
        boiler_water_height = get_sensor(BOILER_WATER_HEIGHT_SENSOR);
        boiler_water_temp = get_sensor(BOILER_WATER_TEMP_SENSOR);

        /* Get control action */
        pthread_mutex_lock(&user_mut);
        control_ni = pi_algorithm(&ni_control, height_set_point, boiler_water_height);
        control_nf = pi_algorithm(&nf_control, height_set_point, boiler_water_height);
        pthread_mutex_unlock(&user_mut);

        /* Set actuators based on the control action */
        if (boiler_water_temp > temp_set_point) {
            set_actuator(10.0, INPUT_SUPPLY_WATER_FLOW_ACTUATOR);
            set_actuator(10.0, OUTPUT_DUMP_WATER_FLOW_ACTUATOR);
        } else {
            set_actuator(control_ni, INPUT_SUPPLY_WATER_FLOW_ACTUATOR);
            set_actuator(control_nf, OUTPUT_DUMP_WATER_FLOW_ACTUATOR);
        }
        

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
                pthread_mutex_lock(&display_mut);
                printf(ANSI_COLOR_RED "\n\nWARNING: Temperature alarm set!\n\n" ANSI_COLOR_RESET);
                pthread_mutex_unlock(&display_mut);
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
    
    /* Logger initialization */
    logger_init();

    while(1) {
        logger_save_file();
        timer_delay(CONVERT_MS_TO_NS(THREAD_SESSION_LOGGER_PERIOD_MS));
    }
}

 

/** \} End of threads group */