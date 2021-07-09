/**
 * \brief Main loop implementation.
 * 
 * \date 2021/08/07
 * 
 * \addtogroup main
 * \{
 */

#include <stdio.h>

#include "controller.h"
#include "udp_client.h"
#include "timer.h"

#define TEMP_SET_POINT		25

int main(int argc, char const *argv[]) {
	
	int cycle = 0;

	float temp;
	float ti;
	float control_na;
	float control_q;
	float control_ni;

	/* Boiler controllers initialization */
	controller_t na_control = controller_init("Na", "temperature", 10.0, 0.0, 500.0, 0.5);
	controller_t ni_control = controller_init("Ni", "temperature", 100.0, 0.0, -500.0, 0.5);
	controller_t q_control = controller_init("Q", "temperature", 1000000.0, 0.0, 10000000.0, 0.5);

	/* UDP interface initialization */
	udp_init(SERVER_ADDRESS, SERVER_PORT);

	/* Timer initialization */
	timer_init();

	/* Main loop (cyclic executive) */
	while(1) {
		
		printf("Loop cycle: %d \n", cycle++);	

		/* Get sensor values */
		temp = get_sensor(BOILER_WATER_TEMP_SENSOR);
		ti = get_sensor(INPUT_SUPPLY_WATER_TEMP_SENSOR);

		/* Get control action */
		control_na = pi_algorithm(&na_control, TEMP_SET_POINT, temp);
		control_q = pi_algorithm(&q_control, TEMP_SET_POINT, temp);
		if(ti < temp){
			control_ni = pi_algorithm(&ni_control, TEMP_SET_POINT, temp);
		} else {
			control_ni = 0;
		}

		/* Set actuators based on the control action */
		set_actuator(control_na, INPUT_SUPPLY_HOT_WATER_FLOW_ACTUATOR);
		set_actuator(control_q, INPUT_HEAT_FLOW_ACTUATOR);
		set_actuator(control_ni, INPUT_SUPPLY_WATER_FLOW_ACTUATOR);

		/* Delay until next system loop cycle (system tick) */
		timer_delay(SYS_TICK);
	}
}

/** \} End of main group */