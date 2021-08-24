/**
 * \brief User interface definitions.
 * 
 * \date 2021/08/22
 * 
 * \defgroup user_interface User interface
 * \ingroup src
 * \{
 */

#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#define TEMPERATURE_SET_POINT_COMMAND   "0"
#define HEIGHT_SET_POINT_COMMAND        "1"
#define STOP_COMMAND                    "s" 

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

extern pthread_mutex_t display_mut;
                                            
void user_interface_init(void);
void user_input_handler(void);
void user_output_handler(void);

#endif /* USER_INTERFACE_H_ */

/** \} End of user_interface group */