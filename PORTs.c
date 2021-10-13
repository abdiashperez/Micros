/*
 * PORTs.c
 *
 * Created: 21/11/2017 03:24:51 p. m.
 *  Author: abdias
 */ 
#include <avr/io.h>

void InicializarPuertos()
{
	DDRF = 0x00; // Puerto F de salida 
	PORTF = 0x00;// Pull ups desactivado
	//UART0_puts("***Inicializar puertos***\r\n");
}
void ConfigurarPuerto(unsigned int portPin, unsigned int valor)
{
	//PrintDec2d(portPin);
	//PrintDec2d(valor);
	 
	if(valor == 1) // Salida
	{
		DDRF |= (1<<portPin);
	}
	if(valor == 0) //Entrada
	{
		DDRF &=~(1<<portPin);
	}
	//UART0_puts("***Configurar puerto***\r\n");
}

void EscrituraPuerto(unsigned int portPin, unsigned int bitx)
{
	
	if(bitx == 1)//Escribir 1 en el puerto
	{
		PORTF |= (1<<portPin);
	}
	if(bitx == 0 )
	{
		PORTF &=~(1<<portPin);
	}
	//UART0_puts("***Escritura puerto***\r\n");
}


void leerPuerto(uint8_t portPin)
{
	unsigned int dato ;
	char valor[20] ={'\0'};
	
	dato = PINF &(1<<portPin);  // Leer atravez de pin cuando esta de entrada
	itoa(valor, dato, 16);
	//PrintDec2d(dato);
	UART0_puts(valor);
}