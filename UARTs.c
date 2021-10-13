/*
 * UARTs.c
 *
 * Created: 21/11/2017 03:11:35 p. m.
 *  Author: abdias
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>


#define BS 0x08 // Backspace
#define CR 0x0D  //Enter
#define SPC 0x20 //Espacio


// BAUDRATE ((F_CPU)/(BAUD*16UL)-1)


void UART0_Init()
{
	UBRR0 = 103; //9600
	
	//Habilitar transmision y recepcion
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	// 8 bits, No paridad
	UCSR0C |= ((1 << UCSZ01)| (1<< UCSZ00));
}

void configurarPuertoSerie(char uart, unsigned long int baudaje, char tamDato, char paridad, char bitParo)
{
	unsigned int ubrr = 0;
	
	//ubrr = (F_OSC/(16*baudaje))-1;
	
	switch(uart)
	{
		case '1':
		UBRR0 = baudaje;
		
		//UARTs_Init(uart0, ubrr, tamDato, bitParo);
		break;
		case '2':
		//UARTs_Init(uart1, ubrr, tamDato, bitParo);
		break;
		case '3':
		//UARTs_Init(uart2, ubrr, tamDato, bitParo);
		break;
		case '4':
		//UARTs_Init(uart3, ubrr, tamDato, bitParo);
		break;
	}
}

void UART0_putchar(char data)
{
	while(!(UCSR0A &(1<< UDRE0)));
	UDR0 = data;
}

void UART0_puts(char *str)
{
	while(*str != '\0')
	{
		UART0_putchar(*str++);
	}
}


//Retorna BYTE recibido pro el puerto serie UART0
unsigned char UART0_getchar(void)
{
	while(!(UCSR0A & (1<<RXC0))); //SI la recepcion esta completa
	return UDR0;
}

void UART0_gets(char *str)
{
	unsigned char data;
	unsigned int lenght = 0;

	while ((data = UART0_getchar()) != 0x0D)
	{
		if(data != 0x08 && lenght <60)
		{
			*str = data;
			UART0_putchar(data);
			str++;
			lenght++;
		}
		else if(lenght >0)
		{
			UART0_putchar(BS);
			UART0_putchar(32);
			UART0_putchar(BS);
			str--;
			lenght--;
		}
	}
	*str = '\0';
}

//////////////////////////////////////////////////////////////////////////
///////////////////Para UART GENERICO   ///////////////////////////////////////////////
void UARTs_Init(uint8_t *direccion)
{
	*(direccion+4) = 103; //Calcular el baudaje
	
	//Registro UCSRnB
	*(direccion+1) = (1 << 3)|(1 << 4); //Transmision y Recepcion

	//Registro UCSRnA
	// *(direccion) = (1 << 1); //Velocidad transmision doble

	//Configurar Regsitro UCSRnC
	// Dato_size(direccion, dato_size);
	*(direccion+2) = (1<<2)|(1<<1);
}
void UARTs_putchar(char data, uint8_t *direccion)
{
	while( ! ( (*direccion)& (1<<UDRE0) ) );
	*(direccion+6)= data;
	//while(!(UCSR0A &(1<< UDRE0)));
	//UDR0 = data;
}

void UARTs_puts(char *str, uint8_t *direccion)
{
	while(*str != '\0')
	{
		UARTs_putchar(*str++, direccion);
	}
}

unsigned char UARTs_getchar(uint8_t *direccion)
{
	while(!(*(direccion)&(1<<RXC0))); //SI la recepcion esta completa
	return *(direccion+6);
	//while(!(UCSR0A & (1<<RXC0))); //SI la recepcion esta completa
	//return UDR0;
}

void UARTs_gets(char *str, uint8_t *direccion)
{
	unsigned char data;
	unsigned int lenght = 0;

	while ((data = UARTs_getchar(direccion)) != 0x0D)
	{
		if(data != 0x08 && lenght <60)
		{
			*str = data;
			UARTs_putchar(data, direccion);
			str++;
			lenght++;
		}
		else if(lenght >0)
		{
			UARTs_putchar(BS, direccion);
			UARTs_putchar(32, direccion);
			UARTs_putchar(BS, direccion);
			str--;
			lenght--;
		}
	}
	*str = 0;
}