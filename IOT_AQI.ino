#include "FirebaseESP8266.h"
#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include "MQ135.h"

FirebaseData fbdo;

#define FIREBASE_HOST "iot-based-aqi-default-rtdb.firebaseio.com"  // the project name address from firebase id
#define FIREBASE_AUTH "*****************************************"  // the secret key generated from firebase

#define WIFI_SSID "FBI OPEN UP!"
#define WIFI_PASSWORD "ReliableBat#64"

#define DHTPIN D6
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(D8, D7,D5, D4, D3, D2); 

/*
  DB8 ==> RS
  GND  ==>   R/W
  DB7  ==> Enable
  DB5   ==> DL4
  DB4   ==> DL5
  DB3   ==> DL6
  DB2   ==> DL7
*/

//const int buzzer = D8;
MQ135 gasSensor = MQ135 (A0);
String quality = "";
float g = (gasSensor.getPPM());


void setup()
{
  //LCD CODE
  Serial.begin(9600);
  
  
  //ESP8266 CODE

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                  //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);     // connect to firebase
  Firebase.reconnectWiFi(true);                         //Start reading dht sensor

  lcd.begin(16,2);
  lcd.setCursor (0,0);                  
  lcd.print("  Team : N 11");
  delay(2000);
  lcd.setCursor (0,0);
  lcd.print(" Mini Project 2");
  delay(2000);
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print("   MONITORING");
  delay(2000);    
  lcd.clear();
  dht.begin(); 
}

void loop()
{
  float g = (gasSensor.getPPM());
  
    if(g < 50){
      quality = "GOOD! Fresh Air";
      //noTone(buzzer);
    }
    else if (g >50 && g <100){
      quality = "FAIR! OpenWindow";
      //tone(buzzer, 25000);
    }
     else{
      quality = "POOR! ESCAPE!";
      //tone(buzzer, 25000);
    }
 
  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  String q = quality;

  if (isnan(h) || isnan(t)) {       // Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.println(" %");
   String fireHumid = String(h) + String("%");       //convert integer to string

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" °C");
    String fireTemp = String(t) + String(" C");      //convert integer to string

    Serial.print("Air Quality: ");
    Serial.print(g);
    Serial.println(" PPM");
    String fireGasLevel = String(g) + String(" PPM");    //convert integer to string

    
    Serial.println(quality);
    Serial.println();
    String fireComment = String(quality);

    //delay(1000);
    

    lcd.setCursor (0,0);
    lcd.print("AQI: ");
    lcd.setCursor (0,1);
    lcd.println(fireGasLevel);  
    delay(2000);
    lcd.clear();
    
    lcd.setCursor (0,0);
    lcd.print(quality);
    delay(2000);
    lcd.clear();

    lcd.setCursor (0,0);
    lcd.print("Temp:");
    lcd.setCursor (0,1);
    lcd.println(fireTemp);
    delay(2000);
    lcd.clear();

    lcd.setCursor (0,0);
    lcd.print("Humidity:");
    lcd.setCursor (0,1);
    lcd.println(fireHumid);
    delay(2000);
    lcd.clear();
    
   Firebase.setString(fbdo, "AQI", fireGasLevel);
   Firebase.setString(fbdo, "Temp",fireTemp);
   Firebase.setString(fbdo, "Humidity",fireHumid);
   Firebase.setString(fbdo, "Comment",fireComment);

}
