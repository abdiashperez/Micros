/*
 * PORTs.h
 *
 * Created: 21/11/2017 03:25:12 p. m.
 *  Author: abdias
 */ 


void InicializarPuertos();
void ConfigurarPuerto(unsigned int portPin, unsigned int valor);
void EscrituraPuerto(unsigned int portPin, unsigned int bitx);
void leerPuerto(unsigned int portPin);