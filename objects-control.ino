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

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>
#define PIN 2 // номер порта к которому подключен модуль
#define FIRST_INPUT1_OUTPUT_LED  0
#define LAST_INPUT1_OUTPUT_LED  42 /*6*/


#define count_led 42 // количество светодиодов 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(count_led, PIN, NEO_GRB + NEO_KHZ800); //first number change does distance between colors
uint8_t room1; 
uint8_t room2; 
uint8_t room3; 
uint8_t room4; 
uint8_t room5; 
uint8_t room6; 
uint8_t room7; 
uint8_t  palette1[9][3] ={ 
  {0,0,0}, //black                                           0
  {255,0,0}, //red                                           1
  {0,255,0}, //green                                         2
  {0,0,255}, //blue                                          3
  {255,255,0}, //yellow                                      4
  {255,0,255}, //magenta                                     5
  {255,255,255}, //white                                     6
  {255,69,0}, //orange -- (Undefined signal from a room)     7
  {192,192,192} //silver -- (Undefined state of the sensor)  8
};
const int relayPin = 5;

const char* ssid1 = "Kaf503_IoT"; //main router
const char* password1 = "12345678";
const char* ssid2 = "k503";           
const char* password2 = "36343218";
WiFiServer server(80);   //ESP8266WebServer server(80);

byte success = 0; 
const int pins[] = {16, 5, 4, 0, 2,14,12,13,15};  //pin GPIO
//                  D0,D1,D2,D3,D4,D5,D6,D7,D8      pin label 
char *State = "111111111 - State of pins: D0 ... D8";  // GPIO = 16, 5, 4, 0, 2,14,12,13,15 
String param, num, state;
int roomNum, roomState;



void setup(void){
  //pinMode(led, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  delay(1000);                       // wait for a second
  for(int i = 2; i > 0; i--)
  {
    digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
    digitalWrite(relayPin, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(relayPin, LOW);
    delay(500);                       // wait for a second
  } 
  delay(1000);  
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid1);
  WiFi.begin(ssid1, password1);
  int count = 40;                                                                           ////modify
  while ((WiFi.status() != WL_CONNECTED) && (count > 0)) {
    delay(500);
    count -= 1;
    Serial.print(".");
  }
  Serial.println(""); Serial.print(ssid1); 
  if(count >0){
    success = 1;
    Serial.println("  connected");
    Blink_N(1);
  } else Serial.println(" not connected");
  if(!success)
  {
    //Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid2);
    WiFi.begin(ssid2, password2);
    count = 20;
    while ((WiFi.status() != WL_CONNECTED) && (count > 0)) 
    {
      delay(500);
      count -= 1;
      Serial.print(".");
    }
    Serial.println(""); Serial.print(ssid2); 
    if(count >0)
    {
      success = 1;
      Serial.println(" connected");
      Blink_N(2);
    }  else Serial.println(" not connected");
   }    Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }



  server.begin();
  Serial.println("HTTP server started");
  // Print the IP address
  //Serial.println(WiFi.localIP()); 
  //start a part of strip
  strip.begin();
  strip.clear();                          // очистить
  strip.show(); // Устанавливаем все светодиоды в состояние "Выключено"


 




  
  for(int room1 = FIRST_INPUT1_OUTPUT_LED; room1 < LAST_INPUT1_OUTPUT_LED; room1++) // All leds from 0 to 41 on green, 50 ms gap between them
  {
    strip.setPixelColor(room1, strip.Color(palette1[8][0], palette1[8][1], palette1[8][2]));       
  }
    strip.show();
    delay(50); 
  //end a part of strip
}



void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  if (req.indexOf("/room/") != -1){
    String param = req.substring(req.indexOf("/room/")+6);
    //Serial.println(param);
    if (param.indexOf(",") >0){
      num = param.substring(0,param.indexOf(","));
      //String num = param.substring(0,param.indexOf(","));
      if(param.length()>param.indexOf(",")+2){ 
      state = param.substring(param.indexOf(",")+1,param.indexOf(",")+2);
      //String state = param.substring(param.indexOf(",")+1,param.indexOf(",")+2);
      //Serial.println(num);
      //Serial.println(state);
      roomNum = num.toInt();
      roomState = state.toInt();
      //int roomNum = num.toInt();
      //int roomState = state.toInt();
      Serial.print("room "); Serial.print(roomNum);
       Serial.print(" : state ");Serial.println(roomState);
     }
    }
   } else{
      Serial.println("invalid request");
      client.stop();
      return;    
     }
 // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  //s+= "
  //<meta charset=\"utf-8\" http-equiv=\"refresh\" content=\"15\" >";
  s+= "<html>\r\n<h1>room ";
  //s = s+ num +"\r\n";
  s = s+ String(roomNum)+"\r\n";
  s+= "<html>\r\nstate is ";
  //s = s+ state +"\r\n";
  s = s+ String(roomState)+"\r\n<h1>";
  s += "</html>\n";
  client.flush();

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println(s);
  Serial.println("Client disonnected");
//    return;

