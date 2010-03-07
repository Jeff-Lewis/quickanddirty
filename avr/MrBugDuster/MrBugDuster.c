#define F_CPU 8000000

#include <avr/io.h>          
#include <stdbool.h> 
#include <stdlib.h> 
#include <inttypes.h> 
#include <util/delay.h> 
#include <avr/interrupt.h> 


#define _TOP 2480

#define _FORWARD_LEFT (_TOP/20*2.0)
#define _FORWARD_RIGHT (_TOP/20*1.0)

#define _BACKWARD_LEFT (_TOP/20*1.0)
#define _BACKWARD_RIGHT (_TOP/20*2.0)

#define _STOP_LEFT (_TOP/20*1.5)
#define _STOP_RIGHT (_TOP/20*1.5)

int main (void) 
{ 
   DDRB |= (1<<PB4)|(1<<PB3); 
   ICR1 = _TOP; 
   OCR1A = _STOP_LEFT; 
   OCR1B = _STOP_RIGHT; 
   TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11); 
   TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11);
	while (1) {

	}
} 
