//////////////////////////////////////////
// Title: jpiiRelay
// Description:
//		Shutdown TV and other devices remotely.
//
// Author: Juhapekka Piiroinen
// License: GNU/GPLv3
// Date: 1.5.2010
//----------------------------------------
// Contact: juhapekka.piiroinen@gmail.com
//////////////////////////////////////////
#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>

#define PWR_BTN_PORT PORTB
#define PWR_BTN_PIN PINB
#define PWR_BTN_BIT PB0

#define RLY_PORT PORTD
#define RLY_DDR DDRD
#define RLY_BIT PD6

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
}

int main(void)
{
	RLY_DDR = _BV(RLY_BIT);
	PWR_BTN_PORT |= _BV(PWR_BTN_BIT);

	for (;;) {
		if (button_is_pressed()) {
			toggle_relay();
			_delay_ms(500);
		}
	}
}
