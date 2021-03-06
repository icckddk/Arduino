#include <ESP8266WiFi.h>                                               
#include <FirebaseArduino.h>      
#define FIREBASE_HOST "fir-led-control-e539a.firebaseio.com"     
#define FIREBASE_AUTH "c7g3UCAfl93cvd4LToe9rSSUiZrQ4SZpgGDrEIws" 
#define WIFI_SSID "space"                                          
#define WIFI_PASSWORD "icckddk1242"  

String red_fireStatus = ""; 
String blue_fireStatus = ""; 
   
int red_led = D4;          
int blue_led = D3;
                                                              
void setup() 
{
  Serial.begin(9600);
  delay(1000);    
  pinMode(red_led, OUTPUT);  
  pinMode(blue_led, OUTPUT);
                 
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
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setString("RED_LED_STATUS", "OFF"); 
  Firebase.setString("BLUE_LED_STATUS", "OFF");
}
 
void loop() 
{
  red_fireStatus = Firebase.getString("RED_LED_STATUS");     
  if (red_fireStatus == "ON")   { 
    Serial.println("RED LED Turned ON");                                                        
    digitalWrite(red_led, HIGH);          
  } 
  else if (red_fireStatus == "OFF") {    
    Serial.println("RED LED Turned OFF");
    digitalWrite(red_led, LOW);    
  } else {
    Serial.println("Command Error! Please send ON/OFF");
  }

  delay(2000);

  blue_fireStatus = Firebase.getString("BLUE_LED_STATUS"); 
  if (blue_fireStatus == "ON")   { 
    Serial.println("BLUE LED Turned ON");                                                        
    digitalWrite(blue_led, HIGH);          
  } 
  else if (blue_fireStatus == "OFF") {    
    Serial.println("BlUE LED Turned OFF");
    digitalWrite(blue_led, LOW);      
  } else {
    Serial.println("Command Error! Please send ON/OFF");
  }

  delay(2000);
}