switch(roomNum)
  {
      case 130:
    {
     // if (roomState > 0 && roomState < 7)
     // {
        //strip.setPixelColor( 0, strip.Color( palette1[2][0], palette1[2][1], palette1[2][2])); // magenta as default
        switch (roomState)
         {
            case 1:
                strip.setPixelColor( 28, strip.Color( palette1[2][0], palette1[2][1], palette1[2][2])); // green as default
              break;
            case 2:
                strip.setPixelColor( 28, strip.Color( palette1[1][0], palette1[1][1], palette1[1][2])); // red
              break;
            case 3:
                strip.setPixelColor( 28, strip.Color( palette1[3][0], palette1[3][1], palette1[3][2])); // blue as default
              break;
            case 4:
                strip.setPixelColor( 28, strip.Color( palette1[4][0], palette1[4][1], palette1[4][2])); // yellow as default
              break;
            case 5:
                strip.setPixelColor( 28, strip.Color( palette1[5][0], palette1[5][1], palette1[5][2])); // magenta as default
              break;
            default:
                strip.setPixelColor( 28, strip.Color( palette1[8][0], palette1[8][1], palette1[8][2])); // magenta as default
         }
    //  }
      //else
      //{
      //  strip.setPixelColor( 0, strip.Color( palette1[7][0], palette1[7][1], palette1[7][2])); // magenta as default
     // }
    }
         break;
  case 132:
    {
     // if (roomState > 0 && roomState < 7)
     // {
        //strip.setPixelColor( 0, strip.Color( palette1[2][0], palette1[2][1], palette1[2][2])); // magenta as default
        switch (roomState)
         {
            case 1:
                strip.setPixelColor( 27, strip.Color( palette1[2][0], palette1[2][1], palette1[2][2])); // green as default
              break;
            case 2:
                strip.setPixelColor( 27, strip.Color( palette1[1][0], palette1[1][1], palette1[1][2])); // red
              break;
            case 3:
                strip.setPixelColor( 27, strip.Color( palette1[3][0], palette1[3][1], palette1[3][2])); // blue as default
              break;
            case 4:
                strip.setPixelColor( 27, strip.Color( palette1[4][0], palette1[4][1], palette1[4][2])); // yellow as default
              break;
            case 5:
                strip.setPixelColor( 27, strip.Color( palette1[5][0], palette1[5][1], palette1[5][2])); // magenta as default
              break;
            default:
                strip.setPixelColor( 27, strip.Color( palette1[8][0], palette1[8][1], palette1[8][2])); // magenta as default
         }
    //  }
      //else
      //{
      //  strip.setPixelColor( 0, strip.Color( palette1[7][0], palette1[7][1], palette1[7][2])); // magenta as default
     // }
    }
         break;
 case 133:
    {
      switch (roomState)
      {
        case 1:
            strip.setPixelColor( 3, strip.Color( palette1[2][0], palette1[2][1], palette1[2][2])); // green as default
          break;
        case 2:
            strip.setPixelColor( 3, strip.Color( palette1[1][0], palette1[1][1], palette1[1][2])); // red
          break;
        case 3:
            strip.setPixelColor( 3, strip.Color( palette1[3][0], palette1[3][1], palette1[3][2])); // blue as default
          break;
        case 4:
            strip.setPixelColor( 3, strip.Color( palette1[4][0], palette1[4][1], palette1[4][2])); // yellow as default
          break;
        case 5:
            strip.setPixelColor( 3, strip.Color( palette1[5][0], palette1[5][1], palette1[5][2])); // magenta as default
          break;
        default:
            strip.setPixelColor( 3, strip.Color( palette1[8][0], palette1[8][1], palette1[8][2])); // magenta as default
      }
    }
       break;
    case 134:
    {
      switch (roomState)
      {
        case 1:
            strip.setPixelColor( 26, strip.Color( palette1[2][0], palette1[2][1], palette1[2][2])); // green as default
          break;
        case 2:
            strip.setPixelColor( 26, strip.Color( palette1[1][0], palette1[1][1], palette1[1][2])); // red
          break;
        case 3:
            strip.setPixelColor( 26, strip.Color( palette1[3][0], palette1[3][1], palette1[3][2])); // blue as default
          break;
        case 4:
            strip.setPixelColor( 26, strip.Color( palette1[4][0], palette1[4][1], palette1[4][2])); // yellow as default
          break;
        case 5:
            strip.setPixelColor( 26, strip.Color( palette1[5][0], palette1[5][1], palette1[5][2])); // magenta as default
          break;
        default:
            strip.setPixelColor( 26, strip.Color( palette1[8][0], palette1[8][1], palette1[8][2])); // magenta as default
      }
    }
      break;
    case 135:
    {
      switch (roomState)
      {
        case 1:
            strip.setPixelColor( 2, strip.Color( palette1[2][0], palette1[2][1], palette1[2][2])); // green as default
          break;
        case 2:
            strip.setPixelColor( 2, strip.Color( palette1[1][0], palette1[1][1], palette1[1][2])); // red
          break;
        case 3:
            strip.setPixelColor( 2, strip.Color( palette1[3][0], palette1[3][1], palette1[3][2])); // blue as default
          break;
        case 4:
            strip.setPixelColor( 2, strip.Color( palette1[4][0], palette1[4][1], palette1[4][2])); // yellow as default
          break;
        case 5:
            strip.setPixelColor( 2, strip.Color( palette1[5][0], palette1[5][1], palette1[5][2])); // magenta as default
          break;
        default:
            strip.setPixelColor( 2, strip.Color( palette1[8][0], palette1[8][1], palette1[8][2])); // magenta as default
      }
    }
    break;
          //default:
            //strip.setPixelColor( 0, strip.Color( palette1[7][0], palette1[7][1], palette1[7][2])); // magenta as default
  }
        strip.show();
        delay(500); 
  
} //end loop



   

void Blink_N(int N){
  for(int i = N; i > 0; i--)
  {
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(relayPin, LOW);
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(relayPin, HIGH);
  delay(500);
  }  
}  
