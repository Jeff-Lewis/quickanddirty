#define F_CPU 8000000UL

#include <avr/io.h>          
#include <stdbool.h> 
#include <stdlib.h> 
#include <inttypes.h> 
#include <util/delay.h> 
#include <avr/interrupt.h> 

int direction = 0;

#define _TOP 2480

#define _FORWARD_LEFT (_TOP/20*2.0)
#define _FORWARD_RIGHT (_TOP/20*1.0)

#define _BACKWARD_LEFT (_TOP/20*1.0)
#define _BACKWARD_RIGHT (_TOP/20*2.0)

#define _STOP_LEFT (_TOP/20*1.5)
#define _STOP_RIGHT (_TOP/20*1.5)

ISR(INT0_vect) 
{
   	OCR1A = _BACKWARD_LEFT; 
   	OCR1B = _BACKWARD_RIGHT;
}

ISR(INT1_vect) 
{
   	OCR1A = _STOP_LEFT; 
   	OCR1B = _STOP_RIGHT;
}


int main (void) 
{ 
   PCMSK |= (1<<PIND2)|(1<<PIND3);
   MCUCR = (1<<ISC01) | (1<<ISC00); 
   GIMSK  |= (1<<INT0)|(1<<INT1);

   DDRB ^= (1<<PB4)|(1<<PB3); 

   ICR1 = _TOP; 
   OCR1A = _STOP_LEFT; 
   OCR1B = _STOP_RIGHT; 
   TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11); 
   TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11);

   sei();

	while (1) {

	}
} 
