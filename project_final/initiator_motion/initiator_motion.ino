#include <esp_now.h>
#include <WiFi.h>
#include <HTTPClient.h>

const int PIR_SENSOR_OUTPUT_PIN = 13;  // PIR sensor output pin
int warm_up;
int id = 1;
uint8_t broadcastAddress[] = {0xC8, 0xF0, 0x9E, 0xA2, 0x97, 0x50}; // REPLACE WITH YOUR RECEIVER MAC Address

typedef struct struct_message {
  char a[32];
  bool b;
  int d;
} struct_message;

struct_message myData;

const char* WIFI_SSID = "HONOR Pad 5";
const char* WIFI_PASSWORD = "debodola1234";
String URL = "http://192.168.43.27/pir_project/data_log.php";

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);
  pinMode(PIR_SENSOR_OUTPUT_PIN, INPUT);
  Serial.println("Waiting For Power On Warm Up");
  delay(2000);
  Serial.println("Ready!");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  int sensor_output = digitalRead(PIR_SENSOR_OUTPUT_PIN);
  if (sensor_output == LOW) {
    if (warm_up == 1) {
      Serial.print("Warming Up\n\n");
      warm_up = 0;
      delay(1000);
    }
    Serial.print("No object in sight\n\n");
    myData.b = false;
    myData.d = id;
    delay(1000);
  } else {
    Serial.print("Object detected\n\n");
    myData.b = true;
    myData.d = id;
    delay(1000);
  }

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }

  delay(2000);
}

