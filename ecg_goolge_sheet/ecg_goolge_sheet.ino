#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define ecg_PIN   36
// #define DHTPIN    23

//our sensor is DHT11 type
// #define DHTTYPE DHT11
// DHT dht(DHTPIN, DHTTYPE);
// const int pingPin = 14;
// long duration, inches, cm;
const char * ssid = "Redmi Note 9 Pro Max";
const char * password = "Bhule gechi";

String server = "http://maker.ifttt.com";
String eventName = "temp_data";
String IFTTT_Key = "dI0KkxUIn9EVXpJoCwP1tdV1gWJrHw-aPwV0l45SGX7";
String IFTTTUrl="http://maker.ifttt.com/trigger/temp_data/with/key/dI0KkxUIn9EVXpJoCwP1tdV1gWJrHw-aPwV0l45SGX7";
int value1;
int value2;
int value3;

void setup() {
  Serial.begin(115200);
  // dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Viola, Connected !!!");
}

float getEcg(void)
{
  int Ecg;
//   float percentage;
  Ecg = analogRead(ecg_PIN);    
//   percentage = ((float)((ldrRawVal*100)/4096));
  return Ecg;
}

void sendDataToSheet(void)
{
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1=" + String((int)value1) + "&value2="+String((int)value2) +"&value3=" + String((int)value3);  
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
 // Setup for leads off detection LO -
// pinMode(4, OUTPUT);

  // value1 = Distance();
  // value2 = dht.readTemperature();
  //  = getLightPercentage(); 
  value3=getEcg();

  Serial.print("Values are ");
  Serial.print(value1);
  Serial.print(' ');
  Serial.print(value2);
  Serial.print(' ');
  Serial.println(value3);
  Serial.print(' '); 

  sendDataToSheet();
  delay(100);
}
// long Distance() {
//     pinMode(pingPin, OUTPUT);             /*Define pingPin as a output*/
//   digitalWrite(pingPin, LOW);
//   delayMicroseconds(2);                 /*Wait for 2uS*/
//   digitalWrite(pingPin, HIGH);
//   delayMicroseconds(5);                 /*Wait for 5uS*/
//   digitalWrite(pingPin, LOW);
//   pinMode(pingPin, INPUT);              /*Define pingPin as a input*/
//   duration = pulseIn(pingPin, HIGH);    /*Reads a pulse HIGH on a pingPin*/
 
//   cm = microsecondsToCentimeters(duration); /*Convert the time into cm*/
//   inches = microsecondsToInches(duration);  /*Convert the time into inch*/
//    return cm;
// }

// long microsecondsToInches(long microseconds) {return microseconds / 74 / 2;}
// long microsecondsToCentimeters(long microseconds) {return microseconds / 29 / 2;}