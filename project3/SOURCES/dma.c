/**************************************************
* Authors : Vishal Vishnani, Virag Gada

* Date : 04/16/2017
*
* File : dma.c
* Description :  source file for DMA configuration
*               -DMA_initialize()
*               -memmove_dma_byte()
*               -memmove_dma_byte_uart()
*               -memmove_dma_halfword()
*               -memmove_dma_word()
*               -memzero_dma_byte()
*               -memzero_dma_halfword()
*               -memzero_dma_word()
*
***************************************************/

#include <stdint.h>
#include "circbuff.h"
#include "memory.h"


/*Compile time switch for FRDM*/
#ifdef FRDM
#include "dma.h"
#include "MKL25Z4.h"

#define DMA_ENABLE_TRANSFER (0x80)
#define DMA_START_BIT_ENABLE (0x10000)
#define DMA_DISABLE (0x00)
#define DMA_CHANNEL0 (0x3C)
#define DMAMUX_CLOCK_ENABLE (0x00000002)
#define DMA_CLOCK_ENABLE (0x00000100)
#define DMA_DCR0_UART (0xE09A0000)
#define DMA_DCR0_8BIT_SINC (0x805A0000)
#define DMA_DCR0_8BIT (0x801A0000)
#define DMA_DCR0_16BIT_SINC (0x806C0000)
#define DMA_DCR0_16BIT (0x802C0000)
#define DMA_DCR0_32BIT_SINC (0x80480000)
#define DMA_DCR0_32BIT (0x80080000)

/*Function to select and enable clock for DMA*/
void DMA_initialize(void){
	/*enable clock for DMA mux clock gate control*/
	SIM_SCGC6=DMAMUX_CLOCK_ENABLE;

	/*enable clock for DMA clock gate control*/
	SIM_SCGC7=DMA_CLOCK_ENABLE;

	/*disable dma before configuration*/
	DMAMUX0_CHCFG0=DMA_DISABLE;
}


/*Function to configure DMA for byte transfer and display on terminal through UART*/
void memmove_dma_byte_uart(uint8_t * src, uint8_t * dst, uint32_t length){

	/*overlapping condition*/
	if((src<dst) && (dst-length)<src){

		uint8_t temp[length];

		/*assign source address*/
		DMA_SAR0=(uint32_t)src;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)&temp;

		/*Do not start transfer until configuration is complete, determine source size,
		*source increment, destination size, destination increment, enable peripheral request*/
		DMA_DCR0=DMA_DCR0_UART;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=DMA_CHANNEL0;

		/*enable DMA transfer*/
		DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

		/*enable start bit*/
		DMA_DCR0|=DMA_START_BIT_ENABLE;

		/*assign source address*/
		DMA_SAR0=(uint32_t)&temp;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)dst;

		/*Do not start transfer until configuration is complete, determine source size,
		*source increment, destination size, destination increment*/
		DMA_DCR0=DMA_DCR0_UART;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=DMA_CHANNEL0;

		/*enable DMA transfer*/
		DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

		/*enable start bit*/
		DMA_DCR0|=DMA_START_BIT_ENABLE;

		/*enable interrupt for dma*/
		NVIC_EnableIRQ(DMA0_IRQn);

	}
	else{

		/*assign source address*/
		DMA_SAR0=(uint32_t)src;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)dst;

		/*Do not start transfer until configuration is complete, determine source size,
		 *source increment, destination size, destination increment*/
		DMA_DCR0=DMA_DCR0_UART;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=DMA_CHANNEL0;

		/*enable DMA transfer*/
		DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

		/*enable start bit*/
		DMA_DCR0|=DMA_START_BIT_ENABLE;

		/*enable interrupt for dma*/
		 NVIC_EnableIRQ(DMA0_IRQn);
	}
}


/*Function to configure dma for byte transfer*/
void memmove_dma_byte(uint8_t * src, uint8_t * dst, uint32_t length){
	/*overlapping condition*/
	if((src<dst) && (dst-length)<src){

		uint8_t temp[length];

		/*assign source address*/
		DMA_SAR0=(uint32_t)src;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)&temp;

		/*Do not start transfer until configuration is complete, determine source size,
		*source increment, destination size, destination increment*/
		DMA_DCR0=DMA_DCR0_8BIT_SINC;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=DMA_CHANNEL0;

		/*enable DMA transfer*/
		DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

		/*enable start bit*/
		DMA_DCR0|=DMA_START_BIT_ENABLE;

		/*assign source address*/
		DMA_SAR0=(uint32_t)&temp;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)dst;

		/*Do not start transfer until configuration is complete, determine source size,
		*source increment, destination size, destination increment*/
		DMA_DCR0=DMA_DCR0_8BIT_SINC;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=DMA_CHANNEL0;

		/*enable DMA transfer*/
		DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

		/*enable start bit*/
		DMA_DCR0|=DMA_START_BIT_ENABLE;

		/*enable interrupt for dma*/
		NVIC_EnableIRQ(DMA0_IRQn);

	}
	else{

		/*assign source address*/
		DMA_SAR0=(uint32_t)src;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)dst;

		/*Do not start transfer until configuration is complete, determine source size,
		 *source increment, destination size, destination increment*/
		DMA_DCR0=DMA_DCR0_8BIT_SINC;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=DMA_CHANNEL0;

		/*enable DMA transfer*/
		DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

		/*enable start bit*/
		DMA_DCR0|=DMA_START_BIT_ENABLE;

		/*enable interrupt for DMA*/
		 NVIC_EnableIRQ(DMA0_IRQn);
	}
}


