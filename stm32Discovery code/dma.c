#include "stm32f4xx.h"                  // Device header
#include <stdbool.h>
#include "dma.h"
#include <string.h>


void DMA_USART_Rx_Init(DMA_Stream_TypeDef* dmaStream, 
															USART_TypeDef* uartPort, 
															uint8_t* uartRxBuffer, 
															uint32_t bufferSize, 
															uint32_t dmaConfig)
														
{
	
	dmaStream->PAR = (uint32_t)&uartPort->DR;
	dmaStream->M0AR = (uint32_t)uartRxBuffer;
	dmaStream->NDTR = bufferSize;
	DMA1->HIFCR |= DMA_HIFCR_CTCIF5;
	dmaStream->CR |= dmaConfig;
	
}	


uint8_t DMA_Rx_NDTR(DMA_Stream_TypeDef* dmaChannel)
{
	return dmaChannel->NDTR;
}


bool DMA_Rx_BufferFull(DMA_TypeDef* dmaPort)
{
	bool bufferIsFull = false;
//	uint8_t bitLocation;
//	switch(streamNumber)
//	{
//		case DMA_STREAM5:
//			bitLocation = 11;
//		break;
//	}
	
	if((dmaPort->HISR & DMA_HISR_TCIF5) == DMA_HISR_TCIF5)
	{
		bufferIsFull = true;
		dmaPort->HIFCR |= DMA_HIFCR_CTCIF5;
	}
	return bufferIsFull;
}
