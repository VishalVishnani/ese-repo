/*************************************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 04/12/2017
*
* File : rtc.h
* Description : Header file for RTC initialization functions
*            	-void rtc_init(void)
***************************************************************************/

#ifndef SOURCES_RTC_H_
#define SOURCES_RTC_H_

#include <time.h>

#define ADJUSTMENT (21580)

uint8_t * c_time_string;

/*******************************************
* SPI_init() - Function to initialize RTC
********************************************/
void rtc_init(void);

#endif /* SOURCES_RTC_H_ */
