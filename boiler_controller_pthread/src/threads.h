/**
 * \brief Threads definitions.
 * 
 * \date 2021/08/22
 * 
 * \defgroup threads Threads
 * \ingroup src
 * \{
 */

#ifndef THREADS_H_
#define THREADS_H_

#define THREAD_TEMP_CONTROLLER_PERIOD_MS        50      /**< Temperature controller thread sleep period in ms. */            
#define THREAD_LEVEL_CONTROLLER_PERIOD_MS       70      /**< Water level controller thread sleep period in ms. */     
#define THREAD_WARNING_ALERT_PERIOD_MS          10      /**< Warning alert thread sleep period in ms. */ 
#define THREAD_USER_INFO_PERIOD_MS              1000    /**< User info thread sleep period in ms. */
#define THREAD_SESSION_LOGGER_PERIOD_MS         10000   /**< Temperature controller thread sleep period in ms. */   

//#define THREADS_INIT_DELAY_MS                   100     /**< Threads init delay period in ms. */     

void threads_init(void);

extern pthread_t thread_user_input_handler;                                          


#endif /* THREADS_H_ */

/** \} End of threads group */