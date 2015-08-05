# WORK IN PROGRESS #
this article is not finalized yet. I am currently planning and making mistakes. When things are working, I will document the progress and notes here for later usage. feel free to use for your own usage as well.




# Introduction #

The idea is to create a i<sup>2</sup>c master device with ATtiny2313 which could be then commanded using hardware UART from a PC/MAC. This kind of debugging devices are already out there in the markets, but this should be relatively easy practice for everyone who are interested in the protocol itself and the 8-bit MCU's.

## What is ATtiny2313? ##
![http://upload.wikimedia.org/wikipedia/commons/thumb/8/86/ATtiny2313.png/240px-ATtiny2313.png](http://upload.wikimedia.org/wikipedia/commons/thumb/8/86/ATtiny2313.png/240px-ATtiny2313.png)![http://quickanddirty.googlecode.com/files/attiny2313.png](http://quickanddirty.googlecode.com/files/attiny2313.png)
![http://quickanddirty.googlecode.com/files/avr_isp.jpg](http://quickanddirty.googlecode.com/files/avr_isp.jpg) <br />
[ATtiny2313](http://www.atmel.com/dyn/resources/prod_documents/doc2543.PDF) is a low power 8-bit microcontroller.
  * 2KB of In-System Self-Programmable Flash
  * 128 Bytes In-System Programmable EEPROM
  * 128 Bytes Internal SRAM
  * USI-Universal Serial Interface
  * Full Duplex UART.

## What I<sup>2</sup>C stands for? ##
![http://upload.wikimedia.org/wikipedia/commons/thumb/3/3e/I2C.svg/350px-I2C.svg.png](http://upload.wikimedia.org/wikipedia/commons/thumb/3/3e/I2C.svg/350px-I2C.svg.png)<br />

I<sup>2</sup>C is a multi-master serial single-ended computer bus invented by Philips that is used to attach low-speed peripherals to a motherboard, embedded system, or cellphone. Since the mid 1990s several competitors (e.g. Siemens AG (later Infineon Technologies AG), NEC, Texas Instruments, STMicroelectronics (formerly SGS-Thomson), Motorola (later Freescale), Intersil, etc.) brought I²C products on the market, which are fully compatible with the NXP (formerly Philips' semiconductor division) I²C-system. As of October 1, 2006, no licensing fees are required to implement the I²C protocol. However, fees are still required to obtain I²C slave addresses allocated by NXP
  * read more @ [wikipedia](http://en.wikipedia.org/wiki/I%C2%B2C).
# UART #
**Always** use external oscillator for time critical tasks.
## block diagram ##
![http://quickanddirty.googlecode.com/files/avr-uart-blockdiagram.png](http://quickanddirty.googlecode.com/files/avr-uart-blockdiagram.png)
## registers ##
![http://quickanddirty.googlecode.com/files/attiny2313-uart-registers2.png](http://quickanddirty.googlecode.com/files/attiny2313-uart-registers2.png)
### USART I/O Data Register – UDR ###
The USART Transmit Data Buffer Register and USART Receive Data Buffer Registers share the
same I/O address referred to as USART Data Register or UDR. The Transmit Data Buffer Register
(TXB) will be the destination for data written to the UDR Register location. Reading the
UDR Register location will return the contents of the Receive Data Buffer Register (RXB).
For 5-, 6-, or 7-bit characters the upper unused bits will be ignored by the Transmitter and set to
zero by the Receiver.
The transmit buffer can only be written when the UDRE flag in the UCSRA Register is set. Data
written to UDR when the UDRE flag is not set, will be ignored by the USART Transmitter. When
data is written to the transmit buffer, and the Transmitter is enabled, the Transmitter will load the
data into the Transmit Shift Register when the Shift Register is empty. Then the data will be serially
transmitted on the TxD pin.
The receive buffer consists of a two level FIFO. The FIFO will change its state whenever the
receive buffer is accessed. Due to this behavior of the receive buffer, do not use Read-Modify-
Write instructions (SBI and CBI) on this location. Be careful when using bit test instructions
(SBIC and SBIS), since these also will change the state of the FIFO.
### USART Control and Status Register A – UCSRA ###
#### Bit 7 – RXC: USART Receive Complete ####
This flag bit is set when there are unread data in the receive buffer and cleared when the receive
buffer is empty (i.e., does not contain any unread data). If the Receiver is disabled, the receive
buffer will be flushed and consequently the RXC bit will become zero. The RXC flag can be used
to generate a Receive Complete interrupt (see description of the RXCIE bit).
#### Bit 6 – TXC: USART Transmit Complete ####
This flag bit is set when the entire frame in the Transmit Shift Register has been shifted out and
there are no new data currently present in the transmit buffer (UDR). The TXC flag bit is automatically
cleared when a transmit complete interrupt is executed, or it can be cleared by writing
a one to its bit location. The TXC flag can generate a Transmit Complete interrupt (see description
of the TXCIE bit).
#### Bit 5 – UDRE: USART Data Register Empty ####
The UDRE flag indicates if the transmit buffer (UDR) is ready to receive new data. If UDRE is
one, the buffer is empty, and therefore ready to be written. The UDRE flag can generate a Data
Register Empty interrupt (see description of the UDRIE bit).
UDRE is set after a reset to indicate that the Transmitter is ready.
#### Bit 4 – FE: Frame Error ####
This bit is set if the next character in the receive buffer had a Frame Error when received. I.e.,
when the first stop bit of the next character in the receive buffer is zero. This bit is valid until the
receive buffer (UDR) is read. The FE bit is zero when the stop bit of received data is one. Always
set this bit to zero when writing to UCSRA.
#### Bit 3 – DOR: Data OverRun ####
This bit is set if a Data OverRun condition is detected. A Data OverRun occurs when the receive
buffer is full (two characters), it is a new character waiting in the Receive Shift Register, and a
new start bit is detected. This bit is valid until the receive buffer (UDR) is read. Always set this bit
to zero when writing to UCSRA.
#### Bit 2 – UPE: USART Parity Error ####
This bit is set if the next character in the receive buffer had a Parity Error when received and the
Parity Checking was enabled at that point (UPM1 = 1). This bit is valid until the receive buffer
(UDR) is read. Always set this bit to zero when writing to UCSRA.
#### Bit 1 – U2X: Double the USART Transmission Speed ####
This bit only has effect for the asynchronous operation. Write this bit to zero when using synchronous
operation.
Writing this bit to one will reduce the divisor of the baud rate divider from 16 to 8 effectively doubling
the transfer rate for asynchronous communication.
#### Bit 0 – MPCM: Multi-processor Communication Mode ####
This bit enables the Multi-processor Communication mode. When the MPCM bit is written to
one, all the incoming frames received by the USART Receiver that do not contain address information
will be ignored. The Transmitter is unaffected by the MPCM setting.
### USART Control and Status Register B – UCSRB ###
#### Bit 7 – RXCIE: RX Complete Interrupt Enable ####
Writing this bit to one enables interrupt on the RXC flag. A USART Receive Complete interrupt
will be generated only if the RXCIE bit is written to one, the Global Interrupt Flag in SREG is written
to one and the RXC bit in UCSRA is set.
#### Bit 6 – TXCIE: TX Complete Interrupt Enable ####
Writing this bit to one enables interrupt on the TXC flag. A USART Transmit Complete interrupt
will be generated only if the TXCIE bit is written to one, the Global Interrupt Flag in SREG is written
to one and the TXC bit in UCSRA is set.
#### Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable ####
Writing this bit to one enables interrupt on the UDRE flag. A Data Register Empty interrupt will
be generated only if the UDRIE bit is written to one, the Global Interrupt Flag in SREG is written
to one and the UDRE bit in UCSRA is set.
#### Bit 4 – RXEN: Receiver Enable ####
Writing this bit to one enables the USART Receiver. The Receiver will override normal port operation
for the RxD pin when enabled. Disabling the Receiver will flush the receive buffer
invalidating the FE, DOR, and UPE Flags.
#### Bit 3 – TXEN: Transmitter Enable ####
Writing this bit to one enables the USART Transmitter. The Transmitter will override normal port
operation for the TxD pin when enabled. The disabling of the Transmitter (writing TXEN to zero)
will not become effective until ongoing and pending transmissions are completed, i.e., when the
Transmit Shift Register and Transmit Buffer Register do not contain data to be transmitted.
When disabled, the Transmitter will no longer override the TxD port.
#### Bit 2 – UCSZ2: Character Size ####
The UCSZ2 bits combined with the UCSZ1:0 bit in UCSRC sets the number of data bits (Character
SiZe) in a frame the Receiver and Transmitter use.
#### Bit 1 – RXB8: Receive Data Bit 8 ####
RXB8 is the ninth data bit of the received character when operating with serial frames with nine
data bits. Must be read before reading the low bits from UDR.
#### Bit 0 – TXB8: Transmit Data Bit 8 ####
TXB8 is the ninth data bit in the character to be transmitted when operating with serial frames
with nine data bits. Must be written before writing the low bits to UDR.
### USART Control and Status Register C - UCSRC ###
#### Bit 6 – UMSEL: USART Mode Select ####
This bit selects between asynchronous and synchronous mode of operation.

|UMSEL| Mode|
|:----|:----|
|0    | Asynchronous Operation|
|1    | Synchronous Operation|

#### Bit 5:4 – UPM1:0: Parity Mode ####
These bits enable and set type of parity generation and check. If enabled, the Transmitter will automatically generate and send the parity of the transmitted data bits within each frame. The Receiver will generate a parity value for the incoming data and compare it to the UPM0 setting.
If a mismatch is detected, the UPE Flag in UCSRA will be set.

| UPM1|  UPM0|  Parity Mode|
|:----|:-----|:------------|
| 0   |  0   |  Disabled   |
| 0   |  1   |  Reserved   |
| 1   |  0   |  Enabled, Even Parity|
| 1   |  1   |  Enabled, Odd Parity|

#### Bit 3 – USBS: Stop Bit Select ####
This bit selects the number of stop bits to be inserted by the Transmitter. The Receiver ignores this setting.

|USBS| Stop Bit(s)|
|:---|:-----------|
|0   | 1-bit      |
|1   | 2-bit      |

#### Bit 2:1 – UCSZ1:0: Character Size ####
The UCSZ1:0 bits combined with the UCSZ2 bit in UCSRB sets the number of data bits (Character SiZe) in a frame the Receiver and Transmitter use.

|UCSZ2| UCSZ1| UCSZ0| Character Size|
|:----|:-----|:-----|:--------------|
|0    | 0    | 0    | 5-bit         |
|0    | 0    | 1    | 6-bit         |
|0    | 1    | 0    | 7-bit         |
|0    | 1    | 1    | 8-bit         |
|1    | 0    | 0    | Reserved      |
|1    | 0    | 1    | Reserved      |
|1    | 1    | 0    | Reserved      |
|1    | 1    | 1    | 9-bit         |

#### Bit 0 – UCPOL: Clock Polarity ####
This bit is used for synchronous mode only. Write this bit to zero when asynchronous mode is used. The UCPOL bit sets the relationship between data output change and data input sample, and the synchronous clock (XCK).

|UCPOL|Transmitted Data Changed (Output of TxD Pin)|Received Data Sampled (Input on RxD Pin)|
|:----|:-------------------------------------------|:---------------------------------------|
|0    | Rising XCK Edge                            |Falling XCK Edge                        |
|1    | Falling XCK Edge                           |Rising XCK Edge                         |

### USART Baud Rate Registers – UBRRL and UBRRH ###
#### Bit 15:12 – Reserved Bits ####
These bits are reserved for future use. For compatibility with future devices, these bit must be written to zero when UBRRH is written.
#### Bit 11:0 – UBRR11:0: USART Baud Rate Register ####
This is a 12-bit register which contains the USART baud rate. The UBRRH contains the four
most significant bits, and the UBRRL contains the eight least significant bits of the USART baud rate. Ongoing transmissions by the Transmitter and Receiver will be corrupted if the baud rate is changed. Writing UBRRL will trigger an immediate update of the baud rate prescaler.
## Code snippets ##
### UBRR register - setting baud rate ###
![http://quickanddirty.googlecode.com/files/avr-UBRR.png](http://quickanddirty.googlecode.com/files/avr-UBRR.png)
### Init 2400 8 n 1 / F\_CPU 16MHz ###
```
#define BAUDMODE 416 //value from datasheet.
UBRRL = BAUDMODE;
UBRRH = (BAUDMODE >> 8);

// enable tx and rx
UCSRB = (1<<TXEN) | (1<<RXEN);
```

### Receive data without using an INT ###
```
while (!(UCSRA & (1<<RXC)) );
received_data = UDR;
```

### Transmit data without using an INT ###
```
while (!(UCSRA & (1<<UDRE)) );
UDR = data_to_be_sent;
```

### Echo uart with interrupt ###
```
#define F_CPU 16000000UL
#define UART_BAUDMODE 416

#include <avr/io.h>
#include <avr/interrupt.h>

void UART_Init() {
	// lets set the baud rate
	UBRRL = (unsigned char)UART_BAUDMODE;
	UBRRH = (UART_BAUDMODE >> 8);

	// enable tx and rx
	UCSRB = (1<<TXEN) | (1<<RXEN);

	// lets enable RX interrupt
	UCSRB |= (1 << RXCIE);

	// enable interrupts
	sei();
}

// basic echo serial sw
ISR(USART_RX_vect) {
	char receivedByte;
	receivedByte = UDR;
	UDR = receivedByte;
}

int main(void) {
	unsigned char isRunning = 1;

	UART_Init();

	while (isRunning) {
		
	}
	return 0;
}

```
### Memory Usage ###
```
AVR Memory Usage
----------------
Device: attiny2313

Program:     106 bytes (5.2% Full)
(.text + .data + .bootloader)

Data:          0 bytes (0.0% Full)
(.data + .bss + .noinit)
```
# Details #

Checklist
  * Search and read Atmel Application Notes **check**
    * [AVR310](http://atmel.com/dyn/resources/prod_documents/doc2561.pdf): Using the USI module as a I2C master [src](http://atmel.com/dyn/resources/prod_documents/AVR310.zip)
    * [AVR244](http://atmel.com/dyn/resources/prod_documents/doc2547.pdf): AVR UART as ANSI Terminal Interface [src](http://atmel.com/dyn/resources/prod_documents/AVR244.zip)
    * [AVR303](http://atmel.com/dyn/resources/prod_documents/doc2557.pdf): SPI-UART Gateway [src](http://atmel.com/dyn/resources/prod_documents/AVR303.zip)
  * Research the devices in the application notes **in progress**
  * Combine information from the application notes into a single black box device
  * add UART to USB chip for better usability
  * make a crossplatform UI for the hardware
    * make a commandline prototype with Python to validate the hardware functionality
    * make C++/Qt interface for the gateway.

# Notes for myself #
  * use external oscillator! the most vital part of the communication.. n00b.. For ATtiny2313 the related UART baud rate table is Table 57. Attach it here for future usage.
  * V-usb as UART to USB gateway, should run with ATtiny2313.

## the plan ##
**PC/MAC**  => (usb)  =>  **2313 with vusb**  => (uart) =>  **2313 with uart**

or

**PC/MAC**  => (usb)  =>  **ftdi U232R**  => (uart) =>  **2313 with uart**

# Existing products #
[BusPirate](http://code.google.com/p/the-bus-pirate/) is a really good product and which should be bought, but as i have several AVR 8-bit MCU's available I could make similar device using them, which would be then _free_ for me.