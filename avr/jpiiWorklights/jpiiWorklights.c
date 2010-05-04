//////////////////////////////////////////
// Title: jpiiWorklights
// Description:
//		Switch lights at the work area on/off.
//
// Bugs:
//		Only one input button is used.
//
// Author: Juhapekka Piiroinen
// License: GNU/GPLv3
// Date: 2.5.2010
//----------------------------------------
// Contact: juhapekka.piiroinen@gmail.com
//////////////////////////////////////////
#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define PWR_BTN_PORT PORTB
#define PWR_BTN_PIN PINB
#define PWR_BTN_BIT PB0

#define RLY_PORT PORTD
#define RLY_DDR DDRD
#define RLY_BIT PD6

#define RLY2_PORT PORTB
#define RLY2_DDR DDRB
#define RLY2_BIT PB3

void toggle_relay();
int button_is_pressed();

int button_is_pressed() {
	if (bit_is_clear(PWR_BTN_PIN, PWR_BTN_BIT)) {
		_delay_ms(100);
		if (bit_is_clear(PWR_BTN_PIN, PWR_BTN_BIT)) return 1;
	}
	return 0;
}

void toggle_relay() {
	RLY_PORT ^= _BV(RLY_BIT);
	RLY2_PORT ^= _BV(RLY2_BIT);
}

ISR(PCINT0_vect){
    cli();
}

int main(void)
{
    GIMSK |= 1<< PCIE;
    PCMSK |= 1<< PCINT0;

	RLY_DDR = _BV(RLY_BIT);
	RLY2_DDR = _BV(RLY2_BIT);

	PWR_BTN_PORT |= _BV(PWR_BTN_BIT);

	for (;;) {
		sei();
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		sleep_mode();
		if (button_is_pressed()) {
			toggle_relay();
		}
	}
}
