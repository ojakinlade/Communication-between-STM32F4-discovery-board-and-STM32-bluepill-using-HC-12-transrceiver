#include <stdbool.h>
#include <stdint.h>
#include "system.h"
#include "HC12.h"
#include "button.h"

uint8_t bluePillData[5] = {0};
Button_t button = {BUTTON_PIN, BUTTON_NOT_PRESSED, false};
uint32_t timestamp1 = 0;
uint32_t timestamp2 = 0;

int main(void)
{
	System_Init();
	Button_Init();
	HC12_Init();
	HC12_RxBufferInit(bluePillData, 5);
	
	while(1)
	{
		Poll(&button);
		if(button.isDebounced && !button.prevPressed)
		{
			HC12_TransmitBytes("Hello", 5);
			timestamp1 = System_GetTick();
			button.prevPressed = true;
		}
		else if(!button.isDebounced && button.prevPressed)
		{
			button.prevPressed = false;
		}
		
		if(HC12_Rx_BufferFull())
		{
			timestamp2 = System_GetTick();
		}
		
		if(HC12_IncompleteRxData() || (bluePillData[0] == IDLE_CHARACTER))
		{
			HC12_RxBufferInit(bluePillData, 5);
		}	
		
	}
}