/*
 * rtc.h
 *
 *  Created on: 27-Mar-2017
 *      Author: omkar
 */

#ifndef SOURCES_RTC_H_
#define SOURCES_RTC_H_

#include <time.h>

#define EPOCH_TIME (1492146476)


time_t current_time;
uint8_t * c_time_string;

/*******************************************
* SPI_init() - Function to initialize RTC
********************************************/
void rtc_init(void);

#endif /* SOURCES_RTC_H_ */
