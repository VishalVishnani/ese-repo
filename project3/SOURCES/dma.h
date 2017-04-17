/**************************************************
* Authors : Vishal Vishnani, Virag Gada

* Date : 04/16/2017
*
* File : dma.h
* Description : Header file for DMA configuration
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
#include "circbuff.h"
#ifndef SOURCES_DMA_H_
#define SOURCES_DMA_H_


/****************************************************************
* DMA_initialize() - This function selects the clock for dma and
*                    enables that clock.
*****************************************************************/
void DMA_initialize(void);


/******************************************************************
* memmove_dma_byte() - This function configures dma for byte
*                       transfer
* uint8_t *src - Pointer to the start of memory to be moved.
* uint8_t *dst - Pointer to the destination memory address.
* uint32_t length - Length of the data to be moved
******************************************************************/
void memmove_dma_byte(uint8_t * src, uint8_t * dst, uint32_t length);


/******************************************************************
* memmove_dma_byte_uart() - This function configures dma for byte
*                       transfer and display on therminal through
*                       UART
* uint8_t *src - Pointer to the start of memory to be moved.
* uint8_t *dst - Pointer to the destination memory address.
* uint32_t length - Length of the data to be moved
********************************************************************/
void memmove_dma_byte_uart(uint8_t * src, uint8_t * dst, uint32_t length);


/******************************************************************
* memmove_dma_halfword() - This function configures dma for 16-bit
*                           transfer
* uint8_t *src - Pointer to the start of memory to be moved.
* uint8_t *dst - Pointer to the destination memory address.
* uint32_t length - Length of the data to be moved
********************************************************************/
void memmove_dma_halfword(uint16_t *src,uint16_t * dst, uint32_t length);


/******************************************************************
* memmove_dma_halfword() - This function configures dma for word
*                           transfer
* uint8_t *src - Pointer to the start of memory to be moved.
* uint8_t *dst - Pointer to the destination memory address.
* uint32_t length - Length of the data to be moved
*******************************************************************/
void memmove_dma_word(uint32_t *src,uint32_t * dst, uint32_t length);


/******************************************************************
* memzero_dma_byte() - This function configures dma for byte
*                           transfer to set the value to 0
* uint8_t *src - Pointer to the start of memory
* uint32_t length - Length of memory
*******************************************************************/
void memzero_dma_byte(uint8_t *src,uint32_t length);


/******************************************************************
* memzero_dma_halfword() - This function configures dma for halfword
*                           transfer to set the value to 0
* uint8_t *src - Pointer to the start of memory
* uint32_t length - Length of memory
*******************************************************************/
void memzero_dma_halfword(uint16_t *src,uint32_t length);


/******************************************************************
* memzero_dma_word() - This function configures dma for word
*                           transfer to set the value to 0
* uint8_t *src - Pointer to the start of memory
* uint32_t length - Length of memory
*******************************************************************/
void memzero_dma_word(uint32_t *src,uint32_t length);

#endif /* SOURCES_DMA_H_ */
