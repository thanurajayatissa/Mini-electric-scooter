#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

TinyGPS gps; 

float lat = 6.877246,lon = 79.989929; 



SoftwareSerial mySerial(9, 10); 
void setup()
{
  lcd.begin(16, 2);
  mySerial.begin(9600);   
  Serial.begin(9600);    
  Serial.println("Welcome to the scooter GPS tracker");
  Serial.println("......................");
  Serial.println();
  delay(100);
}


void loop()
{
  
  
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
    case 'S':
      mySerial.println("Getting ready");    
     delay(1000); 
     mySerial.println("Text to +94779703904"); 
     delay(1000);

     
    

     Serial.println();
    
     Serial.println("Scooter Location....");
     Serial.println(gps_connect());
     Serial.println("......................");
     
     Serial.println();
     delay(100);
     mySerial.println((char)26);
      delay(1000);
      break;



      
    case 'r':
    case 'R':
      mySerial.println("AT+CNMI=2,2,0,0,0"); 
      delay(1000);
      break;
  }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}


float gps_connect() {
  while (Serial.available()) { 
    if (gps.encode(Serial.read())) 
    {
      gps.f_get_position(&lat, &lon); 
    
    }
  }

  String latitude = String(lat, 6);
  String longitude = String(lon, 6);
  Serial.println("Latitude: " + latitude + "," "Longitude: " + longitude);
  
  delay(1000);
  
  String latitude1 = String(lat, 4);
  String longitude1 = String(lon, 4);
  lcd.clear();
     lcd.setCursor(0, 0);
    lcd.print("Scooter Location:");
  
     lcd.setCursor(0, 1);
    lcd.print(latitude1 + " " + longitude1  );
    
}
