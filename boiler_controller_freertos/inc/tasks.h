/**
 * \brief Tasks definitions.
 * 
 * \date 2021/08/22
 * 
 * \defgroup tasks Tasks
 * \ingroup src
 * \{
 */

#ifndef TASKS_H_
#define TASKS_H_

/* Water temperature controller task parameters */
#define TASK_TEMP_CONTROLLER_NAME           "temp_controller"
#define TASK_TEMP_CONTROLLER_PERIOD_MS      50    /**< Temperature controller task sleep period in ms. */            
#define TASK_TEMP_CONTROLLER_STACK_SIZE     512
#define TASK_TEMP_CONTROLLER_PRIORITY       3

/* Water level controller task parameters */
#define TASK_LEVEL_CONTROLLER_NAME          "level_controller"
#define TASK_LEVEL_CONTROLLER_PERIOD_MS     70    /**< Water level controller task sleep period in ms. */     
#define TASK_LEVEL_CONTROLLER_STACK_SIZE    512
#define TASK_LEVEL_CONTROLLER_PRIORITY      3

/* Temperature warning alert task parameters */
#define TASK_WARNING_ALERT_NAME             "warning_alert"
#define TASK_WARNING_ALERT_PERIOD_MS        10    /**< Warning alert task sleep period in ms. */ 
#define TASK_WARNING_ALERT_STACK_SIZE       128
#define TASK_WARNING_ALERT_PRIORITY         5

/* User info task parameters */
#define TASK_USER_INFO_NAME                 "user_info"
#define TASK_USER_INFO_PERIOD_MS            1000  /**< User info task sleep period in ms. */
#define TASK_USER_INFO_STACK_STACK_SIZE     1024
#define TASK_USER_INFO_PRIORITY             2

/* Session logger task parameters */
#define TASK_SESSION_LOGGER_NAME            "session_logger"
#define TASK_SESSION_LOGGER_PERIOD_MS       10000 /**< Session logger task sleep period in ms. */   
#define TASK_SESSION_LOGGER_STACK_SIZE      4096
#define TASK_SESSION_LOGGER_PRIORITY        1



/* Session logger task parameters */
#define TASK_TEMP_READER_NAME               "session_logger"
#define TASK_TEMP_READER_PERIOD_MS          10 /**< Session logger task sleep period in ms. */   
#define TASK_TEMP_READER_STACK_SIZE         512
#define TASK_TEMP_READER_PRIORITY           4

//#define TASKS_INIT_DELAY_MS               100     /**< Tasks init delay period in ms. */     

extern float avg_temp;
extern TickType_t time_to_close_temp;
extern int close_temp_arrived;
extern int alarm_temp;

void create_tasks(void);

#endif /* TASKS_H_ */

/** \} End of tasks group */