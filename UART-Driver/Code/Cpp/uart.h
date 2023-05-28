#ifndef __UART_H 
/*Står för 'if not defined UART_H', detta är en så kallad 'header_guard' som förhindrar dubbelinkludering av headerfilen. 
Det säkerställer att innehållet i headerfilen bara inkluderas en gång i programmet*/

#define __UART_H
/*Här definierar vi __UART_H, vilket fungerar som en unik tagg för att undvika namnkollisioner om filen inkluderas mer än en gång i programmet.*/

#include "stm32f4xx.h" 
/*Den här filen innehåller källkod och definitioner som behövs för att kunn arbeta med STM-hårdvaran
Det ger oss tillgång till olika funktioner och registerdefinitioner som är specifika för STM32f4-mikrokontrollerfamiljen*/

#include <stdio.h> 
/*Denna rad inkluderar en standardbiblioteksfil med namnet stdio.h för at vi ska kunna använda standard in och ut datafunktioner i C eller C++ programmeringsspråken.
Det ger oss tillgång till funktioner som printf och scanf*/


void USART2_Init(void);
/*Deklaration av funktionen USART2_Init som används för att initiera UART-kommunikationen. Funktionen har implementerats i en annan fil.*/

void test_setup(void); 
/*Deklaration av funktionen test_setup, som används för att konfigurera testparametrar för UART. Funktionen kommer att implementeras i en annan fil.*/

#endif 
/*Detta markerar slutet på kodblocket och avslutar #ifndef-koden*/