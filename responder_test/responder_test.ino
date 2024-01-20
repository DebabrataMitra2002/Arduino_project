/*
  ESP-NOW Remote Sensor - Receiver (Multiple Version)
  esp-now-rcv.ino
  Receives Temperature & Humidity data from other ESP32 via ESP-NOW
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/
 
// Include required libraries
#include <WiFi.h>
#include <esp_now.h>
const char* ssid = "Suparna_2.4G";
const char* password = "sunshine_23";
// Define data structure
typedef struct struct_message {
    float a;
    float b;
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
  Serial.print(": ");
  Serial.println(myData.a);
    
  Serial.print("Gyroscope Sensor ");
  Serial.print(myData.c);
  Serial.print(": ");
  Serial.println(myData.b); 
 
  Serial.println("");
}
 
void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);
 
  // Start ESP32 in Station mode
  // WiFi.mode(WIFI_STA);
  // Set the device as a Station and Soft Access Point simultaneously
  WiFi.mode(WIFI_AP_STA);
  
   // Set device as a Wi-Fi Station
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

  
}
 
void loop() {
  }