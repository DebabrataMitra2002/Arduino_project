// Include required libraries
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <esp_now.h>
const char* ssid = "4G";
const char* password = "Kartick@jiofiber70";
 
//----------------------------------------Host & httpsPort
const char* host = "script.google.com";
const int httpsPort = 443;
WiFiClientSecure client; //--> Create a WiFiClientSecure object.
 
String GAS_ID = "AKfycby8Lfzwu-5SBj9tHxbw3_j8ZPZy6P6_3e_BBISC0Jg7SstXLUed"; //--> spreadsheet script ID
 
// Define data structure
typedef struct struct_message {
   
  float a1,a2,a3;
  float b1,b2,b3;
  bool d;
  int c;
} struct_message;
 
// Create structured data object
struct_message myData;
 
// Callback function
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
  // Get incoming data
  memcpy(&myData, incomingData, sizeof(myData));
  
  // Print to Serial Monitor
  Serial.print("Accelerometer Sensor ");
  Serial.print(myData.c);
  Serial.println(": ");
  Serial.print(" X: ");
  Serial.print(myData.a2);
  Serial.print(" y: ");
  Serial.print(myData.a1);
  Serial.print(" z: ");
  Serial.println(myData.a3);
  Serial.print("Gyroscope Sensor ");
  Serial.print(myData.c);
  Serial.println(": ");
  Serial.print(" X: ");
  Serial.print(myData.b1);
  Serial.print(" Y: ");
  Serial.print(myData.b2);
  Serial.print(" Z: ");
  Serial.print(myData.b3);
  Serial.println("");
  if(myData.d==1){
     Serial.println("motion start:");
 }
 else
   {Serial.println("motion stop:");} 


}
 
void setup(){
  Serial.begin(115200);
  // Start ESP32 in Station mode
  // WiFi.mode(WIFI_STA);
  WiFi.mode(WIFI_AP_STA); // Set the device as a Station and Soft Access Point simultaneously
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Setting as a Wi-Fi Station..");
  }
  Serial.print("Station IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Wi-Fi Channel: ");
  Serial.println(WiFi.channel());
  // Initalize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
  client.setInsecure();
  
}
void loop() {}
