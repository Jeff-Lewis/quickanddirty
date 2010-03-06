#include <avr/io.h> 
#include <avr/interrupt.h> 

int main (void) 
{ 
   DDRB |= (1 << DDB0); // Set LED as output 

   TIMSK |= (1 << TOIE1); // Enable overflow interrupt 
   sei(); // Enable global interrupts 

   TCNT1 = 49911; // Preload timer with precalculated value 

   TCCR1B |= ((1 << CS10) | (1 << CS11)); // Set up timer at Fcpu/64 

   for (;;) 
   { 

   } 
} 

ISR(TIMER1_OVF_vect) 
{ 
   PORTB ^= (1 << PORTB0); // Toggle the LED 
   TCNT1  = 49911; // Reload timer with precalculated value 
}