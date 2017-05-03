/*********************************************************
* Authors : Vishal Vishnani, Virag Gada
* Date : 04/26/2017
* File : main.c
*********************************************************/

/*Includes*/
#include "MKL25Z4.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "data.h"
#include "circbuff.h"
#include "binary_logger.h"
#include "logger.h"
#include "led.h"
#include <time.h>
#include <sys/time.h>
#include "timer.h"

/*Macros*/
#define MAX_DATA_SIZE 50

/*Global Variables*/
uint8_t length_TXbuff=255;
uint8_t length_RXbuff=16;

/*Enumerations*/
typedef enum{
	LED_RED=0x01,
	LED_GREEN,
	LED_BLUE,
	LED_ON,
	LED_OFF,
	PWM_ON,
	PWM_OFF,
	GET_RTC,
	SYSTEM_RESET
}cmds;

/*Structure for command packet*/
typedef struct {
	cmds command;
	uint8_t length;
	uint8_t data[MAX_DATA_SIZE];
	uint8_t checksum;
}CI_msg;
CI_msg *packet;



/*Compile time switch for BBB*/
#ifdef BBB
	#define UART_initialize()
    #define DMA_initialize()
	#define rtc_init()
	#define SPI_init()
	#define log_data(data_TX,length_TX) log_data_BBB(data_TX,length_TX)
	#define log_integer(test3,length_TX) log_integer_BBB(test3,length_TX)
	#define log_string(data_TX) log_string_BBB (data_TX)
	#define UART0_C2 (temp)
#endif

/*Compile time switch for HOST*/
#ifdef HOST
	#define UART_initialize()
	#define rtc_init()
	#define SPI_init()
	#define log_data(data_TX,length_TX) log_data_BBB(data_TX,length_TX)
	#define log_integer(test3,length_TX) log_integer_BBB(test3,length_TX)
	#define log_string(data_TX) log_string_BBB (data_TX)
	#define UART0_C2 (temp)
#endif

#ifdef FRDM
#include "MKL25Z4.h"
#include "DMA.h"
#include "uart_init.h"
#include "spi.h"
#include "rtc.h"
#include "nordic.h"
#include "led.h"
#define printf(...)
#endif

/*Global Variables*/
volatile uint8_t recievedDataCount = 0;
uint8_t warningString[] = "Buffer is Full\n\r";
volatile uint8_t recieved_data;
volatile uint8_t receive_packet = 0;
volatile uint8_t analyse=0;
uint8_t timer_overflow=0;
static uint8_t i = 0;
uint8_t checksum_check=0;
uint8_t checksum_correct=0;
uint8_t transfer_complete=0;
uint8_t timestampString1[11] = " Timestamp:";

#define CLOCKTIME (0.047)

uint8_t rtc_trigger = 0;

#ifdef FRDM
uint8_t * txaddr_array;
uint8_t tx_addr_values[5] = { 55, 66, 77, 88, 99 };


/*This function receives the command packet and stores it in the structure*/
uint8_t Receive_Command_Packet(void){
	uint8_t c = recieved_data;
	uint8_t packet_complete=0;

	/*The first byte received is command*/
	if(recievedDataCount==1){
		packet->command=c;
	}

	/*The next byte after the length is data*/
	if(recievedDataCount>2 && recievedDataCount<(packet->length)){
		packet->data[recievedDataCount-3]=c;
	}

	/*The second byte received is length*/
	if(recievedDataCount==2){
		packet->length=c;
	}

	/*If x char is received,abort the packet*/
	if(c=='x'){
		packet->command=0;
		packet->length=0;
		packet->data[0]=0;
		packet->checksum=0;
		recievedDataCount=0;
		receive_packet=0;
	}

	/*The last byte of the packet is checksum*/
	if(recievedDataCount>0){
		if(recievedDataCount==packet->length){
			packet->checksum=c;
			packet_complete=1;
		}
	}
	/*Return 1 after the packet is complete*/
	return packet_complete;
}

/*This function calculates checksum of the packet received
 * and compares it with the packet checksum */
