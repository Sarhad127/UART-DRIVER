#include "UART.h" 

/*Hämtar vår samlingsfil i vår mapp "UART.h" som är vår headerfil som innehåller deklarationer och prototyper för funktioner och datatyper som används för att kommunicera via UART. 
Genom att skriva sin headerfil här så slipper du att skriva dom direkt i programfilen vilket bidrar med en organiserad och strkturerad kod samt som det underlättar en del.*/

void USART2_Init(void) { 
  /*Denna kod definierar en funktion med namnet "USART2_Init" som inte tar emot några argument och inte returnerar något värde (void), 
  den är avsedd för att initialisera UART-kommunikationen för enhet USART2.*/

// 1. Enablea klocktillgång för USART2

RCC->APB1ENR |= 0x20000; 
/*Atkiverar USART2 genom att sätta bit 17 i APB1ENR registret till 1 med hjälp av hexadecimalen 0x20000. "|" används för att bara ändra på den bit vi vill ändra på och inte ändra på de bitarna som redan är en etta elller en nolla.
USART2 modulen behöver en klocka för att generera korrekta tidsintervall för överföring och mottagning av data. Både sändaren och mottagaren måste vara konfigurerade med samma baud rate, även om USART2 inte använder en separat intern klocka för att generera tidsintervall 
är det viktigt att ha en stabil klocka som genererar tidssekvenser som överensstämmer med den baud rate man är ute efter för att ha en bra kommunikation via UART. */

// 2. Enablea klocktillgång för GPIO port A

RCC->AHB1ENR |= 0x01; 
/*Denna rad aktiverar klocktillgången för GPIO port A genom att sätta bit 0 i AHB1ENR registret till värdet 1. AHB1ENR är en register som aktiverar/inaktiverar klocktillgången, detta innebär att GPIO port A kan användas för att styra och
övervaka digitala signaler. Om klocktillgången är av dvs 0 kommer pinnen på den porten vara inaktiv eller inte fungera som förväntat */

// 3. Enablea pins relaterade till vald port, för alternativ funktion

GPIOA->MODER &= ~0x00F0; 
/*Den anvgiva koden ställer in lägena på GPIOA pinnarna. De bitar som representerar port A syns vid resetvärdet 0xA800 0000 vilket betyder att de 16 GPIO pinnarna är alla redo för port A och koden vi skrev använder vi utav bitarna 4-7 dvs pin 2 och 3
0x00F0 är en hexadecimal som motsvarar 32 bitarsformat villket sätter ett värde med ettor på platserna bit 4-7 och värdet 0 på resterande 32 bitarna, 
'~' inverterar varje bit i värdet dvs ettor blir till nollor och nollor blir till ettor, om vi då skriver ut värdet i binär format skulle de se ut som följande 1111 1111 0000 1111, sen så använder vi oss utav AND operationen '&' som 
behåller de befintliga värdena utöver de pinsen som vi ändrat på dvs pins 2 och pins 3, de nollställs*/

GPIOA->MODER |= 0x00A0; 
/*Det hexadecimala värdet motsvarar det binära värdet 0000 0000 1010 0000 i 32-bitarsformat och sätter bitarna 5 och 7 till 1 vilket leder till att pinsen för GPIO port A pin2 och pin3 aktiverar alternativ funktions läge. 
Alternativ funktion öppnar upp möjligheten att använda dessa pinnar för speciella ändamål och kan utnyttja de extra funktioner än bara generellt in eller utgångs läge tillgängliga för dem i mikrokontrollern*/

// 4. Välja typen av alternativ funktion för de valde pinsen

GPIOA->AFR[0] &= ~0xFF00;
/* [0] används för att komma åt den första delen av AFR registret dvs bit 1 för GPIO port A och sedan med hjälp utav det hexadecimala talet och inverteringen nollas bitarna 8-15 oavsett tidigare värde och de andra bitarna förblir oförändrade med hjälp utav (&) AND operatorn, 
På så sätt tar man bort eventuella tidigare konfigurationer för alternativa funktioner på pins PA2 och PA3 i GPIO-port A och skapar en ren utgångspunkt där man kan ställa in de önskade alternativa funktionerna utan påverkan av tidigare inställningar.*/

GPIOA->AFR[0] |= 0x7700; 
/* Genom att använda '|' ändrar vi bara de värden vi vill ändra på och de befintliga värdena förblir oförändrade. I denna kodrad sätter vi bitarna 8-11 samt 12-15 till formatet 0111, i binärt form ser det hela ut som 0111011100000000
Varför man sätter värdet på dessa bits till 0111 är för att i vår data sheet under alternate function mapping så står 'AF07' för USART2_TX och USART2_RX vilket är det alternativa funktion som vi vill sätta våra pins till här, vilket erbjuder transmitting och recieveing utav data*/

/* Konstruktion av enhetens kommunikation avslutas */

// Konfiguration utav UART

USART2->BRR = 0x0683; 
/*Om vi omvandlar det hexadecimala till binärt ser det ut som följande '0000 0110 1000 0011' det motsvarar en 16 bitars format där varje nibble motsvarar en siffra om man omvandlar det binära till ett decimalt tal, i det här fallet blir det 0 6 8 3, vilket är standard baud-rate.
Varför man sätter det till standard kan vara av flera anledningar, exempelvis kompatibilitet: 9600bps är standard baud rate som kan användas av många enheter och kommunikationsprotokoll vilket ökar möjligheten att kommunicera med andra enheter, men även för att 9600 är en väl testad 
och pålitlig baudrate samt som strömförbrukning är lägre än vid högre baud rate. */

USART2->CR1 = 0x000C; 
/* 0x000C i binär format = '0000 0000 0000 1100' och i detta fall utför dessa nollor ett specifikt arbete på bit 12 och bit 10, genom att sätta bit 12 och bit 10 till 0 säger vi till systemet att 
det ska finnas en start bit, 8 bitars data och n stop bitar, och att paritets kontroll ska vara avaktiverad. Att avaktivera paritetskontrollern är för att inte överflöda datapaketet om det inte finns något stort behov eller krav utav felkontroll, vilket 
kan leda till snabbare dataöverföring, paritetens funktion innebär att antalet ettor i dataöverföringen är jämnt, medan ojämn paritet kräver att antalet ettor är ojämnt. Ettorna på vår binära format sätter på transmittern och recievern, Genom att sätta TX och RX till 1 möjliggör 
man full duplex-kommunikation där sändning och mottagning kan ske samtidigt och oberoende av varandra. Detta ger en effektiv och pålitlig kommunikation mellan enheter. I detta fall räcker 8 bitars format för oss att överföra eftersom det bara är en integer värde utav en karaktär 
vilket motsvarar en byte(8 bitar) som vi vill överföra till vår enhet*/

USART2->CR2 = 0x000; 
/* Vad som kan konfigureras genom CR2-registret är exempelvis antalet stopbitar man vill ha vilket vi i detta fall lagt bitarna 12/13 till 00 vilket innebär 1 stopbit. Genom att sätta värdet till 0x000 nollställer man alla bitar i CR2-registret, 
vilket innebär att eventuella tidigare inställningar eller konfigurationer som kan ha funnits i registret rensas och återställs nu till standardvärdena.
Detta innebär en ren utgångspunkt för att sedan manipuleras om det behövs*/

USART2->CR3 = 0x000; 
/*Vi nollställer alla 12 bitar i CR3 till 0 likt förra kodraden,*/

USART2->CR1 |= 0x2000; 
/*Sätter bit 13 i CR1 till 1 vilket aktiverar USART och behåller resterande bitarna i sin befintliga läge, och att aktivera USART innebär det att USART2 kan användas för seriel datakommunikation med hjälp utav TX och RX som vi aktiverade tidigare i vår kontroll register 1*/

}

