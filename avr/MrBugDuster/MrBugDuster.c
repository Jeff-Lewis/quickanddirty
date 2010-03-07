#define F_CPU 8000000UL

#include <avr/io.h>          
#include <stdbool.h> 
#include <stdlib.h> 
#include <inttypes.h> 
#include <util/delay.h> 
#include <avr/interrupt.h> 

#define _FORWARD 2
#define _BACKWARD 1
#define _STOP 0

volatile int direction = _STOP;

#define _TOP 2480

#define _FORWARD_LEFT (_TOP/20*2.0)
#define _FORWARD_RIGHT (_TOP/20*1.0)

#define _BACKWARD_LEFT (_TOP/20*1.0)
#define _BACKWARD_RIGHT (_TOP/20*2.0)

#define _STOP_LEFT (_TOP/20*1.5)
#define _STOP_RIGHT (_TOP/20*1.5)

ISR(INT0_vect) 
{
	if (direction==_STOP) {
	   	OCR1A = _BACKWARD_LEFT; 
   		OCR1B = _BACKWARD_RIGHT;
		direction = _BACKWARD;
	} else if (direction==_BACKWARD) {
	   	OCR1A = _FORWARD_LEFT; 
   		OCR1B = _FORWARD_RIGHT;
		direction = _FORWARD;
	} else {
   		OCR1A = _STOP_LEFT; 
   		OCR1B = _STOP_RIGHT;
		direction = _STOP;
	}
}

ISR(INT1_vect) 
{
   //	OCR1A = _STOP_LEFT; 
   	//OCR1B = _STOP_RIGHT;
}


int main (void) 
{ 
   PCMSK |= (1<<PIND2);
   MCUCR = (1<<ISC01) | (1<<ISC00); 
   GIMSK  |= (1<<INT0);

   DDRB ^= (1<<PB4)|(1<<PB3); 
 

   ICR1 = _TOP; 
   OCR1A = _STOP_LEFT; 
   OCR1B = _STOP_RIGHT; 
   TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11); 
   TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11);


   sei();
   

   DDRB ^= (1<<PB0)|(1<<PB1)|(1<<PB2);

	while (1) {
		if (direction==_BACKWARD) {
			PORTB ^= (1<<PB0);		
		} else if (direction==_FORWARD) {
			PORTB ^= (1<<PB1);
		} else if (direction==_STOP) {
			PORTB ^= (1<<PB2);		
		} else {
	    	PORTB &= ~(_BV(PB0)|_BV(PB1)|_BV(PB2));
		}
		_delay_ms(20);
	    PORTB &= ~(_BV(PB0)|_BV(PB1)|_BV(PB2));
		_delay_ms(20);
	}
} 
