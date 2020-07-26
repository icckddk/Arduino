#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define DHTPIN D4
#define DHTTYPE DHT11

#include <DHT.h>
DHT dht(DHTPIN, DHTTYPE);
 
// Set these to run example.
#define FIREBASE_HOST "fir-android-40516.firebaseio.com"    
#define FIREBASE_AUTH "KgSV0SDa1tfcq5mHT6QQ7cuXk8XQNiPxFb0tLT5x" 
#define WIFI_SSID "space"
#define WIFI_PASSWORD "icckddk1242"

void setup() {
   Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  dht.begin(9600);
  
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

// Ardunio Code
void loop() {
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  
  Firebase.pushFloat("temperature", temp);
  Firebase.pushFloat("humidity", humi);
  
  if (Firebase.failed()) {  
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error()); 
    return;
   }
  Serial.print("pushed: /logDHT/"); 
  delay(5000);
}
