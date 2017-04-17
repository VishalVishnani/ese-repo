ECEN 5013- Embedded Software Essentials: Project 2

Authors: Vishal Vishnani & Virag Gada

Date: 04/16/2017

Supported Platforms: Freedom Freescale KL25Z, BeagleBone Black

Goals:
1. Implemented profiling to check transfer times using DMA and standard memory functions for FRDM and BBB.
2. Implemented Timestamp log on binary logger using RTC.
3. Read/Write to nRF24L01 module registers over SPI.

File structure:

* Headers: Consisting of header files required for our project.
	1. data.h – Header file for implementing data manipulation functions.
	2. memory.h – Header file for implementing memory manipulation functions.
	3. circbuff.h – Header file for implementing circular buffer functions.
	4. logger.h - Header file for implementing logger functions.
	5. binary_logger.h - Header file for implementing binary logger functions.
	6. uart_init.h - Header file for implementing uart module functions.
	7. spi.h - Header file for implementing SPI peripheral functions.
	8. rtc.h - Header file for implementing RTC functions.
	9. gpio.h - Header file for initializing GPIO pins for LED and UART.
	10 nordic.h - Header file for implementing nRF24L01 register definitions and register specific functions.
	11. Profiling_FRDM.h - Header file for implementing timer profiling on FRDM.
	12. DMA.h - Header file for implementing DMA module functions.

* SOURCES: Consisting of source files required for our project.
	1. data.c - Source file for implementing data manipulation functions.
	2. memory.h - Source file for implementing memory manipulation functions.
	3. circbuff.c - Source file for implementing circular buffer functions.
	4. logger.c - Source file for implementing logger functions such as log_data,
	   log_integer, log_string.
	5. binary_logger.c - Source file for implementing binary logging functions such as
	   create_log_item, log_item, destroy_log_item.
	6. uart_init.c - Source file for implementing uart module functions.
	7. spi.c - Source file for implementing SPI functions. 
	8. rtc.c - Source file for RTC initialization.
	9. gpio.c - Source file for GPIO initializations.
	10 nordic.c - Source file for nRF24L01 module
	11. Profiling_FRDM.c - Source file for implementing timer profiling on FRDM.
	12. DMA.c - Source file for implementing DMA module functions.
	12. main.c – main source file for running the project.

* Makefile – Used to make targets with required prerequisites and different compiler options. It consists of compile time switches to switch between platforms thereby making it platform independent.

* sources.mk – Contains path for source and header files.
