#include "LED.h" //Inkluderar header filen för att även denna fil skall känna till de olika LED-beteckningarna och funktioner

//Konstruktorn för LED-lamporna
Led::Led(LedColor_Type _color, LedState_Type _state) /*Definierar konstruktorn i klassen Led som vi skapat inuti Led.h. Detta är funktionen som används för att skapa och konfigurera en LED-lampa. 
Den tar två parametrar: _color, som anger färgen på LED-lampan, och _state, som anger dess  tillstånd.*/
{

  this->color = _color;
  this->state = _state;
/*Användningen av this-> används för att hänvisa till medlemsvariabeln i objektet och inte till en lokal variabel med samma namn. De två parametrarna tilldelar sina värden till nya medlemsvariabel 'color' och 'state'*/

  //Enablea klockan för LED-porten (GPIOB)
  RCC->AHB1ENR |= LED_PORT_CLOCK;
  /*Här så enblear vi klockan för GPIOB och istället för att lägga en hexadecimal till registret kallar vi på den makro vi definierade i vår Led.h fil*/


  switch(_color){ //switch-sats som väljer olika fall beroende på LED-färgen (_color) som skickas in som parameter.


    case RED: //Sätta portläget för LED-konfigurationen till output
      LED_PORT->MODER |= LED_RED_MODE_BIT; //sätter rätt bit i 'MODER' registret för GPIO porten baserad på makro värdet vi tillgav den vilket sätter det till 'General purpose output mode'

      if(this->state == ON){ 
        LED_PORT->ODR |= LED_RED_PIN;
        /*här så kontrolleras LED lampans tillstånd 'state' (ON eller OFF) och om det är 'ON' så sätts 'ODR' registret för GPIOB till LED_RED_PIN, vilket betyder 'ON'*/
      }

      else{
        //Stänga av LED
        LED_PORT->ODR &= ~LED_RED_PIN; //Denna rad använder en bitvis AND-operation och negation (~) för att sätta den angivna bitpositionen till 0, vilket motsvarar att stänga av LED-lampan.
      } 

      //Samma sak görs på alla 'case's i vår switch sats.
      break;

      case YELLOW: 
      LED_PORT->MODER |= LED_YELLOW_MODE_BIT;
      if(this->state == ON){
       
        LED_PORT->ODR |= LED_YELLOW_PIN;
      }
      else{
        
        LED_PORT->ODR &= ~LED_YELLOW_PIN;
      }
      break;

      case BLUE: 
      LED_PORT->MODER |= LED_BLUE_MODE_BIT;
      if(this->state == ON){
        
        LED_PORT->ODR |= LED_BLUE_PIN;
      }
      else{
        
        LED_PORT->ODR &= ~LED_BLUE_PIN;
      }
      break;

      case GREEN: 
      LED_PORT->MODER |= LED_GREEN_MODE_BIT;
      if(this->state == ON){
       
        LED_PORT->ODR |= LED_GREEN_PIN;
      }
      else{
        
        LED_PORT->ODR &= ~LED_GREEN_PIN;
      }
      break;

/*Sammanfattning: Först sätter vi portläget för LED-konfigurationen till output genom att ändra en bit i MODER-registret för GPIO-porten. Detta gör vi med hjälp av makrovärden baserad på den 'MODE_BIT' vi använder.
Sedan kontrollerar vi LED-lampans tillstånd 'state'. Om det är 'ON', slår vi på LED-lampan genom att sätta en bit i ODR-registret för GPIO-porten. 
Om LED-lampans tillstånd inte är 'ON', stängs LED-lampan av genom att rensa (sätta till 0) den angivna bitpositionen i ODR-registret med hjälp av bitvis AND-operation och negation. Koden ändrar inte på något utan behåller bara statusen för LED-lamporna*/

  }


}

  this->state = _state; //Här så sätter vi värdet av 'state' för LED-lampan till samma värde som '_state'

  switch(this->color){  //Denna rad kollar på 'this->color' för att veta vilken färg LED-lampan är satt till. 


      //om LED Röd
    case RED:
      
      LED_PORT->MODER |= LED_RED_MODE_BIT; //Raden ändrar värdet i GPIO-portens MODER-register, specifikt på bitposition 28, för att sätta pinnen till "General purpose output mode". Genom att sätta pinnen till utgångsläge kan man senare styra den genom att ändra värdet på ODR-registret.
      
      if(this->state == ON){ //Här kontrolleras statusen på LED-lampan för att se om den är satt till "ON" eller "OFF".
        
        LED_PORT->ODR |= LED_RED_PIN; //Om LED-lampan är satt till "ON", sätts bitposition 14 i ODR-registret till 1. Detta sätter den specifika pinnen till "aktiv" och därmed tänds LED-lampan.
      }
      else{ //Om statusen visar 'OFF' utförs denna kodrad
        
        LED_PORT->ODR &= ~LED_RED_PIN; // Här sätts bitposition 14 i ODR-registret till 0, vilket inaktiverar den pinnen och därmed släcks LED-lampan.
      }
      break;
      /*Koden ovan utförs likadant på alla andra LED-lampor baserad på vilken färg som står i variabeln 'color'*/


      case YELLOW:
      //sätta pin till outputläge
      LED_PORT->MODER |= LED_YELLOW_MODE_BIT;
      //Om önskad status är ON
      if(this->state == ON){
        //Definerar pinensouput till aktiv
        LED_PORT->ODR |= LED_YELLOW_PIN;
      }
      else{
        //Definerar pin output till inaktiv
        LED_PORT->ODR &= ~LED_YELLOW_PIN;
      }
      break;

      case BLUE:
      //sätta pin till outputläge
      LED_PORT->MODER |= LED_BLUE_MODE_BIT;
      //Om önskad status är ON
      if(this->state == ON){
        //Definerar pinensouput till aktiv
        LED_PORT->ODR |= LED_BLUE_PIN;
      }
      else{
        //Definerar pin output till inaktiv
        LED_PORT->ODR &= ~LED_BLUE_PIN;
      }
      break;

      case GREEN:
      //sätta pin till outputläge
      LED_PORT->MODER |= LED_GREEN_MODE_BIT;
      //Om önskad status är ON
      if(this->state == ON){
        //Definerar pinensouput till aktiv
        LED_PORT->ODR |= LED_GREEN_PIN;
      }
      else{
        //Definerar pin output till inaktiv
        LED_PORT->ODR &= ~LED_GREEN_PIN;
      }
      break;
  }
/*Den här koden är en metod i en klass som heter "Led" och är ansvarig för att sätta och ändra statusen för en LED-lampa. */


LedState_Type Led::getState(void)const{ //Här så använder vi metoden getState i klassen led som definierats i filen led.h. Denna metod används för att få tillgång till och returnera statusen för LED-lampan. 

  //Kontrollera färgen av den LED som efterfrågas, printa sedan statusen
  switch(this->color){  //kontrollerar vilken färg det är på lampan 

    case RED:
      break;

    case YELLOW:
      break;

    case BLUE:
      break;

    case GREEN:
      break;
  }
             
             return this->state; //Baserad på vilken färg det är så returnerar vi statusen på den specifika LED-lampan
}
/*Denna metod används för att hämta och returnera statusen för en LED-lampa av en specifik färg.*/