/*Function to configure dma for byte transfer to set values to 0*/
void memzero_dma_byte(uint8_t *src,uint32_t length){

	/*assign destination address of dma to starting address to memory*/
	DMA_DAR0=(uint32_t)src;

	uint8_t value=0;

	/*assign the value of source address to address of 0*/
	DMA_SAR0=(uint32_t)&value;

	/*Do not start transfer until configuration is complete, determine source size,
	*destination size, destination increment. Do not increment source*/
	DMA_DCR0=DMA_DCR0_8BIT;

	/*load the length value*/
	DMA_DSR_BCR0=length;

	/*select channel source slot*/
	DMAMUX0_CHCFG0|=DMA_CHANNEL0;

	/*enable DMA transfer*/
	DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

	/*enable start bit*/
	DMA_DCR0|=DMA_START_BIT_ENABLE;

	/*enable interrupt for dma*/
	NVIC_EnableIRQ(DMA0_IRQn);
}


/*Function to configure dma for halfword transfer*/
void memmove_dma_halfword(uint16_t *src,uint16_t * dst, uint32_t length){

	/*If the length of bytes is for suppose 11, then 10 bytes will be transferred
	 * by dma_halfword and 1 bytes by my_memmove*/

	uint8_t remainder=0;

	remainder=length % 2;

	length=length-remainder;

	/*check overlapping condition*/
	if((src<dst) && (dst-length)<src){

		uint8_t temp[length];

		/*assign source address*/
		DMA_SAR0=(uint32_t)src;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)&temp;

		/*Do not start transfer until configuration is complete, determine source size,
		 *source increment, destination size, destination increment*/
		DMA_DCR0=DMA_DCR0_16BIT_SINC;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*Select channel source slot*/
		DMAMUX0_CHCFG0|=DMA_CHANNEL0;

		/*enable DMA transfer*/
		DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

		/*enable start bit*/
		DMA_DCR0|=DMA_START_BIT_ENABLE;


		/*assign source address*/
		DMA_SAR0=(uint32_t)&temp;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)dst;

		/*Do not start transfer until configuration is complete, determine source size,
		*source increment, destination size, destination increment*/
		DMA_DCR0=DMA_DCR0_16BIT_SINC;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*Select channel source slot*/
		DMAMUX0_CHCFG0|=DMA_CHANNEL0;

		/*enable DMA transfer*/
		DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

		/*enable start bit*/
		DMA_DCR0|=DMA_START_BIT_ENABLE;


		/*enable interrupt for dma*/
		NVIC_EnableIRQ(DMA0_IRQn);

		}
	else{

		/*assign source address*/
		DMA_SAR0=(uint32_t)src;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)dst;

		/*Do not start transfer until configuration is complete, determine source size,
		 *source increment, destination size, destination increment*/
		DMA_DCR0=DMA_DCR0_16BIT_SINC;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*Select channel source slot*/
		DMAMUX0_CHCFG0|=0x3C;

		/*enable DMA transfer*/
		DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

		/*enable start bit*/
		DMA_DCR0|=DMA_START_BIT_ENABLE;

		/*enable interrupt for dma*/
		NVIC_EnableIRQ(DMA0_IRQn);
	}

	/*remaining transfer by my_memmove*/
	if (remainder > 0){
			uint8_t * src1= (uint8_t *)src + length;
			uint8_t * dst1= (uint8_t *)dst + length;
			my_memmove(src1,dst1,(uint32_t)remainder);
		}

}