uint8_t Validate_Checksum(void){
	uint8_t i=0;
	uint8_t temp_data=0;
	uint8_t checksum_verify=0;
	for(i=0;i<((packet->length)-3);i++){
		/*Add all the data*/
		temp_data += packet->data[i];
	}

	/*Calculate checksum*/
	checksum_check=(packet->command)+(packet->length)+temp_data;
	if((packet->checksum)==checksum_check){
		checksum_verify=1;
	}

	/*Return checksum_verify as 1 if checksum is correct*/
	return checksum_verify;
}

/*This function executes command based on the packet received*/
void Execute_command(void){
	if(packet->command==LED_RED){
		if(packet->data[0]==LED_ON){
			if(packet->data[1]==PWM_ON){
				LED_Intensity('R',packet->data[2]);
			}
			else if(packet->data[1]=PWM_OFF){

				/*If PWM not required for LED ON,set the intensity to maximum*/
				LED_Intensity('R',150);
			}
		}
		else{

			/*For LED OFF, set the intensity to 0*/
			LED_Intensity('R',0);
		}
		receive_packet=0;
	}

	else if(packet->command==LED_GREEN){
		if(packet->data[0]==LED_ON){
			if(packet->data[1]==PWM_ON){
				LED_Intensity('G',packet->data[2]);
			}
			else if(packet->data[1]=PWM_OFF){
				/*If PWM not required for LED ON,set the intensity to maximum*/
				LED_Intensity('G',150);
			}
		}
		else{
			/*For LED OFF, set the intensity to 0*/
			LED_Intensity('G',0);
		}
		receive_packet=0;
	}

	else if(packet->command==LED_BLUE){
		if(packet->data[0]==LED_ON){
			if(packet->data[1]==PWM_ON){
				LED_Intensity('B',packet->data[2]);
			}
			else if(packet->data[1]=PWM_OFF){
				/*If PWM not required for LED ON,set the intensity to maximum*/
				LED_Intensity('B',150);
			}
		}
		else{
			/*If PWM not required for LED ON,set the intensity to maximum*/
			LED_Intensity('B',0);
		}
		receive_packet=0;
	}

	else if(packet->command==GET_RTC){
		rtc_trigger = 1;
		receive_packet=0;
	}

	else if(packet->command==SYSTEM_RESET){
		/*Function for system reset*/
		NVIC_SystemReset();
		receive_packet=0;
	}

	/*Set all variables and command packet to 0*/
	packet->command=0;
	packet->length=0;
	packet->data[0]=0;
	packet->checksum=0;
	recievedDataCount=0;
	receive_packet=0;
	checksum_correct=0;
	transfer_complete=0;
}

/*This function is entered when a byte is received through UART*/
void analyse_data(){
	analyse=0;

	/*Function Pointers*/
	void (*EXECUTE)();
	EXECUTE=&Execute_command;

	uint8_t (*RECEIVE_PACKET)();
	RECEIVE_PACKET=&Receive_Command_Packet;

	uint8_t (*VALIDATE_PACKET)();
	VALIDATE_PACKET=&Validate_Checksum;

	if (receive_packet==1){
		transfer_complete=RECEIVE_PACKET();
		if(transfer_complete==1){
			checksum_correct=VALIDATE_PACKET();
			if(checksum_correct==1){
				//Execute_command();
				EXECUTE();
			}
			else{
				uint8_t checksum_error[]="The received command packet is incorrect";
				uint8_t* data_TX=checksum_error;
				log_string(data_TX);
			}
		}
	}
}


/***********************************
 *Function to handle UART interrupts
 ************************************/
