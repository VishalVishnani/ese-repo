/*
 * binary_logger.h
 *
 *  Created on: Mar 3, 2017
 *      Author: viga7710
 */

#ifndef SOURCES_BINARY_LOGGER_H_
#define SOURCES_BINARY_LOGGER_H_

#define NOERROR 0

typedef enum Log_ID_Types{
	LOGGER_INITIALIZED = 1,
	GPIO_INITIALIZED,
	SYSTEM_INITIALIZED,
    SYSTEM_HALTED,
	INFO,
	WARNING,
	LOG_ERROR,
    DATA_RECEIVED,
	DATA_ANALYSIS_STARTED,
	DATA_ALPHA_COUNT,
	NUMERIC_COUNT,
	DATA_PUNCTUATION_COUNT,
	DATA_MISC_COUNT,
	DATA_ANALYSIS_COMPLETED
    }Log_ID;

typedef struct Log_struct{
     uint16_t  logID;
     uint8_t  LogLength;
     uint16_t  Payload;
}Log_t;

Log_t *system_log;

Log_t * create_log_item(); //- Create a log item in the heap
uint8_t log_item(Log_t * struct_ptr); //- Logs a log item to the serial output. Takes a log structure pointer
uint8_t destroy_log_item(Log_t * struct_ptr); //- deallocates log from heap memory

#endif /* SOURCES_BINARY_LOGGER_H_ */
