#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h> 
#include <ArduinoJson.h> 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define black   0x0000
#define blue    0x001F
#define red     0xF800
#define green   0x07E0
#define cyan    0x07FF
#define magenta 0xF81F
#define yellow  0xFFE0


#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* ssid = "SLT_FIBER "; 
const char* password = "jayathissa"; 

String Location = "Colombo, LK";
String API_Key = "f4793d8deec4b94c960e31a001a42ca2";

const long utcOffsetInSeconds = 0;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};



WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup(void)
{ 
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  
  delay(2000);
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20, 20);

  display.println("HELLO");

  display.display(); 
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  

}
void loop() 
  {
if (WiFi.status() == WL_CONNECTED) 
{
timeClient.begin();

HTTPClient http; 



http.begin("http://api.openweathermap.org/data/2.5/weather?q=" + Location + "&APPID=" + API_Key); 
 
int httpCode = http.GET();
 
if (httpCode > 0) 
{
String payload = http.getString(); 
 
DynamicJsonBuffer jsonBuffer(512);
 

JsonObject& root = jsonBuffer.parseObject(payload);
if (!root.success()) {
Serial.println(F("Parsing failed!"));
return;
}
 
float temp = (float)(root["main"]["temp"]) - 273.15; 
int humidity = root["main"]["humidity"]; 
float pressure = (float)(root["main"]["pressure"]) / 1000; 
float wind_speed = root["wind"]["speed"]; 
int wind_degree = root["wind"]["deg"]; 


Serial.printf("Temperature = %.2f°C\r\n", temp);
Serial.printf("Humidity = %d %%\r\n", humidity);
Serial.printf("Pressure = %.3f bar\r\n", pressure);
Serial.printf("Wind speed = %.1f m/s\r\n", wind_speed);
Serial.printf("Wind degree = %d°\r\n\r\n", wind_degree);
Serial.print(daysOfTheWeek[timeClient.getDay()]);

 display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(daysOfTheWeek[timeClient.getDay()]);
  display.setCursor(60, 0);
  display.print(timeClient.getFormattedTime());
  delay(1000);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.printf("Temperature= %.2fC\r\n", temp);
  display.setCursor(0, 50);
  display.printf("Humidity = %d %%\r\n", humidity);
  display.display(); 
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(daysOfTheWeek[timeClient.getDay()]);
  display.setCursor(60, 0);
  display.print(timeClient.getFormattedTime());
  delay(1000);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.printf("Pressure = %.3f bar\r\n", pressure);
  display.setCursor(0, 50);
  display.printf("Wind speed = %.1f m/s\r\n", wind_speed);
  display.display(); 
  delay(2000);

  display.clearDisplay();

  if(temp < 30){
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.printf("Weather looks great!");
  display.setCursor(0, 30);
  display.printf("Let's go for a ride!");
  display.display(); 
  delay(3000);
  }else{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 30);
  display.printf("The weather looks bad!");
  display.display(); 
  delay(3000);
 
}

 
http.end(); 
 
}
 
delay(6000); 
 
}

delay(1000);
  }
