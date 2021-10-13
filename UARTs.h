/*
 * UARTs.h
 *
 * Created: 21/11/2017 03:12:01 p. m.
 *  Author: abdias
 */ 

void UART0_Init();
void UART0_putchar(char data);
void UART0_puts(char *str);
void UART0_getchar(void);
void UART0_gets(char *str);

