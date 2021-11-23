#include <stdbool.h>
#include <stdint.h>
#include "system.h"
#include "hc12.h"
#include "string.h"

uint8_t discoData[5] = {0};
uint8_t auxBuf[5] = {0};

int main(void)
{
	System_Init();
	HC12_Init();
	HC12_RxBufferInit(discoData, 5);
		
	while(1)
	{
		
		if(HC12_Rx_BufferFull())
		{
			System_TimerDelayMs(100);
			strcpy((char*)auxBuf, (char*)discoData);
			HC12_TransmitBytes("Hello", 5);
		}
		
		if(HC12_IncompleteRxData() || (discoData[0] == IDLE_CHARACTER))
		{
			HC12_RxBufferInit(discoData, 5);
		}		
		
	}
}
