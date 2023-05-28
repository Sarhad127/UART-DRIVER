#include "led.h"
/*Inkluderar headerfilen med namnet 'led.h'. Headerfiler innehåller vanligtvis deklarationer och definitioner av funktioner och variabler som används i koder.*/

LedState_Type led1_state;
LedState_Type led2_state;
LedState_Type led3_state;
/*Dessa rader deklarerar tre variabler av typen LedState_Type som representerar statusen för tre LED-lampor.*/

Led led1(RED,ON); 
/*Denna rad skapar en instans av en LED-lampa med namnet 'led1' genom konstruktorn som finns i en annan kodfil (Led.h), och lägger statusen av lampan 'RED' och som även sätter tillståndet på lampan 'ON' */

int main(void){ 
/*Detta är huvudfunktionen i programmet där konstruktionen och hanteringen av LED-lamporna sker. Programmet börjar utföras från denna punkt.*/

  USART2_Init();
  /*Deklaration av funktionen USART2_Init som används för att initiera UART-kommunikationen. Funktionen har implementerats i en annan fil.*/

  Led led2(BLUE,ON);
  /*En sekundär instans av en LED-lampa skapas med namnet 'led2'. LED-lampan tilldelas färgen 'BLUE' och sätts på 'ON'.*/

  Led *led3 = new Led(YELLOW,ON);
  /* Denna rad skapare en pekare 'led3' till en ny LED-lampa, och vi använder 'new' för att allokera minnet för denna nya lampan och instansierar lampan med färgen 'YELOOW' och sätter tillståndet på lampan 'ON'
  Vi skapar altså en ny LED-lampa och tilldelar pekaren led3 till den. Det gör det möjligt att arbeta med LED-lampan genom att använda pekaren led3 för att komma åt dess egenskaper och funktioner.*/

  led1_state = led1.getState();
  /*Här tilldelas värdet av 'led1' objektets nuvarande status till variabeln 'led1_state' genom att anropa funktionen getState() som finns i vår 'led.h' fil.*/

  led1.setState(OFF);
  /*Här ändras statusen för 'led1' till 'OFF' genom att anropa funktionen setState(OFF)*/

  delete led3;
  /*Denna rad tar bort den minnesallokerade LED-lampan som pekas på av 'led3' pekaren med hjälp av 'delete'-operatorn.*/

  while(1){}
  /*Denna rad skapar en oändlig loop för att hålla programmet igång. Programmet kommer att fortsätta köra i en loop och vänta på händelser eller input. 
  Detta förhindrar att programmet avslutas eller återgår till operativsystemet.*/

}
