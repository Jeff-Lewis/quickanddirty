// juhapekka.piiroinen@gmail.com

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

extern void LCD_Init(void);

int main(void)
{ 
    sei();
    LCD_Init();
    for (;;) {

    }
}
