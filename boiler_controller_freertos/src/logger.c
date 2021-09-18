/**
 * \brief Logger implementation.
 * 
 * \date 2021/08/09
 * 
 * \addtogroup logger
 * \{
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#include "../inc/logger.h"

char log_buffer_0[FILE_BUFFER_SIZE];
char log_buffer_1[FILE_BUFFER_SIZE];

int which_in_use = 0;
int which_to_save = -1;
int sessions_logged = 0;

/* Mutex handler */
pthread_mutex_t buffer_mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_cond = PTHREAD_COND_INITIALIZER;

void logger_init(void) {

    /* Create file with name report (overwrite previous). */
    FILE *report = fopen("report/report.txt", "w");
    fclose(report);
}

void logger_add_entry(char *entry, int entry_size, bool finish_session) {

    int size = 0;
    char buffer[100];
    struct timespec time;
    
    /* Get the current system time */
    clock_gettime(CLOCK_MONOTONIC, &time);

    size = sprintf(buffer, "[%ld:%ld]: ", time.tv_sec, time.tv_nsec);
    strcat(buffer, entry);
    strcat(buffer, "\n");
    
    pthread_mutex_lock(&buffer_mut);
    
    if(which_in_use == 0) {
        strcat(log_buffer_0, buffer);
        if (finish_session == true) {
            strcat(log_buffer_0, "\n");
            sessions_logged++;
        }
    }
    else {
        strcat(log_buffer_1, buffer);
        if (finish_session == true) {
            strcat(log_buffer_1, "\n");
            sessions_logged++;
        }
    }

    if(sessions_logged >= 10) {
        which_to_save = which_in_use;
        which_in_use = (which_in_use+1)%2;
        sessions_logged = 0;
        pthread_cond_signal(&buffer_cond);
    }

    pthread_mutex_unlock(&buffer_mut);
}

int logger_save_file(void) {

    /* Create file pointer. */
    FILE *report = fopen("report/report.txt", "a");

    /* Check if everything is ok. */
    if(!report) {
        printf("File opening failed!\n");
        return -1;
    }

    /* Write the report file with the log buffer */
    
    pthread_mutex_lock(&buffer_mut);
    
    while(which_to_save == -1) {
        pthread_cond_wait(&buffer_cond, &buffer_mut);
    }

    if(which_to_save == 0) {
        fprintf(report, "%s", log_buffer_0);
        /* Clear array */
        memset(log_buffer_0, 0, FILE_BUFFER_SIZE);
    }
    else {
        fprintf(report, "%s", log_buffer_1);
        /* Clear array */
        memset(log_buffer_1, 0, FILE_BUFFER_SIZE);
    }

    which_to_save = -1;

    pthread_mutex_unlock(&buffer_mut);

    fclose(report);
    return 0;
}



/** \} End of logger group */