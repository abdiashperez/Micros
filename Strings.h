/*
 * Strings.h
 *
 * Created: 21/11/2017 03:14:15 p. m.
 *  Author: abdias
 */ 


char* ltrim(char *cadena_copia, char caracter);
char* rtrim(char *cadena, char caracter);
int str_length(char cadena[]);
char* strcopy(char original[], char cadena_copia[]);
int str_cmp(char cadena_fuente[], char cadena_base[]);
char* separarCadena(char cadenaCopia[20], char matriz[20][20]);
unsigned int atoi(char *str);
void itoa(unsigned char *str,unsigned int num,unsigned int base);
void LimpiarCadena(char* cadena_copia, char caracter);
void PrintDec2d(unsigned int dato);