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

int main(int argc, char const *argv[]) {
	
	int cycle = 0;
	char buffer[MAX_BUFFER_SIZE];
	int received_size = 0;
	float temp;
	float ti;
	float control_na;
	float control_q;
	float control_ni;

	float temp_ref = 70;

	/* Boiler controller initialization */
	struct controller na_control = controller_init("Na", "temperature", 10.0, 0.0, 500.0, 0.5);
	struct controller ni_control = controller_init("Ni", "temperature", 100.0, 0.0, -500.0, 0.5);
	struct controller q_control = controller_init("Q", "temperature", 1000000.0, 0.0, 10000000.0, 0.5);

	/* UDP interface initialization */
	udp_init(SERVER_ADDRESS, SERVER_PORT);

	/* Timer initialization */
	timer_init();

	/* Main loop (cyclic executive) */
	while(1) {
		
		printf("Loop cycle! \t %d \n", cycle++);

		/********* Do stuff */
		send_message("st-0");
		received_size = receive_message(buffer);
		
		temp = get_sensor("st-0");
		ti = get_sensor("sti0");

		control_na = pi_algorithm(&na_control, temp_ref, temp);
		control_q = pi_algorithm(&q_control, temp_ref, temp);

		if(ti < temp){
			control_ni = pi_algorithm(&ni_control, temp_ref, temp);
		} else {
			control_ni = 0;
		}

		set_actuator(control_na, "ana");
		set_actuator(control_q, "aq");
		set_actuator(control_ni, "ani");
	
		if (received_size > 0) {
			buffer[received_size] = '\0';
			printf("Received message of %d bytes >>> %s\n\n", received_size, buffer);
		}
		else {
			printf("Receive message failed!\n\n");
		}
		/********* Finished stuff */

		/* Delay until next system loop cycle (system tick) */
		timer_delay(SYS_TICK);
	}
}

/** \} End of main group */