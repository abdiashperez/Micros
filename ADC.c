#include <avr/io.h>
#include "Strings.h"

void ADC_INI(uint8_t pin)
{
	//Voltaje de referencia interna del uC = 5v
	ADMUX |= (1<<REFS0); 
	
	/*Ativar el convertidor analogico  y usar prescalador 128*/
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)| (1<<ADPS1)| (1<<ADPS0);
	
}

void BitSalida(uint8_t pin)
{
	//Elegir el canal por donde va a salir
	switch(pin)
	{
		case '0':
			ADCSRB = 0x20;	
			break;
		case '1':
			ADCSRB = 0x21;
			break;
		case '2':
			ADCSRB = 0x22;
			break;
		case '3':
			ADCSRB = 0x23;
			break;
		case '4':
			ADCSRB = 0x24;
			break;
		case '5':
			ADCSRB = 0x25;
			break;
		case '6':
			ADCSRB = 0x26;
			break;
		case '7':
			ADCSRB = 0x27;
			break;
	}
	
}

unsigned int ADC_LEER(void)
{ 
	UART0_puts("obtener  valor");
	ADCSRA |= (1<<ADSC);//Inicia la conversion
	 /* Espera hasta completar la conversion - ADIF se usa como bandera*/
	while (!(ADCSRA & (1<<ADIF)))
	ADCSRA |= (1<<ADIF);
	
	return (ADC);
}