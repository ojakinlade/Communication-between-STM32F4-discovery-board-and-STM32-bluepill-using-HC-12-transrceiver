#ifndef BUTTON_H
#define BUTTON_H

#define BUTTON_PIN 		0

#define BUTTON_PRESSED 				1
#define BUTTON_NOT_PRESSED 		0

typedef struct
{
	uint8_t pin;
	bool state;
	bool prevPressed;
	bool isDebounced;
}Button_t;

extern void Button_Init(void);
extern void Poll(Button_t* pButton);

#endif /* BUTTON_H */
