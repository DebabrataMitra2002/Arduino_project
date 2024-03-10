#include <esp_now.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "HONOR Pad 5";
const char* password = "debodola1234";
String URL = "http://192.168.43.27/pir_project/data_log.php";

typedef struct struct_message {
    char a[32];
    bool b;
    int d;
} struct_message;

struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));

  Serial.print("SensorId: ");
  Serial.print(myData.d);
  Serial.print(" SensorStatus: ");
  Serial.println(myData.b);
  
  if (myData.b == true) {
    HTTPClient http; 
    http.begin(URL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    String postData = "SensorId=" + String(myData.d) + "&SensorStatus=" + String(myData.b); 
    int httpCode = http.POST(postData); 
    String payload = http.getString(); 
    
    Serial.print("URL : "); Serial.println(URL); 
    Serial.print("Data: "); Serial.println(postData); 
    Serial.print("httpCode: "); Serial.println(httpCode); 
    Serial.print("payload : "); Serial.println(payload); 
    Serial.println("--------------------------------------------------");
  }
}

void connectWiFi() {
  // WiFi.mode(WIFI_OFF);
  // delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  connectWiFi();

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  delay(1000);
}
