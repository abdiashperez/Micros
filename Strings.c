/*
 * Strings.c
 *
 * Created: 21/11/2017 03:14:34 p. m.
 *  Author: abdias
 */ 
#include <avr/io.h>
#define SPC 0x20


char* ltrim(char *cadena_copia, char caracter)
{
	char* original = cadena_copia;
	char *p = original;
	int trimmed = 0;
	do
	{
		if (*original != caracter || trimmed)
		{
			trimmed = 1;
			*p++ = *original;
		}
	}
	while (*original++ != '\0');
	
  return cadena_copia;
}
char* rtrim(char *cadena, char caracter)
{
	int tamanio  = str_length(cadena);
	char* original = cadena + tamanio; 
	
	while(*--original == caracter);
	*(original + 1) = '\0';

	return cadena;
}
int str_length(char cadena[])
{
	int i=0;
	int n=0;

	while (cadena[i]!='\0')
	{						
		n++;
		i++;
	}
 return n;
}
char* strcopy(char original[], char cadena_copia[])
{
	uint8_t i =0;
	while(original[i] != '\0')
	{
		cadena_copia[i] = original[i];
		i++;
	}
	cadena_copia[i] = '\0';
	
	return cadena_copia;
}
int str_cmp(char cadena_fuente[], char cadena_base[])
{
	unsigned int i=0;
	unsigned int comparacion = 0;
	
	for(i=0; cadena_fuente[i]; i++)
	{
		if(cadena_fuente[i] != cadena_base[i])//Si es diferente
		{
			comparacion = 1;
			return comparacion;
		}
		else
		{
			comparacion = 0;
		}

	}
	
	return comparacion;
}
char* separarCadena(char cadenaCopia[20], char matriz[20][20])
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;
	
	while(cadenaCopia[i] != '\x0')
	{
		if(cadenaCopia[i] != 0x20)
		{
			matriz[k][j] = cadenaCopia[i];
			i++;
			j++;
		}
		else if (cadenaCopia[i-1]!= 0x20)
		{
			i++;
			matriz[k][j] ='\x0';
			j = 0;
			k++;
		}
		else
		i++;
	}
	matriz[k][j] ='\x0';
	matriz[k+1][j] ='\x0';
	
	return matriz;
}
unsigned int atoi(char *str)
{
	unsigned int i=0, num=0;
	for(i=0; ((str[i]!='\x0') && (str[i] >= '0' && str[i] <= '9')) ; i++)
	{
		if(str[i] >= '0' && str[i] <= '9')
		{
			num = num*10 + (str[i] - '0');
		}
	}
	return num;
}

void itoa(unsigned char *str,unsigned int num,unsigned int base)
{
	unsigned char temp,i=0,j=0;
	
	do
	{
		temp=num%base;
		temp+=0x30;
		if(temp>0x39)
		{
			temp+=7;
		}
		str[i]=temp;
		num/=base;
		i++;
	}while(num!=0);
	str[i]='\0';
	do
	{
		i--;
		temp=str[j];
		str[j]=str[i];
		str[i]=temp;
		j++;
	}while(j<i);
}

void LimpiarCadena(char* cadena_copia, char caracter)
{
	ltrim(cadena_copia, caracter);
	rtrim(cadena_copia, caracter);
}

void PrintDec2d(unsigned int dato)
{
	UART0_putchar( dato/100 +'0'); /*Imprime centenas*/
	UART0_putchar( dato/10 +'0'); /* Imprime decenas */
	UART0_putchar( dato%10 +'0'); /* Imprime unidades */
}