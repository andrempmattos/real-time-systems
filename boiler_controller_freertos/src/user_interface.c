/**
 * \brief User interface implementation.
 * 
 * \date 2021/08/22
 * 
 * \addtogroup user_interface
 * \{
 */

#include <stdbool.h>
#include <FreeRTOS.h>
#include <task.h>

#include "../inc/controller.h"
#include "../inc/console.h"
#include "../inc/user_interface.h"
#include "../inc/tasks.h"

void user_interface_init(void) {

	console_print("\n");
    console_print("\n");
    console_print(" ___  ___  _  _    ___  ___    ___  ___  _ _  ___  ___  ___  _    _    ___  ___ \n");
    console_print("| . ]| . || || |  | __]| . \\  |  _]| . || \\ ||_ _|| . \\| . || |  | |  | __]| . \\ \n");
    console_print("| . \\| | || || |_ | _] |   /  | [__| | ||   | | | |   /| | || |_ | |_ | _] |   / \n");
    console_print("|___/`___'|_||___||___]|_\\_\\  `___/`___'|_\\_| |_| |_\\_\\`___'|___||___||___]|_\\_\\ \n");
    console_print("\n");

    console_print(ANSI_COLOR_GREEN "\nWelcome to the boiler controller!\n\n" ANSI_COLOR_RESET);
}

void user_output_handler(void) {

    /* Print user outputs */
    console_print(
        ANSI_COLOR_GREEN "[%lu]: " ANSI_COLOR_RESET 
        "Room temperature: " 
        ANSI_COLOR_BLUE  "%f\n" ANSI_COLOR_RESET, 
        xTaskGetTickCount(), 
        get_sensor(ROOM_TEMP_SENSOR)
    );

    console_print(
        ANSI_COLOR_GREEN "[%lu]: " ANSI_COLOR_RESET 
        "Boiler water temperature: " 
        ANSI_COLOR_RED  "%f\n" ANSI_COLOR_RESET, 
        xTaskGetTickCount(), 
        get_sensor(BOILER_WATER_TEMP_SENSOR)
    );

    console_print(
        ANSI_COLOR_GREEN "[%lu]: " ANSI_COLOR_RESET 
        "Boiler water height: " 
        ANSI_COLOR_YELLOW  "%f\n" ANSI_COLOR_RESET, 
        xTaskGetTickCount(), 
        get_sensor(BOILER_WATER_HEIGHT_SENSOR)
    );

    console_print(
        ANSI_COLOR_GREEN "[%lu]: " ANSI_COLOR_RESET 
        "Boiler water average temperature: " 
        ANSI_COLOR_GREEN  "%f\n" ANSI_COLOR_RESET, 
        xTaskGetTickCount(), 
        avg_temp
    );

    if(close_temp_arrived) {
        console_print(
            ANSI_COLOR_GREEN "[%lu]: " ANSI_COLOR_RESET 
            "Time in seconds to arrive in 0.95 of setpoint: " 
            ANSI_COLOR_GREEN  "%lu\n" ANSI_COLOR_RESET, 
            xTaskGetTickCount(), 
            time_to_close_temp
        );
    }
    
    if (alarm_temp) {
        console_print(
            ANSI_COLOR_GREEN "\n[%lu]: " ANSI_COLOR_RESET
            ANSI_COLOR_RED "WARNING: Temperature alarm set!\n\n" ANSI_COLOR_RESET,
            xTaskGetTickCount());
    }
}

/** \} End of user_interface group */