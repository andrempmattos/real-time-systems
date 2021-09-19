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

#define FILE_BUFFER_SIZE        10000

void logger_init(void);
void logger_add_entry(char *entry, int entry_size);
int logger_save_file(void);

#endif /* LOGGER_H_ */

/** \} End of logger group */