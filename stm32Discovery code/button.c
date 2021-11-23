#include "stm32f4xx.h"                  // Device header
#include "stdbool.h"
#include "system.h"
#include "gpio.h"
#include "button.h"


void Button_Init(void)
{
	GPIO_Input_Init(GPIOA, GPIO_PIN0, false);

}

static bool Debounce(Button_t* pButton)
{
	pButton->state = GPIO_Input_Read(GPIOA, pButton->pin);
	if(pButton->state == BUTTON_PRESSED)
	{
		System_Timer_DelayMs(100);
		if(pButton->state == BUTTON_PRESSED)
		{
			return true;
		}
	}
	return false;
}

void Poll(Button_t* pButton)
{
	
	pButton->isDebounced = Debounce(pButton);
	
}




