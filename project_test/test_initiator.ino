#include <WiFi.h>
#include <esp_now.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <esp_wifi.h>
Adafruit_MPU6050 mpu;
// Integer for identification (make unique for each transmitter)
int ident = 1;
const int PIN_TO_SENSOR = 19; // GPIO19 pin connected to OUTPUT pin of sensor
int pinStateCurrent   = LOW;  // current state of pin
int pinStatePrevious  = LOW;  // previous state of pin
bool pir=0;
// Responder MAC Address (Replace with your responders MAC Address)
//uint8_t broadcastAddress[] = {0xC8, 0xF0, 0x9E, 0xA2, 0x97, 0x50};
//uint8_t broadcastAddress[] = {0xB8, 0xD6, 0x1A, 0xAB, 0xBA, 0xC0};
uint8_t broadcastAddress[] = {0xB0, 0xA7, 0x32, 0x15, 0xEA, 0x38};
// Define data structure
typedef struct struct_message 
{
  float a1,a2,a3;
  float b1,b2,b3;
  bool d;
  int c;
} struct_message;
constexpr char WIFI_SSID[] = "4G";

int32_t getWiFiChannel(const char *ssid) 
{
  if (int32_t n = WiFi.scanNetworks()) 
  {
      for (uint8_t i=0; i<n; i++) 
      {
          if (!strcmp(ssid, WiFi.SSID(i).c_str())) 
          {
              return WiFi.channel(i);
          }
      }
  }
  return 0;
}
// Create structured data object
struct_message myData;

// Register peer
esp_now_peer_info_t peerInfo;

// Sent data callback function
void OnDataSent(const uint8_t *macAddr, esp_now_send_status_t status)
{
  Serial.print("Last Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {

  // Setup Serial monitor
  Serial.begin(115200);
  delay(10);
  pinMode(PIN_TO_SENSOR, INPUT); // set ESP32 pin to input mode to read value from OUTPUT pin of sensor
 Serial.println("Adafruit MPU6050 test!");

if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  // Set ESP32 WiFi mode to Station temporarly
  WiFi.mode(WIFI_STA);
  int32_t channel = getWiFiChannel(WIFI_SSID);

  WiFi.printDiag(Serial); // Uncomment to verify channel number before
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);
  WiFi.printDiag(Serial); // Uncomment to verify channel change after

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Define callback
  esp_now_register_send_cb(OnDataSent);


  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  Serial.println("");
  delay(100);

}

void loop() {
 sensors_event_t ac1, g1, temp;
  mpu.getEvent(&ac1, &g1, &temp);
  pinStatePrevious = pinStateCurrent; // store old state
  delay(1);
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);   // read new state

  if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {   // pin state change: LOW -> HIGH
    pir=1;
    Serial.println("Motion detected!");
  }
  else if (pinStatePrevious == HIGH && pinStateCurrent == LOW) {   // pin state change: HIGH -> LOW
  pir=0;
  Serial.println("Motion stopped!");
  }

  myData.a1 = ac1.acceleration.x;
  myData.a2 = ac1.acceleration.y;
  myData.a3 = ac1.acceleration.z;
  delay(10);
  myData.b1 = g1.gyro.x;
  myData.b2 = g1.gyro.y;
  myData.b3 = g1.gyro.z;
  myData.d=pir;
  myData.c = ident;
  delay(1);
  Serial.print("Acceleration");
  Serial.print("myData.c");
  Serial.print(":");
  Serial.print(" X: ");
  Serial.print(ac1.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(ac1.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(ac1.acceleration.z);
  Serial.println(" m/s^2");
  Serial.print("Rotation");
  Serial.print("myData.c");
  Serial.print(":");
  Serial.print(" X: ");
  Serial.print(g1.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g1.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g1.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.println("");
  delay(10);
  // Add to structured data object
  

  // Send data
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));


  delay(100);
}
