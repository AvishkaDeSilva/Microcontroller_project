#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <SD.h>
#include "DHT.h"
#define DHTPIN 2
File Dhtemp;
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
#include "RTClib.h"
#include <ArduinoJson.h>
#define HOST2 "iot_device_page.com" //server  name
#define WIFI_SSID "wifi"   // Enter wifi name
#define WIFI_PASSWORD "1234"  // Enter wifi password
DynamicJsonDocument doc(1024);
int a=1;
RTC_DS1307 RTC;
void setup() {
  Serial.begin(115200);
  Wire.begin(); // Start the I2C
  RTC.begin();  // Init RTC
  RTC.adjust(DateTime(__DATE__, __TIME__));
  dht.begin();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());
  delay(1000);
}

void loop() {
  DateTime now = RTC.now();
  String datee=sprintf(buf1, "%02d/%02d/%02d %02d:%02d:%02d",  now.year(),now.month(),now.date(),now.hour(), now.minute(), now.second()); 
  deserializeJson(doc, Serial);
  HTTPClient http2;
  float temp = doc["temp"];
  float humidity = doc["humidity"];
  double pressure = doc["pressure"];
  float light = doc["light"];
  delay(1000);
  String postData= "sendval1=" + temp  + "&sendval2=" + humidity + "&sendval3=" + pressure + "&sendval4=" +  light + "&sendval5=" + datee;
  delay(100);
  if(WiFi.status()){
    if(a==0){
      myFile = SD.open("temp.txt");
      if (myFile) { 
        while (myFile.available()) { //execute while file is available
          char letter = myFile.read(); //read next character from file
          http2.begin("http://iot_device_page.com/ardunio.php");
          http2.addHeader("Content-Type","application/x-www-form-urlencoded");
          int httpCodess = http2.POST(letter);
          Serial.println("success-3");
          if(httpCodess==200){
            Serial.println("success-4");
            Serial.println(httpCodess);
            String webpage=http2.getString();
            Serial.println(webpage+"\n");
          }else{
            Serial.println(httpCodess);
            http2.end();
            return;
          }
          delay(300);
        }

        myFile.close(); //close file
      }
      SD.remove("temp.txt");
      a=1;
    }else{
    http2.begin("http://iot_device_page.com/ardunio.php");
    http2.addHeader("Content-Type","application/x-www-form-urlencoded");
    int httpCodess = http2.POST(postData);
    Serial.println("success-3");
    if(httpCodess==200){
    Serial.println("success-4");
    Serial.println(httpCodess);
    String webpage=http2.getString();
    Serial.println(webpage+"\n");
  }else{
    Serial.println(httpCodess);
    http2.end();
    return;
  }
  delay(2000);
  }
  }else{
   Dhtemp = SD.open("temp.txt",FILE_WRITE);
   Dhtemp.println(postData);
   Dhtemp.close();
   a=0;
  }
  delay(840000);
}
