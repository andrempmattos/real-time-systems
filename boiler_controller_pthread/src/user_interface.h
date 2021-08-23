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

#define TEMPERATURE_SET_POINT_COMMAND
#define HEIGHT_SET_POINT_COMMAND
#define STOP_COMMAND
                                            
void user_interface_init(void);
void user_input_handler(void);
void user_output_handler(void);

#endif /* USER_INTERFACE_H_ */

/** \} End of user_interface group */