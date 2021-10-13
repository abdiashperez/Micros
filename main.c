/*
 * ExamenEspecial.c
 *
 * Created: 21/11/2017 03:10:19 p. m.
 * Author : abdias
 */ 
#include <avr/io.h>
#include "UARTs.h"
#include "Strings.h"
#include "PORTs.h"
#include "ADC.h" 
#define SPC 0x20

unsigned int Comparar_Comandos(char renglon[20], const char tokens_comandos[10][5]);
void ValidarAtributos(unsigned int renglon, char matriz_separada[20][20]);
int AtributosValidos(const int tokens_atributos[10], char matriz_separada[20][20]);
int ValidarNumero(char cadena, char min, char max);
int ValidarNumero_MayorCero(char* renglon);
int ValidarBaudaje(unsigned long baud);


//Comandos Validos
const char tokens_comandos[10][5]= {"wb","cb","rb","cfs","send","wp", "rp","ra", "\x0"};
const int tokens_atributos[10][10]={{1,2}, {1,2},{1},{3, 4, 5, 6, 7},{3,8},{9},{2},{10}};
int main(void)
{
       char cadena_separada[20][20]={""};
       char cad_original[20]={'\0'};
       char cad_copia[20]={'\0'};
       unsigned int comparacion = 0;
       
       UART0_Init();
	   InicializarPuertos();
	   ADC_INI(0);
	   
      UART0_puts("***Inicio***\r\n");
    while (1) 
    {
		UART0_gets(cad_original);
		UART0_puts("\r\n");
		if(cad_original[0] != '\0')
		{
			strcopy(cad_original, cad_copia);
			LimpiarCadena(cad_copia, SPC);
			separarCadena(cad_copia, cadena_separada);
			comparacion = Comparar_Comandos(cadena_separada, tokens_comandos);
			if(comparacion != 0)
			{
			   ValidarAtributos(comparacion,cadena_separada);
			}
			else
			{
				UART0_puts("Comando Incorrecto");
				UART0_puts("\r\n");
			}
		}
		else
		{
			UART0_puts("\r\n");
		}
    }
	
	return 0;
}
unsigned int Comparar_Comandos(char renglon[20], const char tokens_comandos[10][5])
{
	unsigned int i=0;

	while(i<8)
	{
		if(str_cmp(tokens_comandos[i], renglon) == 0)
		{
			return i+1;
		}
		i++;
	}
	i = 0;
	return i;
}
void ValidarAtributos(unsigned int renglon, char matriz_separada[20][20])
{
	unsigned int valor = 0;
	UART0_puts("\r\n");
	switch (renglon - 1)
	{

		case 0:
			//Escritura del puerto wb
			valor=AtributosValidos(tokens_atributos[0], matriz_separada);
			if ( valor != 0)
			{
				unsigned int puerto = matriz_separada[1][1]-48;
				unsigned int pin = matriz_separada[2][0]-48;
				EscrituraPuerto(puerto, pin);
			}
			else
			{
				UART0_puts("Comando Desconocido");
				UART0_puts("\r\n");
			}
		break;
					
		case 1:
		//Configuracion del puerto
			if ((AtributosValidos(tokens_atributos[1], matriz_separada))==1)
			{
				unsigned int puertoPin = matriz_separada[1][1]-48;
				unsigned int valor = matriz_separada[2][0]-48;
			
				ConfigurarPuerto(puertoPin, valor);
			}
			else
			{
				UART0_puts("Comando Desconocido");
				UART0_puts("\r\n");
			}
		break;
		
		case 2:
		//Lectura puerto
			valor = AtributosValidos(tokens_atributos[2], matriz_separada);
			//PrintDec2d(valor);wb 
			if (valor !=0)
			{
				
				uint8_t puerto = matriz_separada[1][1]-48;
				leerPuerto(puerto); 
				UART0_puts("\r\n");
			}
			else
			{
				UART0_puts("Comando Desconocido");
				UART0_puts("\r\n");
			}
		break;
		

		case 3:
			if((AtributosValidos(tokens_atributos[3], matriz_separada)) == 1)
			{
				UART0_puts("Configurar UART");
			}
			else
			{
				UART0_puts("Comando Desconocido");
				UART0_puts("\r\n");
			}
		break;
		
		case 4:
			if((AtributosValidos(tokens_atributos[4], matriz_separada)) == 1)
			{
				UART0_puts("Imprimir cadena");
			}
			else
			{
				UART0_puts("Comando Desconocido");
				UART0_puts("\r\n");
			}
			break;
		
		case 5:
			if((AtributosValidos(tokens_atributos[5], matriz_separada)) == 1)
			{
				UART0_puts("Configurar PWM");
			}
			else
			{
				UART0_puts("Comando Desconocido");
				UART0_puts("\r\n");
			}
		break;
		
		case 6:
				//UART0_puts("Comando rp");
		if((AtributosValidos(tokens_atributos[6], matriz_separada)) == 1)
		{
			UART0_puts("Leer pwm");
		}
		else
		{
			UART0_puts("Comando Desconocido");
			UART0_puts("\r\n");
		}
		break;
		
		case 7:

			if(AtributosValidos(tokens_atributos[7], matriz_separada))
			{			
				uint8_t pin  = matriz_separada[1][0]-48;
				unsigned int valorAdc=0;
				char valorBit[20] ={'\0'};
				ADC_INI(0);
				BitSalida(pin);
				valorAdc =  ADC_LEER();
				UART0_puts("Comando ra valido");	
				//itoa(valorBit,valorAdc, 16);
				//UART0_puts(valorBit);
				PrintDec2d(valorAdc);
				UART0_puts("\r\n");
			}
			else
			{
				UART0_puts("Comando Desconocido ra");
				UART0_puts("\r\n");
			}
		break;
	}
	
}
int AtributosValidos(const int tokens_atributos[10], char matriz_separada[20][20])
{
	int i = 1; //renglon matriz separada
	int k = 0; //columna  matriz separada
	int j = 0; //Tokens
	int bandera = 0;
	char par ={"E","O", "N"};
	unsigned int numero = 0;
	unsigned long baudaje =0; 
	
	do
	{
		switch (tokens_atributos[j])
		{
			case 1:
				if (matriz_separada[i][k] == 'b')
				{
					if (ValidarNumero(matriz_separada[i][k+1], 48, 55))
					{
						if(matriz_separada[i][k+2] != '\x0')
							bandera = 0;
						else
						{
							//UART0_puts("Se valido el bx ");
							bandera = 1;
							i++;
							j++;
							k = 0;
						}
					}
					else
					{
						bandera = 0;
					}
				}
				else
				{
					bandera = 0;
				}
			break;
			
			//Comparar numero 0 o 1
			case 2:
					if (ValidarNumero(matriz_separada[i][k], 48, 49))
					{
						//UART0_putchar(matriz_separada[i][k]);
						if (matriz_separada[i][k+1] != '\x0')
						{
							bandera=0;
						}
						else
						{
							//UART0_puts("\n\r Validar valor");
							bandera = 1;
							i++;
							j++;
							k = 0;
						}
					}
					else
					{
						bandera = 0;
					}
				break;
			//Comparar un Numero 1-4
			case 3:
					if(ValidarNumero(matriz_separada[i][k], 49, 52) == 1)
					{
						k++;
						if (matriz_separada[i][k] != '\x0')
						{
							bandera = 0;
						}
						else
						{
							bandera = 1;
							i++;
							j++;
							k = 0;
						}
					}
					else
					{
						bandera = 0;
					}
				break;
			case 4:
					if(ValidarNumero_MayorCero(matriz_separada[i])==1)
					{
						baudaje = atoi(matriz_separada[i]);
						 if(ValidarBaudaje(baudaje))
						 {
							 bandera = 1;
							 i++;
							 j++;
							 k = 0;
						 }
						 else
						 {
							bandera = 0; 
						 }
					}
					else
					{
						bandera = 0;
					}
				break;
			
			// Comparar numero entre 5-8
			case 5:
					//UART0_puts("Validar Numeros 5-8 ");
					if(ValidarNumero(matriz_separada[i][k], 53, 56))
					{
						k++;
						if(matriz_separada[i][k] != '\x0')
						bandera = 0;
						else
						{
							bandera = 1;
							i++;
							j++;
							k = 0;
						}
					}
					else
					{
						bandera=0;
					}
				break;
			
			//Comparar E,0,N
			case 6:
					//UART0_puts("Validar Letras E O N ");
					if(matriz_separada[i][k] == 'E'||matriz_separada[i][k] == 'O' ||matriz_separada[i][k] == 'N')
					{
						k++;
						if(matriz_separada[i][k] != '\x0')
						bandera = 0;
						else
						{
							bandera = 1;
							i++;
							j++;
							k = 0;
						}
					}
					else
					{
						bandera=0;
					}
			  	break;
			
			//Validar 1 2
			case 7:
					//UART0_puts("Validar 1 2");
					if(ValidarNumero(matriz_separada[i][k], 49, 50))
					{
						k++;
						if(matriz_separada[i][k] != '\x0')
						bandera = 0;
						else
						{
							bandera = 1;
							i++;
							j++;
							k = 0;
						}
					}
					else
					{
						bandera = 0;
					}
				break;
			
			//Validar comillas
			case 8:
					UART0_puts("Validar comillas");
				break;
			
			//Validar numero 0-100
			case 9:
					//UART0_puts("Numero 0 100 ");
					if( ValidarNumero_MayorCero(matriz_separada[i])==1)
					{
						numero = atoi(matriz_separada[i]);
						//UART0_puts("Numero rango ");
						if(numero >=0 && numero <= 100)
						{
							//UART0_puts("Numero Valido");
							bandera = 1;
							i++;
							j++;
							k = 0;
						}
						else
						{
							bandera = 0;
						}
					}
					else
					{
						bandera  = 0;
					}
				break;
			
			//VALIDAR NUMERO 0-7
			case 10:
					//UART0_puts("Validar numero 0 - 7 ");
					if(ValidarNumero(matriz_separada[i][k], 48, 55))
					{
						if(matriz_separada[i][k+1] != '\x0')
							bandera = 0;
						else
						{
							//UART0_puts("Correcto");
							bandera = 1;
							i++;
							j++;
							k = 0;
						}
					}
					else
					{
						bandera = 0;
					}
				break;
			default:
				//if(bandera != 1)
				//{
					UART0_puts(i);
					bandera = 0;
				//}
					i++;
			break;
		}	
	}while(matriz_separada[i][0]!='\x0' && bandera == 1 && tokens_atributos[j] != '\x0');
	return bandera;
}
int ValidarNumero(char cadena, char min, char max)
{
		if (cadena >= min && cadena <= max)
		{
			return 1;
		}
	return 0;
}
int ValidarNumero_MayorCero(char* renglon)
{
	int i =0;
	int bandera =0;
	for(i=0; renglon[i]; i++)
	{
		if(renglon[i]>= 48 && renglon[i]<=57)
		{
			bandera = 1;
		}
		else
		{
			return 0;
		}
	}
	return bandera;
}
int ValidarBaudaje(unsigned long baud)
{
	unsigned long baud_array[]={{1200}, {2400}, {4800}, {9600}, {19200}, {38300}, {57600}, {11520}};
	int i=0; 			
	for (i=0; i<=7; i++)
	{
		if(baud_array[i] == baud)
		{
			return 1;
		}
	}
		
	return 0; 
}
