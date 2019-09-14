/*********** WeMos D1 mini pinout*****************************
  Контакт   Назначение        ESP-8266 контакты
      TX      TXD                   TXD
      RX      RXD                   RXD
      A0     Analog input,          A0
             max 3.3V input  
      D0      IO                    GPIO16
      D1     IO, SCL                GPIO5
      D2     IO, SDA                GPIO4
      D3     IO,10k Pull-up         GPIO0
      D4     IO, 10k Pull-up,       GPIO2  
             BUILTIN_LED  
      D5     IO, SCK                GPIO14
      D6     IO, MISO               GPIO12
      D7     IO, MOSI               GPIO13
      D8     IO,10k Pull-down, SS   GPIO15
      G      Ground                 GND
      5V     5V                     -
      3V3    3.3V                   3.3V
      RST    Reset                  RST 
***************************************************************/
#include <Adafruit_NeoPixel.h>
#define PIN 2 // номер порта к которому подключен модуль
//#define DOOR 0 // Номер порта "датчика" двери
//#define WINDOW 5 // Номер порта "датчика" окна
#define FIRST_INPUT1_OUTPUT_LED  0
#define LAST_INPUT1_OUTPUT_LED  6


#define count_led 42 // количество светодиодов 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(count_led, PIN, NEO_GRB + NEO_KHZ800); //first number change does distance between colors
uint8_t i;  
uint8_t  palette1[7][3] ={ //7 цветов по RGB
  {0,0,0}, //black
  {255,0,0}, //red сигнализирует о проблеме с объектом "дверь"
  {0,255,0}, //green сигнализирует о "нормальном" состоянии объектов
  {0,0,255}, //blue сигнализирует о проблеме с объектом "Окно"
  {255,255,0}, //yellow
  {255,0,255}, //magenta другой датчик
  {255,255,255} //white
};


void setup() {
  strip.begin();
  strip.clear();                          // очистить
  strip.show(); // Устанавливаем все светодиоды в состояние "Выключено"
  //pinMode(DOOR, INPUT_PULLUP);
  //pinMode(WINDOW, INPUT_PULLUP);
}
void loop() {
      for(int i = FIRST_INPUT1_OUTPUT_LED; i < LAST_INPUT1_OUTPUT_LED; i++)
    {
      strip.setPixelColor(i, strip.Color(palette1[2][0], palette1[2][1], palette1[2][2]));
    }
        strip.show();
    delay(1000);
}
    
    
   /* 
    if (digitalRead(DOOR)) strip.setPixelColor( 3, strip.Color( palette1[2][0], palette1[2][1], palette1[2][2])); //Проверим сигнал для двери
    else strip.setPixelColor( 3, strip.Color( palette1[3][0], palette1[3][1], palette1[3][2]));
    if (digitalRead(WINDOW)) strip.setPixelColor( 6, strip.Color( palette1[2][0], palette1[2][1], palette1[2][2]));
    else strip.setPixelColor( 6, strip.Color( palette1[1][0], palette1[1][1], palette1[1][2]));
    strip.show();                         // отправить на ленту
    delay(1000);
}*/
