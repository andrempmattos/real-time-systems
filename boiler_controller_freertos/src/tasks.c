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
#include "../inc/console.h"
#include "../inc/user_interface.h"

/* Task functions */
void task_temp_controller(void *pvParameters);
void task_level_controller(void *pvParameters);
void task_warning_alarm(void *pvParameters);
void task_user_info(void *pvParameters);
void task_session_logger(void *pvParameters);
void task_temp_reader(void *pvParameters);

TaskHandle_t x_temp_controller_handle = NULL;
TaskHandle_t x_level_controller_handle = NULL;
TaskHandle_t x_warning_alarm_handle = NULL;
TaskHandle_t x_user_info_handle = NULL;
TaskHandle_t x_temp_reader_handle = NULL;

void create_tasks(void) {
    xTaskCreate(&task_temp_controller, TASK_TEMP_CONTROLLER_NAME, TASK_TEMP_CONTROLLER_STACK_SIZE, NULL, TASK_TEMP_CONTROLLER_PRIORITY, &x_temp_controller_handle);
    xTaskCreate(&task_level_controller, TASK_LEVEL_CONTROLLER_NAME, TASK_LEVEL_CONTROLLER_STACK_SIZE, NULL, TASK_LEVEL_CONTROLLER_PRIORITY, &x_level_controller_handle);
    xTaskCreate(&task_warning_alarm, TASK_WARNING_ALERT_NAME, TASK_WARNING_ALERT_STACK_SIZE, NULL, TASK_WARNING_ALERT_PRIORITY, &x_warning_alarm_handle);
    xTaskCreate(&task_user_info, TASK_USER_INFO_NAME, TASK_USER_INFO_STACK_STACK_SIZE, NULL, TASK_USER_INFO_PRIORITY, &x_user_info_handle);
    xTaskCreate(&task_temp_reader, TASK_TEMP_READER_NAME, TASK_TEMP_READER_STACK_SIZE, NULL, TASK_TEMP_READER_PRIORITY, &x_temp_reader_handle);
}

float avg_temp = 0;
TickType_t time_to_close_temp;
int close_temp_arrived = 0;
int alarm_temp = 0;

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

    bool alert_sent = false;
    static uint32_t thread_notification;

    while(1) {
        thread_notification = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        if(thread_notification){
            alarm_temp = 1;
        }
    }
}

void task_user_info(void *pvParameters) {

    TickType_t last_cycle = xTaskGetTickCount();
    
    while(1) {
        user_output_handler();
        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_USER_INFO_PERIOD_MS));
    }
}

void task_temp_reader(void *pvParameters) {

    float boiler_water_temp_a;
    TickType_t last_cycle = xTaskGetTickCount(); 
    float arr_last_ten_temp[10] = { 0 };
    int pointer_arr = 0;
    float sum_temp = 0.0;

    while(1) {

        /* Get sensor values */
        boiler_water_temp_a = get_sensor(BOILER_WATER_TEMP_SENSOR);

        if(boiler_water_temp_a >= 30) {
            /* Call temp alert task with notification */
            xTaskNotifyGive(x_warning_alarm_handle);
        } else {
            alarm_temp = 0;
        }
        
        /* Get ten last values and print average */
        if(pointer_arr < 9) {
            arr_last_ten_temp[pointer_arr] = boiler_water_temp_a;
            pointer_arr++;
        } else {
            arr_last_ten_temp[pointer_arr] = boiler_water_temp_a;
            pointer_arr = 0;
        }

        for (int i = 0; i < 10; i++) {
            sum_temp += arr_last_ten_temp[i];
        }
        avg_temp = sum_temp / 10;
        sum_temp = 0;

        if (boiler_water_temp_a >= 0.95*temp_set_point && !close_temp_arrived) {
            time_to_close_temp = last_cycle / 1000;
            close_temp_arrived = 1;
        }

        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_TEMP_READER_PERIOD_MS));
    }
}

/** \} End of threads group */ 
