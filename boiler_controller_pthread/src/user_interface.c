/**
 * \brief User interface implementation.
 * 
 * \date 2021/08/22
 * 
 * \addtogroup user_interface
 * \{
 */

#include <stdio.h>

#include "controller.h"
#include "user_interface.h"


void user_interface_init(void) {

    printf("Welcome to the boiler controller!\n\n");

	printf("The controller menu has the following options:\n");
	printf("[0] enter [ref_temp] enter   -> to select the controller temperature set point \n");
	printf("[1] enter [ref_height] enter -> to select the controller water height set point \n");    
    printf("[s] -> to execute a clean exit procedure \n");
}

void user_input_handler(void) {
	char menu_input;
	float value_input;

	scanf("%s", menu_input);

	switch(menu_input) {
		case TEMPERATURE_SET_POINT_COMMAND:
			scanf("%f", value_input);
			/* Call temp set point update */			
			break;
		case HEIGHT_SET_POINT_COMMAND:
			scanf("%f", value_input);
			/* Call height set point update */
			break;
		case STOP_COMMAND:
			/* Call clean termination procedure */
			break;
	}
}

void user_output_handler(void) {

    printf("Boiler water temperature: %f \n", get_sensor(BOILER_WATER_TEMP_SENSOR));
    printf("Boiler water height: %f \n", get_sensor(BOILER_WATER_HEIGHT_SENSOR)); 
}

/** \} End of user_interface group */