void UART0_IRQHandler(void) {
	START_CRITICAL();
	/* Check if interrupt is for TX or RX and handle accordingly
	 * For TX interrupt we take the data from TX buffer and
	 * sent it to UART to transmit*/
	if ((UART0_C2 & UART0_C2_TIE_MASK) != 0) {
		uint8_t data;
		uint16_t i;
		while (CircBuffT->count) {
		#ifdef EXTRA_CREDIT
			memmove_dma_byte_uart((CircBuffT->tail),&(UART0_D),(uint32_t) 1);
		#else
			data = *(CircBuffT->tail);
			UART_send_byte(data);
		#endif
			cbuffer_remove(CircBuffT, 1);
			for (i = 1000; i > 0; i--);
		}
		/*Disabling TX interrupt bit*/
		log_flush();
		UART0_C2 &= ~UART0_C2_TIE_MASK;
	}

	/* For RX interrupt check add data to the RX buffer and
	 * analyse the data to check if it is an alphabet, number,
	 * punctuation or a miscellaneous characters*/
	else if (((UART0_C2 & UART0_C2_RIE_MASK) != 0)
			&& ((UART0_S1 & UART0_S1_RDRF_MASK) != 0)) {
		uint8_t c = UART_receive_byte();
		recieved_data = c;
		recievedDataCount++;
		cbuffer_add(CircBuffR, &c, 1);
		analyse=1;
		if(c=='p'){
			receive_packet =1;
			recievedDataCount=0;
		}
		uint16_t j;
		for (j = 1000; j > 0; j--);
		UART0_C2 |= UART_C2_TIE_MASK;
	}
	END_CRITICAL();
}

/******************************************
 *Function to handle RTC Seconds interrupts
 ******************************************/
void RTC_Seconds_IRQHandler(void) {
	START_CRITICAL();
#ifdef LOG_ON
	log_string("\n\r");
	system_log->Timestamp = RTC_TSR;
	system_log->logID = HEARTBEAT;
	system_log->LogLength = 0;
	system_log->Payload = 0;
	log_item(system_log);
#endif

}

/************************************
 *Function to handle DMA0 interrupts
 ************************************/
void DMA0_IRQHandler(void){
__disable_irq();
#ifdef PROFILER
	TPM0_stop();
#endif

DMA_DCR0 &=0x7FFFFFFF;
DMA_DSR_BCR0 |= 0x01000000;
__enable_irq();
}

/************************************
 *Function to handle TPM0 interrupts
 ************************************/
void TPM0_IRQHandler(void){
	__disable_irq();
	timer_overflow++;
	TPM0_SC|=TPM_SC_TOF_MASK; //clear TOF flag
	__enable_irq();
}

#endif

int main(void)
{
	system_log = create_log_item();

		/*Create and Initialize Transmit Circular Buffer*/
		CircBuffT = (CircBuff *) calloc(1,sizeof(CircBuff));
		packet = (CI_msg*) calloc(1,sizeof(CI_msg));
		uint8_t * cbufferT=NULL;
		(CircBuffT->length) = length_TXbuff;
		cbufferT = cbuffer_memoryAllocate(cbufferT,length_TXbuff);

		CircBuffT->buffer = cbufferT;
		cbuffer_init(CircBuffT);

		rtc_init();
		system_log->Timestamp = RTC_TSR;
		UART_initialize();
		init_PWM();
		#ifdef LOG_ON
			system_log->logID = LOGGER_INITIALIZED;
			log_item(system_log);
			system_log->logID = SYSTEM_INITIALIZED;
			log_item(system_log);
		#endif
			init_PWM();
		/*Create and Initialize Receiver Circular Buffer*/
	    CircBuffR = (CircBuff *) calloc(1,sizeof(CircBuff));
	    uint8_t * cbufferR=NULL;
	    (CircBuffR->length) = length_RXbuff;
	    cbufferR = cbuffer_memoryAllocate(cbufferR,length_RXbuff);
	    CircBuffR->buffer = cbufferR;
	    cbuffer_init(CircBuffR);

	init_PWM();
	#ifdef FRDM
	void(*ANALYSE)();
	ANALYSE=&analyse_data;

	while(1){
		/*When UART receives data the variable is set to analyze data*/
		if(analyse == 1){
			//analyse_data();
			ANALYSE();
		}
		if(rtc_trigger == 1){
			c_time_string = ctime((time_t *)&RTC->TSR);
			uint8_t length = stringLength(c_time_string);
			c_time_string[length-1] = ' ';
			log_string(c_time_string);
			rtc_trigger = 0;
		}
	}
	#endif

}

