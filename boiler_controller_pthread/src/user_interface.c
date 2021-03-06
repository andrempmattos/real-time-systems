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
pthread_mutex_t user_mut = PTHREAD_MUTEX_INITIALIZER;

void user_interface_init(void) {

	printf("\n");
    printf("\n");
    printf(" ___  ___  _  _    ___  ___    ___  ___  _ _  ___  ___  ___  _    _    ___  ___ \n");
    printf("| . ]| . || || |  | __]| . \\  |  _]| . || \\ ||_ _|| . \\| . || |  | |  | __]| . \\ \n");
    printf("| . \\| | || || |_ | _] |   /  | [__| | ||   | | | |   /| | || |_ | |_ | _] |   / \n");
    printf("|___/`___'|_||___||___]|_\\_\\  `___/`___'|_\\_| |_| |_\\_\\`___'|___||___||___]|_\\_\\ \n");
    printf("\n");

    printf(ANSI_COLOR_GREEN "\nWelcome to the boiler controller!\n\n" ANSI_COLOR_RESET);

	printf("The controller menu has the following options:\n");
	
	printf(ANSI_COLOR_RED "[0] " ANSI_COLOR_RESET);
	printf("enter ");
	printf(ANSI_COLOR_RED "[ref_temp] " ANSI_COLOR_RESET);
	printf("enter   ");
	printf("-> to select the controller temperature set point \n");

	printf(ANSI_COLOR_YELLOW "[1] " ANSI_COLOR_RESET);
	printf("enter ");
	printf(ANSI_COLOR_YELLOW "[ref_height] " ANSI_COLOR_RESET);
	printf("enter ");    
    printf("-> to select the controller water height set point \n");
    
    printf(ANSI_COLOR_BLUE "[s] " ANSI_COLOR_RESET);
    printf("enter ");
    printf("-> to execute a clean exit procedure \n\n");
}

void user_input_handler(void) {
	
	char menu_input;
	float value_input;

	scanf("%s", &menu_input);

	if(strcmp(&menu_input, TEMPERATURE_SET_POINT_COMMAND) == 0) {
		scanf("%f", &value_input);
		/* Call temp set point update */
		pthread_mutex_lock(&display_mut);
		printf(ANSI_COLOR_RED "Temperature set point command sent: %f \n\n" ANSI_COLOR_RESET, value_input);
		pthread_mutex_unlock(&display_mut);
		pthread_mutex_lock(&user_mut);
		temp_set_point = value_input;
		pthread_mutex_unlock(&user_mut);
	}

	if(strcmp(&menu_input, HEIGHT_SET_POINT_COMMAND) == 0) {
		scanf("%f", &value_input);
		/* Call height set point update */
		pthread_mutex_lock(&display_mut);
		printf(ANSI_COLOR_RED "Height set point command sent: %f \n\n" ANSI_COLOR_RESET, value_input);
		pthread_mutex_unlock(&display_mut);
		pthread_mutex_lock(&user_mut);
		height_set_point  = value_input;
		pthread_mutex_unlock(&user_mut);
	}

	if(strcmp(&menu_input, STOP_COMMAND) == 0) {
		/* Call clean termination procedure */
		pthread_exit(0);
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