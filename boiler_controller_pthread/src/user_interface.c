/**
 * \brief User interface implementation.
 * 
 * \date 2021/08/22
 * 
 * \addtogroup user_interface
 * \{
 */

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>

#include "controller.h"
#include "logger.h"
#include "user_interface.h"

/* Mutex handler */
pthread_mutex_t display_mut = PTHREAD_MUTEX_INITIALIZER;

void user_interface_init(void) {

    printf("\nWelcome to the boiler controller!\n\n");

	printf("The controller menu has the following options:\n");
	printf("[0] enter [ref_temp] enter   -> to select the controller temperature set point \n");
	printf("[1] enter [ref_height] enter -> to select the controller water height set point \n");    
    printf("[s] -> to execute a clean exit procedure \n\n");
}

void user_input_handler(void) {
	
	char menu_input;
	float value_input;

	scanf("%s", &menu_input);

	if(strcmp(&menu_input, TEMPERATURE_SET_POINT_COMMAND) == 0) {
		scanf("%f", &value_input);
		/* Call temp set point update */
	}

	if(strcmp(&menu_input, HEIGHT_SET_POINT_COMMAND) == 0) {
		scanf("%f", &value_input);
		/* Call height set point update */
	}

	if(strcmp(&menu_input, STOP_COMMAND) == 0) {
		/* Call clean termination procedure */
	}
}

void user_output_handler(void) {
    
	char buffer[100];
	int size = 0;

	/* Save log outputs */
	size = sprintf(buffer, "ROOM_TEMP_SENSOR = %f", get_sensor(ROOM_TEMP_SENSOR));
	logger_add_entry(buffer, size, false);
	memset(buffer, 0, 100);

	size = sprintf(buffer, "BOILER_WATER_TEMP_SENSOR = %f", get_sensor(BOILER_WATER_TEMP_SENSOR));
	logger_add_entry(buffer, size, false);
	memset(buffer, 0, 100);

	size = sprintf(buffer, "INPUT_SUPPLY_WATER_TEMP_SENSOR = %f", get_sensor(INPUT_SUPPLY_WATER_TEMP_SENSOR));
	logger_add_entry(buffer, size, false);
	memset(buffer, 0, 100);

	size = sprintf(buffer, "OUTPUT_DEMAND_WATER_FLOW_SENSOR = %f", get_sensor(OUTPUT_DEMAND_WATER_FLOW_SENSOR));
	logger_add_entry(buffer, size, false);
	memset(buffer, 0, 100);

	size = sprintf(buffer, "BOILER_WATER_HEIGHT_SENSOR = %f", get_sensor(BOILER_WATER_HEIGHT_SENSOR));
	logger_add_entry(buffer, size, false);
	memset(buffer, 0, 100);

	size = sprintf(buffer, "INPUT_SUPPLY_WATER_FLOW_ACTUATOR = %f", get_sensor(INPUT_SUPPLY_WATER_FLOW_ACTUATOR));
	logger_add_entry(buffer, size, false);
	memset(buffer, 0, 100);

	size = sprintf(buffer, "INPUT_SUPPLY_HOT_WATER_FLOW_ACTUATOR = %f", get_sensor(INPUT_SUPPLY_HOT_WATER_FLOW_ACTUATOR));
	logger_add_entry(buffer, size, false);
	memset(buffer, 0, 100);

	size = sprintf(buffer, "INPUT_HEAT_FLOW_ACTUATOR = %f", get_sensor(INPUT_HEAT_FLOW_ACTUATOR));
	logger_add_entry(buffer, size, false);
	memset(buffer, 0, 100);

	size = sprintf(buffer, "OUTPUT_DUMP_WATER_FLOW_ACTUATOR = %f", get_sensor(OUTPUT_DUMP_WATER_FLOW_ACTUATOR));
	logger_add_entry(buffer, size, true);
	memset(buffer, 0, 100);


    /* Get the current system time */
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);

    pthread_mutex_lock(&display_mut);

    /* Print user outputs */
    printf(ANSI_COLOR_GREEN "[%ld:%ld]: " ANSI_COLOR_RESET, time.tv_sec, time.tv_nsec);
    printf("Room temperature: ");
    printf(ANSI_COLOR_BLUE "%f\n" ANSI_COLOR_RESET, get_sensor(ROOM_TEMP_SENSOR));

    printf(ANSI_COLOR_GREEN "[%ld:%ld]: " ANSI_COLOR_RESET, time.tv_sec, time.tv_nsec);
    printf("Boiler water temperature: ");
    printf(ANSI_COLOR_RED "%f\n" ANSI_COLOR_RESET, get_sensor(BOILER_WATER_TEMP_SENSOR));

    printf(ANSI_COLOR_GREEN "[%ld:%ld]: " ANSI_COLOR_RESET, time.tv_sec, time.tv_nsec);
    printf("Boiler water height: ");
    printf(ANSI_COLOR_YELLOW "%f\n\n" ANSI_COLOR_RESET, get_sensor(BOILER_WATER_HEIGHT_SENSOR));

    pthread_mutex_unlock(&display_mut);
}

/** \} End of user_interface group */