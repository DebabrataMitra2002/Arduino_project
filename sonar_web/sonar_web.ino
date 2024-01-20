// const char* ssid = "*Your SSID*";         /*Enter Your SSID*/
// const char* password = "*Your Password*"; /*Enter Your Password*/
 

// Ultrasonic Sensor WebServer Code for ESP32
// /*
//   ESP32 Ultrasonic HC-Sr04 WebServer Code 
//   http:://www.electronicwings.com
// */

#include <WiFi.h>
#include <WebServer.h>
#include "html.h"

WebServer server(80);

const char * ssid = "Redmi Note 9 Pro Max";
const char * password = "Bhule gechi"; /*Enter Your Password*/

const int pingPin = 14;
long duration, inches, cm;

void MainPage() {
  String _html_page = html_page;              /*Read The HTML Page*/
  server.send(200, "text/html", _html_page);  /*Send the code to the web server*/
}

void Distance() {
  String data = "[\""+String(cm)+"\",\""+String(inches)+"\"]";
  server.send(200, "text/plane", data);
}

void setup(void){
  Serial.begin(115200);                 /*Set the baudrate to 115200*/
  WiFi.mode(WIFI_STA);                  /*Set the WiFi in STA Mode*/
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  delay(1000);                         /*Wait for 1000mS*/
  while(WiFi.waitForConnectResult() != WL_CONNECTED){Serial.print(".");} /*Wait while connecting to WiFi*/
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("Your Local IP address is: ");
  Serial.println(WiFi.localIP());       /*Print the Local IP*/

  server.on("/", MainPage);             /*Display the Web/HTML Page*/
  server.on("/readDistance", Distance); /*Display the updated Distance value(CM and INCH)*/
  server.begin();                      /*Start Server*/
  delay(1000);                         /*Wait for 1000mS*/
}

void loop(void){
  pinMode(pingPin, OUTPUT);             /*Define pingPin as a output*/
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);                 /*Wait for 2uS*/
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);                 /*Wait for 5uS*/
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);              /*Define pingPin as a input*/
  duration = pulseIn(pingPin, HIGH);    /*Reads a pulse HIGH on a pingPin*/
 
  cm = microsecondsToCentimeters(duration); /*Convert the time into cm*/
  inches = microsecondsToInches(duration);  /*Convert the time into inch*/
 
  server.handleClient();
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(1000);
}

long microsecondsToInches(long microseconds) {return microseconds / 74 / 2;}
long microsecondsToCentimeters(long microseconds) {return microseconds / 29 / 2;}