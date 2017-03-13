ECEN 5013- Embedded Software Essentials: Project 2

Authors: Vishal Vishnani & Virag Gada

Date: 03/12/2017

Supported Platforms: Freedom Freescale KL25Z, HOST LINUX-Ubuntu, BeagleBone Black

Goals:
1. Implementing an optimized circular buffer.
2. Unit testing data, memory and circular buffer functions using cmocka framework.
3. Implementing UART Binary Logger to log information using UART.

File structure:
* Libraries: Consisting of Makefile and folders required to install and run unit tests in cmocka framework.

* Headers: Consisting of header files required for our project.
	1. data.h – Header file for implementing data manipulation functions.
	2. memory.h – Header file for implementing memory manipulation functions.
	3. circbuff.h – Header file for implementing circular buffer functions.
	4. logger.h - Header file for implementing logger functions.
	5. binary_logger.h - Header file for implementing binary logger functions.
	6. uart_init.h - Header file for implementing uart module functions.

* SOURCES: Consisting of source files required for our project.
	1. data.c - Source file for implementing data manipulation functions.
	2. memory.h - Source file for implementing memory manipulation functions.
	3. circbuff.c - Source file for implementing circular buffer functions.
	4. logger.c - Source file for implementing logger functions such as log_data,
	   log_integer, log_string.
	5. binary_logger.c - Source file for implementing binary logging functions such as
	   create_log_item, log_item, destroy_log_item.
	6. uart_init.c - Source file for implementing uart module functions.
	7. test_data.c - Source file for unit testing data manipulation functions using cmocka.
	8. test_memory.c - Source file for unit testing memory manipulation functions using cmocka.
	9. test_circbuff.c - Source file for unit testing circular buffer functions using cmocka.
	10. test_project2.c - Source file for unit testing data, memory and circular buffer functions
	    using cmocka.
	11. main.c – main source file for running the project.

* Makefile – Used to make targets with required prerequisites and different compiler options. It consists of compile time switches to switch between platforms thereby making it platform independent.

* Makefile1 – Makefile required to run unit test functions using cmocka framework.

* sources.mk – Contains path for source and header files.
