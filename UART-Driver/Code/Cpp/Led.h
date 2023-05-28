#ifndef LED_H
#define LED_H
/*Dessa rader förhindrar att samma headerfil inkluderas flera gånger. De ser till att filens innehåll inkluderas endast en gång, även om den refereras till från olika delar av programmet.*/

#include <stdint.h>
/*En annan standardbiblioteksfil i C och C++-programmeringsspråket som innehåller definitioner av fasta storlekar för heltalstyper. 
<stdio.h> används för att hantera in- och utmatning. <stdint.h> används för att definiera exakta storlekar för heltalstyper.*/

#include "UART.h"
/*Denna rad inkluderar "UART.h"-filen*/

#include "stm32f4xx.h"
/*Denna rad inkluderar "stm32f4xx.h"-filen*/

#define LED_PORT GPIOB
/*I denna rad definierar vi vilken GPIO port som skall vara ansvarig för LED-funktionen, i detta fall GPIOB. I koden säger vi att vi vill använda en speciell port på vår dator som heter GPIOB för att kontrollera våra LED-lampor. 
Istället för att skriva 'GPIOB' varje gång vi vill prata om den porten, så säger vi istället att vi kallar den 'LED_PORT', så varje gång man använder headern till denna fil så kan man använda definitionen LED_PORT som en synonym för GPIOB. 
På så sätt blir det lättare att förstå och så slipper vi skriva det långa ordet varje gång. Så överallt i koden där vi skriver "LED_PORT" kommer det egentligen att betyda 'GPIOB'.*/

#define LED_PORT_CLOCK (1U<<1)
/*Denna rad definierar en makro LED_PORT_CLOCK och tilldelar den värdet (1U<<1). Makron används för att representera värdet för klocksignalen för porten som är ansvarig för LED-funktionen. 
Så när vi skriver '(1U<<1)' betyder det att vi tar talet 1 på bit 0 och flyttar det ett steg till vänster, vi sätter alstå värdet på biten 1 i RCC_AHB1ENR registret till 1.*/

#define LED_RED_PIN (1U<<14) //motsvarar bit 14 i GPIO-porten.
#define LED_GREEN_PIN (1U<<12) //motsvarar bit 12 i GPIO-porten.
#define LED_BLUE_PIN (1U<<15) //motsvarar bit 15 i GPIO-porten.
#define LED_YELLOW_PIN (1U<<13) //motsvarar bit 13 i GPIO-porten.
/*I koden definieras de olika LED-lampornas koppling till GPIO-porten vi arbetar med, i det här fallet GPIOB. Varje LED definieras med sin specifika bitposition i GPIO-porten.*/

#define LED_RED_MODE_BIT (1U<<28)
#define LED_GREEN_MODE_BIT (1U<<24)
#define LED_YELLOW_MODE_BIT (1U<<26)
#define LED_BLUE_MODE_BIT (1U<<30)
/*Här så definieras mode-bitsen för varje LED-färg, vilket representerar bitpositionerna i MODER-registret för att konfigurera respektive LED-pin som en utgång. När vi använder värdet 01 i GPIO-portens MODER-register, 
betyder det (general purpose output mode). Det innebär att den specifika pinnen i GPIO-porten konfigureras som en utgång och kan användas för att styra en LED */

typedef enum {
  RED = 0,
  GREEN,
  YELLOW,
  BLUE
}LedColor_Type;
/*Definerar de olika LED-färgerna som finns. Med hjälp av funktionen 'typedef enum' får varje färg en motsvarande numeriskt värde för att enklare kunna hantera dom senare i koden.*/

typedef enum {
  OFF = 0,
  ON = 1
}LedState_Type;
/*Även dessa med hjälp utav 'typedef enum' representerar olika tillstånd (ON/OFF) för en LED-lampa, värdet OFF (0) eller ON (1) anger om LED-lampan är avstängd eller påslagen.*/



class Led{ //Vi skapar en klass som heter "Led" för att representera de LED-lampor vi skapar. Inuti klassen har vi olika delar som hjälper oss att hantera lamporna.

  private: /*Dessa variabler inuti private används för att lagra informationen om färgen och tillståndet (ON eller OFF) för LED-lampan. Eftersom de är privata kan de endast användas inuti klassen, 
  vilket ger oss bättre kontroll över hur de används och vilket skyddar dem från att ändras av misstag från andra delar av koden.*/

      LedColor_Type color; //variabel av typen LedColor_Type som representerar färgen på LED-lampan. 
      LedState_Type state; //variabel av typen LedState_Type som representerar tillståndet (ON eller OFF) för LED-lampan.

  public: /*koder inuti public kan nås och användas från andra delar av vår kod, alstå: en konstruktor, som används för att skapa och ställa in en LED-lampa med en viss färg och tillstånd, Vi har också funktionerna "setState" och "getState". "setState" låter
   oss ändra tillståndet för lampan (ON eller OFF), medan "getState" ger oss det aktuella tillståndet.*/

      Led(LedColor_Type _color,LedState_Type _state); 
      /*Detta är den konstruktor för klassen Led. Konstruktorn tar emot två parametrar, 
      en för färgen och en för tillståndet, och används för att sätta värden på variablerna när ett nytt Led-objekt skapas.*/

      void setState(LedState_Type _state); // Detta är en funktion som används för att ändra tillståndet (ON eller OFF) för LED-lampan. Funktionen tar emot en parameter _state av typen LedState_Type och sätter värdet på variabeln 'state' till det angivna tillståndet.
      LedState_Type getState() const; /*Detta är en funktion som används för att få tillståndet för LED-lampan. Funktionen returnerar värdet av medlemsvariabeln state som representerar det aktuella tillståndet. 
      Den är markerad med const, vilket innebär att den inte ändrar några medlemsvariabler i klassen.*/

}
#endif
