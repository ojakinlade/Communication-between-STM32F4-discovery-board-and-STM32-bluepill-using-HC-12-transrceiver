#ifndef UART_H
#define UART_H

enum BAUD
{
	BAUD_2400 = 0xD05,
	BAUD_9600 = 0x341,
	BAUD_115200 = 0x45
	
};

#define USART_TX_ENABLE										USART_CR1_TE
#define USART_RX_ENABLE										USART_CR1_RE
#define USART_DMA_RX_ENABLE								USART_CR3_DMAR
#define USART_DMA_TX_ENABLE								USART_CR3_DMAT
#define USART_IDLE_INTERRUPT_ENABLE				USART_CR1_IDLEIE

#define USART_DMA_TX_DISABLE	0x00
#define USART_DMA_RX_DISABLE	0x01

//Initializes the USART of choice
extern void USART_Init(USART_TypeDef* uartPort, uint16_t baud, uint8_t dmaMode, uint8_t uartMode);
//Transmits single byte serial data
extern void USART_Transmit_Byte(USART_TypeDef* uartPort, uint8_t byte);

extern void USART_Transmit_Bytes(USART_TypeDef* uartPort, uint8_t* pString, uint8_t len);

extern bool USART_RxIdleLineDetected(USART_TypeDef* uartPort);


#endif /* UART_H */
