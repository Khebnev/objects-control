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
#define FIRST_INPUT1_OUTPUT_LED  0
#define LAST_INPUT1_OUTPUT_LED  6

#define FIRST_INPUT2_OUTPUT_LED  6
#define LAST_INPUT2_OUTPUT_LED 12
/*
#define FIRST_INPUT3_OUTPUT_LED  12
#define LAST_INPUT3_OUTPUT_LED 17

#define FIRST_INPUT4_OUTPUT_LED  18
#define LAST_INPUT4_OUTPUT_LED 23

#define FIRST_INPUT5_OUTPUT_LED  24
#define LAST_INPUT5_OUTPUT_LED 29

#define FIRST_INPUT6_OUTPUT_LED  30
#define LAST_INPUT6_OUTPUT_LED 35

#define FIRST_INPUT7_OUTPUT_LED  36
#define LAST_INPUT7_OUTPUT_LED 41
*/

#define count_led 42 // количество светодиодов 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(count_led, PIN, NEO_GRB + NEO_KHZ800); //first number change does distance between colors
uint8_t i; 
uint8_t ii; 
uint8_t  palette1[7][3] ={ //7 цветов по RGB
  {0,0,0}, //black
  {255,0,0}, //red 
  {0,255,0}, //green 
  {0,0,255}, //blue 
  {255,255,0}, //yellow
  {255,0,255}, //magenta другой датчик
  {255,255,255} //white
};


void setup() {
  strip.begin();
  strip.clear();                          // очистить
  strip.show(); // Устанавливаем все светодиоды в состояние "Выключено"
  //pinMode(led1, INPUT_PULLUP);
  //pinMode(led2, INPUT_PULLUP);
}
void loop() {
  for(int i = FIRST_INPUT1_OUTPUT_LED; i < LAST_INPUT1_OUTPUT_LED; i++)
    {
      strip.setPixelColor(i, strip.Color(palette1[2][0], palette1[2][1], palette1[2][2]));
      strip.show();
      delay(400); //to test 400 ms
    }
       /* if (digitalRead(i == 3))
        {
          strip.setPixelColor(3, strip.Color(palette1[2][0], palette1[2][1], palette1[2][2]));
        }
        else
        {
          strip.setPixelColor( 3, strip.Color( palette1[3][0], palette1[3][1], palette1[3][2]));
        }
        strip.show();
        delay(500);
    }
    strip.show();
    delay(1000);*/
  for(int ii = FIRST_INPUT2_OUTPUT_LED; ii < LAST_INPUT2_OUTPUT_LED; ii++)
  {
    strip.setPixelColor(ii, strip.Color(palette1[2][0], palette1[2][1], palette1[2][2]));
      strip.show();
      delay(200); to test 200 ms
  }
}
  
/*    if (digitalRead(led1)) strip.setPixelColor( 3, strip.Color( palette1[2][0], palette1[2][1], palette1[2][2])); /
    else strip.setPixelColor( 3, strip.Color( palette1[3][0], palette1[3][1], palette1[3][2]));
    if (digitalRead(led2)) strip.setPixelColor( 6, strip.Color( palette1[2][0], palette1[2][1], palette1[2][2]));
    else strip.setPixelColor( 6, strip.Color( palette1[1][0], palette1[1][1], palette1[1][2]));
    strip.show();                         // отправить на ленту
    delay(1000);
} */
