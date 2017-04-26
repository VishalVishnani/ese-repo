/*************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 03/12/2017
*
* File : logger.h
* Description : Header file for wrapper logger functions
*               -void log_data(uint8_t * data_TX,uint8_t length_TX)
*               -void log_flush(void)
*               -void log_data_BBB(uint8_t * data_TX,uint8_t length_TX)
*		-void log_string(uint8_t * data_TX)
*               -void log_string_BBB(uint8_t * data_TX)
*		-void log_integer(uint32_t test3,uint8_t length)
*		-void log_integer_BBB(uint32_t test3,uint8_t length)
***************************************************************************/
#ifndef SOURCES_LOGGER_H_
#define SOURCES_LOGGER_H_

#ifdef FRDM
#define printf(...)
#endif


/****************************************************************************
* This function is used to block until the logger buffer is empty
****************************************************************************/
void log_flush(void);


/****************************************************************************
* This function is used as to add data to circular buffer and then transmit
* through uart for FRDM
* uint8_t * data_TX - This pointer points to the array where the data is stored
* uint8_t length_TX - This gives the length of bytes to be transmitted
*****************************************************************************/
void log_data(uint8_t * data_TX,uint8_t length_TX);


/****************************************************************************
* This function is used to add string to circular buffer and then transmit
* through uart for FRDM
* uint8_t * data_TX - This pointer points to the string to be transmitted
****************************************************************************/
void log_string(uint8_t * data_TX);


/****************************************************************************
* This function is used as to add data to circular buffer and then display
* using printf for BBB and host machine
* uint8_t * data_TX - This pointer points to the array where the data is stored
* uint8_t length_TX - This gives the length of bytes to be transmitted
*****************************************************************************/
void log_data_BBB(uint8_t * data_TX,uint8_t length_TX);


/****************************************************************************
* This function is used to add string to circular buffer and then display
* using printf for BBB and host machine
* uint8_t * data_TX - This pointer points to the string to be transmitted
****************************************************************************/
void log_string_BBB(uint8_t * data_TX);


/***************************************************************************
* This function is used to convert integer to ascii and then transmit
* through uart for FRDM
* uint32_t test3 - This variable has the integer variable which is to be
 convert to ascii
* uint8_t length - This variable gives the length to be converted
**************************************************************************/
void log_integer(uint32_t test3,uint8_t length);



/***************************************************************************
* This function is used to convert integer to ascii and then display
* using printf for BBB and host machine
* uint32_t test3 - This variable has the integer variable which is to be
 convert to ascii
* uint8_t length - This variable gives the length to be converted
**************************************************************************/
void log_integer_BBB(uint32_t test3,uint8_t length);




#endif /* SOURCES_LOGGER_H_ */
