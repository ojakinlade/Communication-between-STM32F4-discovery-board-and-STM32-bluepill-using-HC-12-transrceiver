#include "stm32f4xx.h"                  // Device header
#include <stdbool.h>
#include "uart.h"


void USART_Init(USART_TypeDef* uartPort, uint16_t baud, uint8_t dmaMode, uint8_t uartMode)
{
	/*
	@brief:
	Initializes USART peripheral
	
	@param:
	1.) uartPort: pointer to USART_TypeDef struct which contains
	all registers for the desired USART peripheral
	e.g. if uartPort is passed an argument of USART1, the USART1 peripheral
	is configured and if passed an argument of USART2, the USART2 peripheral
	is configured etc.
	
	2.) baud: configures the baud rate of the USART peripheral. If this parameter
	is passed BAUD_9600, the baud rate is set to 9600 baud. 
	
	3.) dmaMode: enables DMA mode for transmission or reception. If passed
	USART_DMA_RX_ENABLE, the DMA is enabled for reception and if passed
	USART_DMA_TX_ENABLE, the DMA is enabled for transmisson. If both
	transmitter and receiver DMA modes are required, USART_DMA_RX_ENABLE
	and USART_DMA_TX_ENABLE must be logically ORed.
	
	4.) uartMode: enables USART for transmission or reception. If this
	parameter is passed USART_TX_ENABLE, the USART transmitter is
	enabled and if passed with USART_RX_ENABLE, the USART receiver is 
	enabled. If both transmitter and receiver are required, the USART_TX_ENABLE
	and USART_RX_ENABLE must be logically ORed.
	
	@return:
	None
	
	*/
	uartPort->CR1 |= USART_CR1_UE;
	
	switch(dmaMode)
	{
		case USART_DMA_RX_DISABLE:
			uartPort->CR3 &= ~USART_DMA_RX_ENABLE;
			break;
		case USART_DMA_TX_DISABLE:
			uartPort->CR3 &= ~USART_DMA_TX_ENABLE;
			break;
		case USART_DMA_RX_ENABLE:
			uartPort->CR3 |= USART_DMA_RX_ENABLE;
			break;
		case USART_DMA_TX_ENABLE:
			uartPort->CR3 |= USART_DMA_TX_ENABLE;
			break;
		
	}
	uartPort->BRR = baud;
	uartPort->CR1 |= uartMode;
}

void USART_Transmit_Byte(USART_TypeDef* uartPort, uint8_t byte)
{
	/*
	@brief:
	Transmits a byte of data through the Tx pin of
	the configured USART peripheral
	
	@param:
	1.) uartPort:  pointer to USART_TypeDef struct which contains
	all registers for the desired USART peripheral
	e.g. if uartPort is passed an argument of USART1, the USART1 peripheral
	is configured and if passed an argument of USART2, the USART2 peripheral
	is configured etc.
	
	2.) byte: Data to be transmitted. The data to be transmitted
	is a character or byte.
	
	@return:
	None
	
	*/
	
	while ( (uartPort->SR & USART_SR_TXE) != USART_SR_TXE);
	uartPort->DR = byte;
	
}

void USART_Transmit_Bytes(USART_TypeDef* uartPort, uint8_t* pString, uint8_t len)
{
	/*
	Description:
	Transmits multiple bytes of data through the Tx pin of
	the configured USART peripheral
	
	Parameters:
	1.) uartPort:  pointer to USART_TypeDef struct which contains
	all registers for the desired USART peripheral
	e.g. if uartPort is passed an argument of USART1, the USART1 peripheral
	is configured and if passed an argument of USART2, the USART2 peripheral
	is configured etc.
	
	2.) pString: pointer to data to be transmitted. The data to be transmitted
	is an array of characters excluding the 'NULL' character.
	
	Return:
	None
	
	*/
	uint8_t i = 0;
	
	while (i < len)
	{
		while ((uartPort->SR & USART_SR_TXE) != USART_SR_TXE);
		uartPort->DR = pString[i];
		i++;
	}
	while((uartPort->SR & USART_SR_TC) != USART_SR_TC);	
}



/**
@brief Indicates if a USART's data register contains data or not.  
@param uartPort: pointer to USART_TypeDef struct which contains all registers  
for the desired USART peripheral.  
@return true if an IDLE line is detected during data reception.  
*/
bool USART_RxIdleLineDetected(USART_TypeDef* uartPort)
{
	//volatile uint16_t readSR;
	volatile uint16_t readDR;
	bool idleLineDetected = false;
	if((uartPort->SR & USART_SR_IDLE) == USART_SR_IDLE)
	{
		idleLineDetected = true;
		//readSR = uartPort->SR;
		readDR = uartPort->DR;
	}
	return idleLineDetected;
}