// UART Write

int USART2_write(int ch){  
/*Denna rad deklarerar en skrivfunktion som är avsedd att skicka en byte(8 bitar) som ska motsvara ett tecken till terminalen*/

  while(!(USART2->SR & 0x0080)){} 
  /*I denna while loop så kontrolleras statusregistret (SR) bit 7 (TXE) som står för Transmit Data Register Empty. Om TXE är 1 betyder det att överföringsbufferten är tom och redo att ta emot nästa byte för sändning.
  Om TXE är 0, vilket indikerar att bufferten inte är tom, kommer loopen att fortsätta tills TXE blir 1 och då utföra överföringen.*/



  USART2->DR = (ch & 0xFF); 
  /* Denna rad skickar värdet 'ch' till dataregistret för överföring. När man vill skicka data används USART->DR för att skriva värdet du vill överföra till dataregisret, och när du tar emot data komer det data som mottas lagras i dataregistret som man sedan kan läsa värdet av. 
  (cg & 0xFF) använder & operatorn med värdet 0xFF vilket är ett 8 bitars tal med alla värden satta till 1, och med (&) operatorn ignorerar vi alla andra bitar och behåller bara de signifikanta bitarna i detta fall de 8 bitar som representerar vår 'ch' 
  som sedan skickas till dataregistret för överföring.*/
  return ch;
  /*Här så returnerar vi vår värde som vi skrev in, kan vara användbart om man vill ha bekräftelse på den byte man skicka utfört sin uppgift, eller så kan det vara ett sätt att bara avsluta sitt program */
} 

// UART Read

int USART2_read(void){ 
/*Denna rad deklarerar en läsfunktion (mottagning av information) som returnerar en integer värde, */

  while(!(USART2->SR & 0x0020)){} 
/*while-loopen kontrollerar statusregistret (SR) för USART2, mer specifikt kontrolleras bit 5 (RXNE), som indikerar om det finns mottagen data som är redo att läsas. 
Om bit 5 är noll, vilket innebär att det inte finns någon mottagen data att läsa, fortsätter while-loopen att köras tills bit 5 blir 1 (dvs. det finns mottagen data att läsa). 
Detta säkerställer att funktionen väntar på att data ska vara tillgänglig innan den fortsätter exekveringen.*/

  return USART2->DR; 
  /*Läser ut datan som mottagaren sänder och som läses ifrån dataregistret på vår enhet*/
}































