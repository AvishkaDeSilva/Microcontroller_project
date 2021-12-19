#include "DHT.h"
#include <SoftwareSerial.h> 
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
#include <SFE_BMP180.h>
#include <Wire.h>
#include <ArduinoJson.h>
SFE_BMP180 pressure;
#define ALTITUDE 943.7
int temt6000Pin = A0;
float light;
int light_value;
int count=0;
float averagehumidity=0;
float averagetemp=0;
float averagelight=0;
double averagepressure=0;
DynamicJsonDocument doc(1024);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pressure.begin();
  pinMode(temt6000Pin, INPUT);
  delay(2000);
}

void loop() {
  for (count = 0; count < 45; count++){
  char status;
  double T, P,airpressue;
  delay(100);   
  float humidity = dht.readHumidity();
  delay(100); 
  float temp = dht.readTemperature();
  delay(100); 
  int light_value = analogRead(temt6000Pin);
  delay(100); 
  light = light_value * 0.0976;
  delay(100); 
  status = pressure.startPressure(3);
  delay(100); 
      if (status != 0)
      {
        status = pressure.getPressure(P, T);
        delay(100); 
        if (status != 0){
          airpressue=(P * 0.014503774, 2);
          delay(100); 
        }
      }
  averagehumidity=averagehumidity+humidity;
  delay(100); 
  averagetemp=averagetemp+temp;
  delay(100); 
  averagelight=averagelight+light;
  delay(100); 
  averagepressure=averagepressure+airpressue;
  delay(100);
  count=count+1; 
  delay(15000);   
  }
  doc["temp"]   = averagetemp/45;
  delay(100); 
  doc["humidity"] = averagehumidity/45;
  delay(100); 
  doc["pressure"]= averagepressure/45;
  delay(100); 
  doc["light"] = averagelight/45;
  delay(100); 
  serializeJson(doc, Serial);
  delay(1000);
  averagetemp=0;
  delay(100);
  averagehumidity=0;
  delay(100);
  averagepressure=0;
  delay(100);
  averagelight=0;
  delay(100);
  count=0;
  delay(100);   
  
}
