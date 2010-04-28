// juhapekka.piiroinen@gmail.com

#define BAUD 2400
#define __AVR_AT90S2313__
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <string.h>
#include <stdint.h>
#include "lcd.h"
#include "lcd.c"
//#include "uart.h"
//#include "uart.c"
//#define OW_ONE_BUS
 
//#include "onewire.h"
//#include "onewire.c"
//#include "ds18x20.h"
//#include "ds18x20.c"
 
//#define MAXSENSORS 2
//uint8_t gSensorIDs[MAXSENSORS][OW_ROMCODE_SIZE];
/*
void put_temp(const uint8_t subzero, uint8_t cel, 
	uint8_t cel_frac_bits)
{
	char buffer[sizeof(int)*8+1];
	uint16_t decicelsius;
	uint8_t i, j;
	
/	uart_putc((subzero)?'-':'+');
	uart_puti((int)cel);
	uart_puts_P(".");*
	itoa((cel_frac_bits*DS18X20_FRACCONV),buffer,10);
	j=4-strlen(buffer);
//	for (i=0;i<j;i++) uart_puts_P("0");
/*	uart_puts(buffer);
	uart_puts_P("°C [");
	// "rounding"
	uart_putc((subzero)?'-':'+');*
	decicelsius = DS18X20_temp_to_decicel(subzero, cel, cel_frac_bits);
/*	uart_puti( (int)(decicelsius/10) );
	uart_puts_P(".");
	uart_putc( (decicelsius%10) + '0');
	uart_puts_P("°C]");*
}*/

int main(void)
{ 
//	uint8_t nSensors, i;
//	uint8_t subzero, cel, cel_frac_bits; 
//ow_set_bus(&PIND,&PORTD,&DDRD,PD6);
	sei();
//		uart_init((UART_BAUD_SELECT((BAUD),F_CPU)));
    lcd_init(LCD_DISP_ON);
    lcd_clrscr();
    lcd_puts("01234567");
    lcd_puts("76543210");

    for (;;) {
//		i = gSensorIDs[0][0]; // family-code for conversion-routine
//		DS18X20_start_meas( DS18X20_POWER_PARASITE, NULL );
//		_delay_ms(DS18B20_TCONV_12BIT);
//		DS18X20_read_meas_single(i, &subzero, &cel, &cel_frac_bits);
//		put_temp(subzero, cel, cel_frac_bits);
  //      _delay_ms(1000);
    }
}