/**
 * \brief Tasks implementation.
 * 
 * \date 2021/08/22
 * 
 * \addtogroup tasks
 * \{
 */

#include <stdbool.h>
#include <FreeRTOS.h>
#include <task.h>

#include "../inc/tasks.h"
#include "../inc/controller.h"
#include "../inc/logger.h"
#include "../inc/console.h"
#include "../inc/user_interface.h"

/* Task functions */
void task_temp_controller(void *pvParameters);
void task_level_controller(void *pvParameters);
void task_warning_alarm(void *pvParameters);
void task_user_info(void *pvParameters);
void task_session_logger(void *pvParameters);

void create_tasks(void) {
    xTaskCreate(&task_temp_controller, TASK_TEMP_CONTROLLER_NAME, TASK_TEMP_CONTROLLER_STACK_SIZE, NULL, TASK_TEMP_CONTROLLER_PRIORITY, NULL);
    xTaskCreate(&task_level_controller, TASK_LEVEL_CONTROLLER_NAME, TASK_LEVEL_CONTROLLER_STACK_SIZE, NULL, TASK_LEVEL_CONTROLLER_PRIORITY, NULL);
    xTaskCreate(&task_warning_alarm, TASK_WARNING_ALERT_NAME, TASK_WARNING_ALERT_STACK_SIZE, NULL, TASK_WARNING_ALERT_PRIORITY, NULL);
    xTaskCreate(&task_user_info, TASK_USER_INFO_NAME, TASK_USER_INFO_STACK_STACK_SIZE, NULL, TASK_USER_INFO_PRIORITY, NULL);
    xTaskCreate(&task_session_logger, TASK_LEVEL_CONTROLLER_NAME, TASK_LEVEL_CONTROLLER_STACK_SIZE, NULL, TASK_LEVEL_CONTROLLER_PRIORITY, NULL);
}

void task_temp_controller(void *pvParameters) {
    
    TickType_t last_cycle = xTaskGetTickCount();
    
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
        control_na = pi_algorithm(&na_control, temp_set_point, boiler_water_temp);
        control_q = pi_algorithm(&q_control, temp_set_point, boiler_water_temp);

        /* Set actuators based on the control action */
        set_actuator(control_na, INPUT_SUPPLY_HOT_WATER_FLOW_ACTUATOR);
        set_actuator(control_q, INPUT_HEAT_FLOW_ACTUATOR);
        
        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_TEMP_CONTROLLER_PERIOD_MS));
    }
}

void task_level_controller(void *pvParameters) {
    
    TickType_t last_cycle = xTaskGetTickCount();
    
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
        control_ni = pi_algorithm(&ni_control, height_set_point, boiler_water_height);
        control_nf = pi_algorithm(&nf_control, height_set_point, boiler_water_height);

        /* Set actuators based on the control action */
        if (boiler_water_temp > temp_set_point) {
            set_actuator(10.0, INPUT_SUPPLY_WATER_FLOW_ACTUATOR);
            set_actuator(10.0, OUTPUT_DUMP_WATER_FLOW_ACTUATOR);
        } else {
            set_actuator(control_ni, INPUT_SUPPLY_WATER_FLOW_ACTUATOR);
            set_actuator(control_nf, OUTPUT_DUMP_WATER_FLOW_ACTUATOR);
        }
        
        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_LEVEL_CONTROLLER_PERIOD_MS));
    }
}

void task_warning_alarm(void *pvParameters) {
    
    TickType_t last_cycle = xTaskGetTickCount();
    
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
                console_print(ANSI_COLOR_RED "\n\nWARNING: Temperature alarm set!\n\n" ANSI_COLOR_RESET);
                alert_sent = true;
            }
        }
        else {
            alert_sent = false;
        }

        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_WARNING_ALERT_PERIOD_MS));
    }
}

void task_user_info(void *pvParameters) {

    TickType_t last_cycle = xTaskGetTickCount();
    
    while(1) {
        user_output_handler();
        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_USER_INFO_PERIOD_MS));
    }
}

void task_session_logger(void *pvParameters) {
    
    TickType_t last_cycle = xTaskGetTickCount();
    
    /* Logger initialization */
    logger_init();

    while(1) {
        logger_save_file();
        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_SESSION_LOGGER_PERIOD_MS));
    }
}

/** \} End of threads group */ 




 