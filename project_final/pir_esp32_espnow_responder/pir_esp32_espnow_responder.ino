
#include <esp_now.h>
#include <WiFi.h>
#include <HTTPClient.h>


String URL = "http://192.168.43.27/pir_project/data_log.php";
// Replace with your network credentials (STATION)
const char* ssid = "HONOR Pad 5";
const char* password = "debodola1234";

// // Replace with your Google Script ID
// const String GOOGLE_SCRIPT_ID = "AKfycbxudMWgLrEFzEf6Ao_SO2HKeWXQh_0q2ehlMoBZZKS6GREPIpHBCnVJPz_d7IRFEu_7";

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32];
    bool b;
    int d;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Initialize a client object


// Function to send data to Google Sheets
// void sendData(bool bValue, int dValue) {
//    HTTPClient http;

//    // Construct the URL with parameters
//    String url = "http://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?";
//    url += "sensorId=" + String(bValue);
//    url += "&sensorStatus=" + String(dValue);

//    // Make the HTTP request
//    Serial.print("Sending data to Google Sheets: ");
//    Serial.println(url);
//    http.begin(url); // Specify the URL

//    int httpCode = http.GET();
//    if (httpCode > 0) {
//      Serial.print("HTTP Response Code: ");
//      Serial.println(httpCode);
//    } else {
//      Serial.print("HTTP Error: ");
//      Serial.println(http.errorToString(httpCode).c_str());
//    }
   
//    http.end();
// }

// Callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  // Copy received data into the message structure
  memcpy(&myData, incomingData, sizeof(myData));

  // Print received data
  Serial.print("SensorId: ");
  Serial.print(myData.d);
  Serial.print("SensorStatus: ");
  Serial.println(myData.b);
  

  // Send the received data to Google Sheets
  // sendData(myData.b, myData.d);
}

 void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  //This line hides the viewing of ESP as wifi hotspot
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 }
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial); // Wait for Serial Monitor to open
  
    connectWiFi();

  // Set the device as a Station and Soft Access Point simultaneously
  // WiFi.mode(WIFI_AP_STA);
  // WiFi.mode(WIFI_STA);
  // // Set device as a Wi-Fi Station
  // WiFi.begin(ssid, password);
  // Serial.print("Connecting to Wi-Fi");
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println();
  
  // Serial.print("Connected. IP Address: ");
  // Serial.println(WiFi.localIP());
  // Serial.print("Wi-Fi Channel: ");
  // Serial.println(WiFi.channel());
  
  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register callback for receiving data
  esp_now_register_recv_cb(OnDataRecv);
}
  
 
void loop() {
//  {if(WiFi.status() != WL_CONNECTED) { 
//     connectWiFi();
//   } 
if(myData.b==1)
{
  Serial.println("Initialization complete");
  String postData = "SensorId=" + String(myData.d) + "&SensorStatus=" + String(myData.b); 

  HTTPClient http; 
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpCode = http.POST(postData); 
  String payload = http.getString(); 
  
  Serial.print("URL : "); Serial.println(URL); 
  Serial.print("Data: "); Serial.println(postData); 
  Serial.print("httpCode: "); Serial.println(httpCode); 
  Serial.print("payload : "); Serial.println(payload); 
  Serial.println("--------------------------------------------------");
  } 
  delay(2000);
}
 
 // Your additional code or tasks can go here
//   delay(1000); // Add a delay to avoid excessive looping

