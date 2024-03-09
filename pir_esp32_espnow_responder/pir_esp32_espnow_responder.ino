#include <esp_now.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials (STATION)
const char* ssid = "HONOR Pad 5";
const char* password = "debodola1234";

// Replace with your Google Script ID
String GOOGLE_SCRIPT_ID = "AKfycbwGQLYjnrDj7_DzoehJuk3xm9pX6UnmbcV8QpoOwaCo1tqwl6kgwQvZUBihRyFYDaE";

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32];
    bool b;
    int d;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Initialize a secure client object
WiFiClientSecure client;

// Function to send data to Google Sheets
void sendData(bool bValue, int dValue) {
   HTTPClient http;

   // Construct the URL with parameters
   String url = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec";
   
   // Set the parameters in the request body
   String requestBody = "sensorId=" + String(bValue) + "&sensorStatus=" + String(dValue);

   // Make the HTTP request
   Serial.print("Sending data to Google Sheets: ");
   Serial.println(url);
   http.begin(client, url); // Specify the client and URL
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");

   int httpCode = http.POST(requestBody); // Use POST method with request body
   if (httpCode > 0) {
     Serial.print("HTTP Response Code: ");
     Serial.println(httpCode);
   } else {
     Serial.print("HTTP Error: ");
     Serial.println(http.errorToString(httpCode).c_str());
   }
   
   http.end();
}

// Callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  // Copy received data into the message structure
  memcpy(&myData, incomingData, sizeof(myData));

  // Print received data
  Serial.print("Received Data - b: ");
  Serial.println(myData.b);
  Serial.print("Received Data - d: ");
  Serial.println(myData.d);

  // Send the received data to Google Sheets
  sendData(myData.b, myData.d);
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial); // Wait for Serial Monitor to open
  
  // Set the device as a Station and Soft Access Point simultaneously
  WiFi.mode(WIFI_AP_STA);
  
  // Set device as a Wi-Fi Station
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  Serial.print("Connected. IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Wi-Fi Channel: ");
  Serial.println(WiFi.channel());
  
  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register callback for receiving data
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("Initialization complete");
}
 
void loop() {
  // Your additional code or tasks can go here
  delay(1000); // Add a delay to avoid excessive looping
}



