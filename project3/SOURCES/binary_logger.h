/************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 04/16/2017
*
* File : binary_logger.h
* Description : Header file for binary logger
*               -create_log_item()
*               -log_item()
*               -destroy_log_item()
*************************************************/

#ifndef SOURCES_BINARY_LOGGER_H_
#define SOURCES_BINARY_LOGGER_H_

#define NOERROR (0)

/*Enums to be used by Binary Logger*/
typedef enum Log_ID_Types{
	RTC_INITIALIZED = 1,
	LOGGER_INITIALIZED,
	GPIO_INITIALIZED,
	SPI_INITIALIZED,
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
	DATA_ANALYSIS_COMPLETED,
	HEARTBEAT
    }Log_ID;

/******************************************
* Binary Logger Structure
* logID : Indicates the log type
* LogLength : Gives the length of payload
* in bytes
* *Payload : Pointer to the payload data
******************************************/
typedef struct Log_struct{
     uint16_t  logID;
     uint32_t  Timestamp;
     uint8_t   LogLength;
     uint8_t * Payload;
}Log_t;

Log_t *system_log;

/*********************************************************************
* create_log_item() - Function to allocate memory in heap to the
*             	      Binary Log structure
* Log_t *(return)- Pointer of type Log_t which points to the location
*                  in heap memory where structure is created.
*********************************************************************/
Log_t * create_log_item();

/**********************************************************************
* log_item() - Function to call the logger functions which push
*	       the binary log data to serial output
* Log_t * struct_ptr - Structure pointer which stores the log data that
*		       needs to be logged on the serial output
* uint8_t(return)- Return NOERROR when all the data is logged
**********************************************************************/
uint8_t log_item(Log_t * struct_ptr);

/**********************************************************************
* destroy_log_item() - Function to free the structure memory from heap
* Log_t * struct_ptr - Pointer of the structure that needs to be freed
* uint8_t(return)- Return NOERROR when structure is freed from memory
**********************************************************************/
uint8_t destroy_log_item(Log_t * struct_ptr);

#endif /* SOURCES_BINARY_LOGGER_H_ */
