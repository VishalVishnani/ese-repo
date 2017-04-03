/*
 * DMA.h
 *
 *  Created on: Mar 24, 2017
 *      Author: vishal
 */

#ifndef SOURCES_DMA_H_
#define SOURCES_DMA_H_

void DMA_initialize(void);
void memmove_dma_byte(uint8_t * src, uint8_t * dst, uint32_t length);
void memmove_dma_halfword(uint16_t *src,uint16_t * dst, uint32_t length);
void memmove_dma_word(uint32_t *src,uint32_t * dst, uint32_t length);
void memzero_dma_byte(uint8_t *src,uint32_t length);
void memzero_dma_halfword(uint16_t *src,uint32_t length);
void memzero_dma_word(uint32_t *src,uint32_t length);

#endif /* SOURCES_DMA_H_ */
