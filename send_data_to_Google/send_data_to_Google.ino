#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// #define LDR_PIN   36
#define DHTPIN    23
// #define LQ   10
// #define lq   11
//our sensor is DHT11 type
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char * ssid = "Ping Me";
const char * password = "Abhishek@12345";

String server = "http://maker.ifttt.com";
String eventName = "temp_data";
String IFTTT_Key = "dI0KkxUIn9EVXpJoCwP1tdV1gWJrHw-aPwV0l45SGX7";
String IFTTTUrl="http://maker.ifttt.com/trigger/temp_data/with/key/dI0KkxUIn9EVXpJoCwP1tdV1gWJrHw-aPwV0l45SGX7";
int value1;
int value2;
int value3;
const int pingPin1 = 14;
const int pingPin2 = 25;
void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Viola, Connected !!!");
  
}

// float getLightPercentage(void)
// {
//   int ldrRawVal;
//   float percentage;
//   ldrRawVal = analogRead(LDR_PIN);    
//   percentage = ((float)((ldrRawVal*100)/4096));
//   return percentage;
// }

void sendDataToSheet(void)
{
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1=" + String((cons i)value1) + "&value2="+String((int)value2) +"&value3=" + String((int)value3);  
  Serial.println(url);
  //Start to send data to IFTTT
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
  http.begin(url); //HTTP

  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();

}

void loop() {
//   if((digitalRead(lq) == 1)||(digitalRead(LQ) == 1)){
// Serial.println('!');
// }
// else{
value3=analogRead(34);
// send the value of analog input 0:
Serial.println(value3);
// }
  value1 = sensorSonar(pingPin1,1);
  value2 = sensorSonar(pingPin2,2);

  // value3 = getLightPercentage(); 

  Serial.print("Values are ");
  Serial.print(value1);
  Serial.print(' ');
  Serial.print(value2);
  Serial.print(' ');
  Serial.println(value3);
  Serial.print(' '); 

  sendDataToSheet();
  delay(10);
}
long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
char sensorSonar(int pingPin,int sensor_num)
{
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  if(cm>=10 && cm<=50 )
  {
   
   return Serial.println("motion"+sensor_num);
  //  Serial.print(sensor_num);
  //  Serial.println();

  }
  else{
     return Serial.println("no movement");

  }
// Serial.print(inches);
  // Serial.print("in, ");
  // Serial.print(cm);
  // Serial.print("cm");
  delay(100);
}