/*function to configure dma for halfword transfer to set the value to 0*/
void memzero_dma_halfword(uint16_t *src,uint32_t length){

	/*If the length of bytes is for suppose 11, then 10 bytes will be transferred
	* by dma_halfword and 1 bytes by my_memset*/

	uint8_t remainder=0;
	remainder=length % 2;
	length=length-remainder;

	uint16_t value=0;

	/*assign address of 0 to source address*/
	DMA_SAR0=(uint32_t)&value;

	/*assign destination address*/
	DMA_DAR0=(uint32_t)src;

	/*Do not start transfer until configuration is complete, determine source size,
	 *destination size, destination increment. Do not increment source */
	DMA_DCR0=DMA_DCR0_16BIT;

	/*load the length value*/
	DMA_DSR_BCR0=length;

	/*Select channel source slot*/
	DMAMUX0_CHCFG0|=DMA_CHANNEL0;

	/*enable DMA transfer*/
	DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

	/*enable start bit*/
	DMA_DCR0|=DMA_START_BIT_ENABLE;

	/*enable interrupt for dma*/
	NVIC_EnableIRQ(DMA0_IRQn);

	/*remaining transfer by my_memset*/
	if (remainder > 0){
		uint8_t * src1= (uint8_t *)src + length;
		my_memset(src1,(uint32_t)remainder,(uint8_t) 0);

	}
}


/*function to configure dma for word transfer*/
void memmove_dma_word(uint32_t *src,uint32_t * dst, uint32_t length){

	/*If the length of bytes is for suppose 11, then 8 bytes will be transferred
	* by dma_word and 3 bytes by my_memmove*/


	uint8_t remainder=0;
	remainder=length % 4;
	length=length-remainder;

	/*Check overlapping condition*/
	if((src<dst) && (dst-length)<src){

		uint8_t temp[length];

		/*assign source address*/
		DMA_SAR0=(uint32_t)src;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)&temp;

		/*Do not start transfer until configuration is complete, determine source size,
		*source increment, destination size, destination increment*/
		DMA_DCR0=DMA_DCR0_32BIT_SINC;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=DMA_CHANNEL0;

		/*Enable DMA transfer*/
		DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

		/*enable start bit*/
		DMA_DCR0|=DMA_START_BIT_ENABLE;

		/*assign source address*/
		DMA_SAR0=(uint32_t)&temp;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)dst;

		/*Do not start transfer until configuration is complete, determine source size,
		*source increment, destination size, destination increment*/
		DMA_DCR0=DMA_DCR0_32BIT_SINC;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=DMA_CHANNEL0;

		/*Enable DMA transfer*/
		DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

		/*enable start bit*/
		DMA_DCR0|=DMA_START_BIT_ENABLE;

		/*enable interrupt for dma*/
		NVIC_EnableIRQ(DMA0_IRQn);

	}
	else{

		/*assign source address*/
		DMA_SAR0=(uint32_t)src;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)dst;

		/*Do not start transfer until configuration is complete, determine source size,
		 *source increment, destination size, destination increment*/
		DMA_DCR0=DMA_DCR0_32BIT_SINC;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=DMA_CHANNEL0;

		/*Enable DMA transfer*/
		DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

		/*enable start bit*/
		DMA_DCR0|=DMA_START_BIT_ENABLE;

		/*enable interrupt for dma*/
		NVIC_EnableIRQ(DMA0_IRQn);

	}

	/*remaining bytes transferred by my_memmoove*/
	if (remainder > 0){
		uint8_t * src1= (uint8_t *)src + length;
		uint8_t * dst1= (uint8_t *)dst + length;
		my_memmove(src1,dst1,(uint32_t)remainder);
	}
}


/*function to configure dma to transfer word and set value to 0*/
void memzero_dma_word(uint32_t *src,uint32_t length){

	/*If the length of bytes is for suppose 11, then 8 bytes will be transferred
	* by dma_word and 3 bytes by my_memset*/
	uint8_t remainder=0;
	remainder=length % 4;
	length=length-remainder;

	uint32_t value=0;

	/*assign address of 0 to source address*/
	DMA_SAR0=(uint32_t)&value;


	/*assign destination address*/
	DMA_DAR0=(uint32_t)src;

	/*Do not start transfer until configuration is complete, determine source size,
	 *destination size, destination increment. Do not increment source*/
	DMA_DCR0=DMA_DCR0_32BIT;

	/*load the length value*/
	DMA_DSR_BCR0=length;

	/*select channel source slot*/
	DMAMUX0_CHCFG0|=DMA_CHANNEL0;

	/*Enable DMA transfer*/
	DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;

	/*enable start bit*/
	DMA_DCR0|=DMA_START_BIT_ENABLE;

	/*enable interrupt*/
	NVIC_EnableIRQ(DMA0_IRQn);

	/*remaining bytes to be transferred by my_memset*/
	if (remainder > 0){
		uint8_t * src1= (uint8_t *)src + length;
		my_memset(src1,(uint32_t)remainder,(uint8_t) 0);
	}

}
#endif
