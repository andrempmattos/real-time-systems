/**
 * \brief Main loop implementation.
 * 
 * \date 2021/08/07
 * 
 * \addtogroup main
 * \{
 */

#include <stdio.h>
#include <pthread.h>

#include "controller.h"
#include "udp_client.h"
#include "timer.h"
#include "logger.h"

void system_init(void);
void thread_temp_controller(void);
void thread_level_controller(void);
void thread_warning_alarm(void);
void thread_user_input(void);
void thread_user_info(void);
void thread_logger_file(void);

/* Threads handlers */
pthread_t thread_temp_controller_handler;
pthread_t thread_level_controller_handler;
pthread_t thread_warning_alarm_handler;
pthread_t thread_user_input_handler;
pthread_t thread_user_info_handler;
pthread_t thread_logger_file_handler;

/* Cycle counter variable to keep track of periodic events */
int cycle;

/* Variables to */
float boiler_water_temp, input_water_temp;

/* Variables to hold the controller structures for each control loop */
float control_na, control_q, control_ni;

/* Boiler controllers initialization */
controller_t na_control;
controller_t ni_control;
controller_t q_control;

void main(void) {

	system_init();

	/* Main loop (cyclic executive) */
	while(1) {

		/* 30ms, each cycle: Periodically run the controllers */
		thread_temp_controller();
		thread_level_controller();

		/* 1s, each TICKS_TO_1_SECOND cycles: Periodically prints user information */
		if(!(cycle%TICKS_TO_1_SECOND)) {
			thread_user_info();
		}

		/* 30s, after buffer size achieved: Periodically save the logger session */
		if((cycle%FILE_BUFFER_SIZE+1) >= FILE_BUFFER_SIZE) {
			thread_logger_file();
		}	

		/* Increment cycle counter variable */
		cycle++;

		/* Delay until next system loop cycle (system tick: 30ms) */
		timer_delay(SYS_TICK);
	}
}

void system_init(void) {

	pthread_create(&thread_temp_controller_handler, NULL, (void *)thread_temp_controller, NULL);
	pthread_create(&thread_level_controller_handler, NULL, (void *)thread_level_controller, NULL);
	pthread_create(&thread_warning_alarm_handler, NULL, (void *)thread_warning_alarm, NULL);
	pthread_create(&thread_user_input_handler, NULL, (void *)thread_user_input, NULL);
	pthread_create(&thread_user_info_handler, NULL, (void *)thread_user_info, NULL);
	pthread_create(&thread_logger_file_handler, NULL, (void *)thread_logger_file, NULL);

	/* Boiler controllers initialization */
	na_control = controller_init("Na", "temperature", 10.0, 0.0, 500.0, 0.5);
	ni_control = controller_init("Ni", "temperature", 100.0, 0.0, -500.0, 0.5);
	q_control = controller_init("Q", "temperature", 1000000.0, 0.0, 10000000.0, 0.5);

	/* UDP interface initialization */
	udp_init(SERVER_ADDRESS, SERVER_PORT);

	/* Timer initialization */
	timer_init();
}

void thread_temp_controller(void) {

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
}

void thread_level_controller(void) {

}

void thread_warning_alarm(void) {

}

void thread_user_input(void) {

}

void thread_user_info(void) {
	printf("Loop cycle: %d \n", cycle/TICKS_TO_1_SECOND);
	printf("Boiler water temperature: %f \n", boiler_water_temp);
	printf("Boiler water height: %f \n", get_sensor(BOILER_WATER_HEIGHT_SENSOR));
}

void thread_logger_file(void) {

}

/** \} End of main group */