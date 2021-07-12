/**
 * \brief Logger definitions.
 * 
 * \date 2021/08/09
 * 
 * \defgroup logger Logger
 * \ingroup src
 * \{
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#define FILE_BUFFER_SIZE        1000

void logger_set_entry(void);
void logger_get_entry(void);
int logger_save_file(void);

#endif /* LOGGER_H_ */

/** \} End of logger group */