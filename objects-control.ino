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
#define count_led 42 // количество светодиодов 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(count_led, PIN, NEO_GRB + NEO_KHZ800); //first number change does distance between colors
void setup() {
  strip.begin();
  strip.show(); // Устанавливаем все светодиоды в состояние "Выключено"
}
void loop() {
strip.setPixelColor(1, strip.Color(0,150,0)); // Назначаем для первого светодиода цвет "Зеленый"
strip.setPixelColor(2, strip.Color(250,150,0)); // Назначаем для первого светодиода цвет "Зеленый"
strip.setPixelColor(3, strip.Color(0,0,250)); // Назначаем для первого светодиода цвет "Синий"
 strip.show();
}
