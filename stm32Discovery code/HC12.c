#include "stm32f4xx.h"                  // Device header
#include <stdbool.h>
#include "gpio.h"
#include "uart.h"
#include "dma.h"



void HC12_Init(void)
{
	GPIO_Alt_Func_Init(GPIOA, GPIO_PIN2_ALT_FUNCTION, GPIO_PIN2, USART_1_2_3);
	GPIO_Alt_Func_Init(GPIOA, GPIO_PIN3_ALT_FUNCTION, GPIO_PIN3, USART_1_2_3);
	USART_Init(USART2, BAUD_9600, USART_DMA_RX_ENABLE, (USART_TX_ENABLE | USART_RX_ENABLE));
}

void HC12_RxBufferInit(uint8_t* pBuffer, uint8_t bufferSize)
{
	
//	DMA_USART_Rx_Init(DMA1_Stream5, USART2, pBuffer, bufferSize, (DMA_STREAM5_CHANNEL4_SELECT | DMA_STREAM5_CIRCULAR_BUFFER |
//																																					 DMA_STREAM5_MEMORY_INC_MODE | DMA_STREAM5_ENABLE));
	DMA1_Stream5->CR &= ~DMA_SxCR_EN;
	while((DMA1_Stream5->CR & DMA_SxCR_EN) == DMA_SxCR_EN );
	DMA1_Stream5->PAR = (uint32_t)&USART2->DR;
	DMA1_Stream5->M0AR = (uint32_t)pBuffer;
	DMA1_Stream5->NDTR = bufferSize;
	DMA1->HIFCR |= DMA_HIFCR_CTCIF5;
	DMA1_Stream5->CR |= DMA_SxCR_CHSEL_2 | DMA_SxCR_MINC | DMA_SxCR_CIRC | DMA_SxCR_EN;

}



void HC12_TransmitBytes(uint8_t* bytes, uint8_t len)
{
	/*
	Description:
	
	Parameters:
	
	Return:
	
	*/
	USART_Transmit_Bytes(USART2, bytes, len);
	
}

void HC12_TransmitByte(uint8_t pData)
{
	USART_Transmit_Byte(USART2, pData);
}

bool HC12_Rx_BufferFull(void)
{
	return DMA_Rx_BufferFull(DMA1);
}

bool HC12_IncompleteRxData(void)
{
	if(USART_RxIdleLineDetected(USART2))
	{
		return true;
	}
	return false;
}


//void HC12_RxBufferErrorHandler(uint8_t* pData)
//{
//	if(pData[0] == IDLE_CHARACTER_ERROR)
//	{
//		pData[0] = 0;
//		HC12_RxBufferInit(pData, 5);
//	}
//}
