UART-driver för STM32F411x-plattformsfamiljen med inkluderad LED-applikations samt förklaringar utmed koden.

I vår "Code" -mapp finns det fem olika kodfiler som tillsammans utvecklar en UART-drivrutin för STM32F411x-mikrokontrollplattformen. 
Drivrutinen är skriven i C och C++ programmeringsspråken och erbjuder olika funktioner för att underlätta initialisering och konfigurering av UART-enheten. 
Dessutom möjliggör den överföring och mottagning av data genom UART-gränssnittet.

För att ytterligare utöka funktionaliteten har vi även inkluderat en LED-funktion som möjliggör kommunikation med LED-lampor. 
Denna LED-funktion är implementerad genom att använda flera filer i mappen som samverkar med varann.

Följande är en översikt av de olika filerna och deras funktioner:

1. "UART.cpp" och "UART.h": 

Dessa filer innehåller implementationen av UART-drivrutinen. 
De erbjuder funktioner för att initiera och konfigurera UART-enheten och hanterar dataöverföring via UART-gränssnittet. 

2. "led.cpp" och "led.h": 
Dessa filer innehåller definitionen av en LED-klass och dess funktioner. 
LED-klassen används för att skapa och hantera LED-lampor. 
Funktioner i dessa filer erbjuder ändring av tillståndet för lampan och hämtning av LED-lampornas aktuella tillstånd.

3. "main.cpp": 
Detta är huvudfilen som innehåller main()-funktionen. 
Här initieras UART-drivrutinen genom att anropa relevanta funktioner i "UART.h". 

Genom att använda dessa fem filer tillsammans skapar vi en komplett lösning som möjliggör UART-kommunikation och LED-styrning på STM32F411x-mikrokontrollplattformen.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

För att kunna använda dessa koder/drivrutin för att styra LED-lampa behöver man följande:

1. En STM32f11x-mikrokontrollplattform eftersom koderna är baserad just för denna hårdvaran.
2. Utvecklingsmiljöer som exempelvis STM32CubeIDE 
3. LED-lampor 
4. UART kabel elelr USB till UART konverterings kabel
5. Grundläggande förståelse av koderna i filen för att kunna implementera de funktioner som erbjuds korrekt 

6. Initiera UART kommunikationen genom att anropa "USART2_Init()" från "uart.cpp" i huvudkoden.
7. Använda lämpliga funktioner och metoder från "led.cpp" för att styra LED-lampan exempelvis: skapa en instans av LED-lampan som du vill styra genom att använda konstruktorn i "led.cpp". 
Slutför koden med en oändlig loop som håller programmet igång: "while(1) {}"

Det är viktigt att ha grundläggande förståelse för koden som erbjuds i denna projekt för att kunna dra full nytta utav dess funktioner och möjligheter för att styra exempelvis LED-lampor.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Licens

Detta projekt är licensierat under NackademinSarhad-licensen.