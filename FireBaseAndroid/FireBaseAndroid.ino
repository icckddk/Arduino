#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define DHTPIN D4
#define DHTTYPE DHT11

#include <DHT.h>
DHT dht(DHTPIN, DHTTYPE);


// Set these to run example.
#define FIREBASE_HOST "fir-dht11-b45d1.firebaseio.com"
#define FIREBASE_AUTH "uLbbq6QTziu2F4zfws6GnRc6cumGqU7XNSPJVHBh"
#define WIFI_SSID "2424"
#define WIFI_PASSWORD "qorhvms1219"

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
  Serial.print("Temperature = ");
  Serial.println(temp);
  Serial.print("Humidity = ");
  Serial.println(humi);
  
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
