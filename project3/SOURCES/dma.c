/*
 * DMA.c

 *
 *  Created on: Mar 23, 2017
 *      Author: vishal
 */

#include <stdint.h>
#include "DMA.h"
#include "MKL25Z4.h"

void DMA_initialize(void){
	/*enable clock for DMA mux clock gate control*/
	SIM_SCGC6=0x00000002;

	/*enable clock for DMA clock gate control*/
	SIM_SCGC7=0x00000100;

	/*disable dma before configuration*/
	DMAMUX0_CHCFG0=0x00;
}

void memmove_dma_byte(uint8_t * src, uint8_t * dst, uint32_t length){
	/*overlapping condition*/
	if((src<dst) && (dst-length)<src){

		uint8_t temp[length];

		DMA_SAR0=(uint32_t)src;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)&temp;

		/*Do not start transfer until configuration is complete, determine source size,
		*source increment, destination size, destination increment*/
		DMA_DCR0=0x005A0000;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=0x3C;

		/*enable DMA transfer*/
		DMAMUX0_CHCFG0|=0x80;

		/*enable start bit*/
		DMA_DCR0|=0x00010000;

		DMA_SAR0=(uint32_t)&temp;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)dst;

		/*Do not start transfer until configuration is complete, determine source size,
		*source increment, destination size, destination increment*/
		DMA_DCR0=0x005A0000;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=0x3C;

		/*enable DMA transfer*/
		DMAMUX0_CHCFG0|=0x80;

		/*enable start bit*/
		DMA_DCR0|=0x00010000;

	}
	else{

		/*assign source address*/
		DMA_SAR0=(uint32_t)src;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)dst;

		/*Do not start transfer until configuration is complete, determine source size,
		 *source increment, destination size, destination increment*/
		DMA_DCR0=0x005A0000;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=0x3C;

		/*enable DMA transfer*/
		DMAMUX0_CHCFG0|=0x80;

		/*enable start bit*/
		DMA_DCR0|=0x00010000;
	}
}

void memzero_dma_byte(uint8_t *src,uint32_t length){

	DMA_DAR0=(uint32_t)src;

	/*assign destination address*/
	uint8_t value=0;
	DMA_SAR0=(uint32_t)&value;

	/*Do not start transfer until configuration is complete, determine source size,
	*source increment, destination size, destination increment*/
	DMA_DCR0=0x001A0000;

	/*load the length value*/
	DMA_DSR_BCR0=length;

	/*select channel source slot*/
	DMAMUX0_CHCFG0|=0x3C;

	/*enable DMA transfer*/
	DMAMUX0_CHCFG0|=0x80;

	/*enable start bit*/
	DMA_DCR0|=0x00010000;

}

void memmove_dma_halfword(uint16_t *src,uint16_t * dst, uint32_t length){

	if((src<dst) && (dst-length)<src){

			uint8_t temp[length];
			/*assign source address*/
			DMA_SAR0=(uint32_t)src;

			/*assign destination address*/
			DMA_DAR0=(uint32_t)&temp;

			/*Do not start transfer until configuration is complete, determine source size,
			 *source increment, destination size, destination increment*/
			DMA_DCR0=0x006C0000;

			/*load the length value*/
			DMA_DSR_BCR0=length;

			/*Select channel source slot*/
			DMAMUX0_CHCFG0|=0x3C;

			/*enable DMA transfer*/
			DMAMUX0_CHCFG0|=0x80;

			/*enable start bit*/
			DMA_DCR0|=0x00010000;


			DMA_SAR0=(uint32_t)&temp;

			/*assign destination address*/
			DMA_DAR0=(uint32_t)dst;

			/*Do not start transfer until configuration is complete, determine source size,
			*source increment, destination size, destination increment*/
			DMA_DCR0=0x006C0000;

			/*load the length value*/
			DMA_DSR_BCR0=length;

			/*Select channel source slot*/
			DMAMUX0_CHCFG0|=0x3C;

			/*enable DMA transfer*/
			DMAMUX0_CHCFG0|=0x80;

			/*enable start bit*/
			DMA_DCR0|=0x00010000;

		}
	else{

		/*assign source address*/
		DMA_SAR0=(uint32_t)src;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)dst;

		/*Do not start transfer until configuration is complete, determine source size,
		 *source increment, destination size, destination increment*/
		DMA_DCR0=0x006C0000;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*Select channel source slot*/
		DMAMUX0_CHCFG0|=0x3C;

		/*enable DMA transfer*/
		DMAMUX0_CHCFG0|=0x80;

		/*enable start bit*/
		DMA_DCR0|=0x00010000;
	}

}
void memzero_dma_halfword(uint16_t *src,uint32_t length){

	/*assign source address*/
	uint16_t value=0;
	DMA_SAR0=(uint32_t)&value;

	/*assign destination address*/
	DMA_DAR0=(uint32_t)src;

	/*Do not start transfer until configuration is complete, determine source size,
	 *source increment, destination size, destination increment*/
	DMA_DCR0=0x002C0000;

	/*load the length value*/
	DMA_DSR_BCR0=length;

	/*Select channel source slot*/
	DMAMUX0_CHCFG0|=0x3C;

	/*enable DMA transfer*/
	DMAMUX0_CHCFG0|=0x80;

	/*enable start bit*/
	DMA_DCR0|=0x00010000;

}

void memmove_dma_word(uint32_t *src,uint32_t * dst, uint32_t length){

	if((src<dst) && (dst-length)<src){
		uint8_t temp[length];
		DMA_SAR0=(uint32_t)src;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)&temp;

		/*Do not start transfer until configuration is complete, determine source size,
		*source increment, destination size, destination increment*/
		DMA_DCR0=0x00480000;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=0x3C;

		/*Enable DMA transfer*/
		DMAMUX0_CHCFG0|=0x80;

		/*enable start bit*/
		DMA_DCR0|=0x00010000;


		DMA_SAR0=(uint32_t)&temp;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)dst;

		/*Do not start transfer until configuration is complete, determine source size,
		*source increment, destination size, destination increment*/
		DMA_DCR0=0x00480000;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=0x3C;

		/*Enable DMA transfer*/
		DMAMUX0_CHCFG0|=0x80;

		/*enable start bit*/
		DMA_DCR0|=0x00010000;

	}
	else{

		/*assign source address*/
		DMA_SAR0=(uint32_t)src;

		/*assign destination address*/
		DMA_DAR0=(uint32_t)dst;

		/*Do not start transfer until configuration is complete, determine source size,
		 *source increment, destination size, destination increment*/
		DMA_DCR0=0x00480000;

		/*load the length value*/
		DMA_DSR_BCR0=length;

		/*select channel source slot*/
		DMAMUX0_CHCFG0|=0x3C;

		/*Enable DMA transfer*/
		DMAMUX0_CHCFG0|=0x80;

		/*enable start bit*/
		DMA_DCR0|=0x00010000;
	}
}

void memzero_dma_word(uint32_t *src,uint32_t length){

	/*assign source address*/
	uint32_t value=0;
	DMA_SAR0=(uint32_t)&value;

	/*assign destination address*/
	DMA_DAR0=(uint32_t)src;

	/*Do not start transfer until configuration is complete, determine source size,
	 *source increment, destination size, destination increment*/
	DMA_DCR0=0x00080000;

	/*load the length value*/
	DMA_DSR_BCR0=length;

	/*select channel source slot*/
	DMAMUX0_CHCFG0|=0x3C;

	/*Enable DMA transfer*/
	DMAMUX0_CHCFG0|=0x80;

	/*enable start bit*/
	DMA_DCR0|=0x00010000;

}

