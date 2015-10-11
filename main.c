/*
 * main.c
 *
 *  Created on: Oct 11, 2015
 *      Author: JohnnyP
 *      http://www.avrfreaks.net/forum/tut-c-newbies-guide-avr-adc
 *      https://www.youtube.com/watch?v=sVvDiACf3yE&list=PLE72E4CFE73BD1DE1&index=31
 *      Data sheet page 122
 */

#include <avr/io.h>
#include <avr/interrupt.h>

int main (void)
{
	DDRB |= (1 << PINB3);	// LED indicator Pin #2
	// No MUX values needed to be changed to use ADC0. ADC0 is on the Pin #1
	ADCSRA |= (1 << ADPS2);	// Set ADC prescaler to 16 what gives 62.5 kHz sample rate @ 1 MHz
	ADMUX |= (1 << REFS0); 	// Set ADC reference to AVCC
	ADMUX |= (1 << ADLAR); 	// Left adjust ADC result to allow easy 8 bit reading
	ADCSRA |= (1 << ADIE);  // Enable ADC Interrupt
	ADCSRA |= (1 << ADEN);  // Enable ADC
	sei();					// Enable Global Interrupts
	ADCSRA |= (1 << ADSC);  // Start ADC Conversion

	while(1)
	{
	}
}

ISR(ADC_vect)
{
	if(ADCH < 128)
	{
		PORTB &= ~(1 << PINB3); // Turn off LED
	}
	else
	{
		PORTB |= (1 << PINB3); 	// Turn on LED
	}

	ADCSRA |= (1 << ADSC);  	// Start next ADC Conversion
}
