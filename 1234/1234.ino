#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
// #include <esp_wifi.h>
Adafruit_MPU6050 mpu;
// Integer for identification (make unique for each transmitter)
int ident = 2;
// REPLACE WITH RECEIVER MAC Address
// uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t broadcastAddress[] = {0xB0, 0xA7, 0x32, 0x15, 0xEA, 0x38};

typedef struct struct_message 
{
  float a1,a2,a3;
  float b1,b2,b3;
  int c;
} struct_message;
struct_message myData;


int32_t getWiFiChannel(const char *ssid) {
  if (int32_t n = WiFi.scanNetworks()) {
      for (uint8_t i=0; i<n; i++) {
          if (!strcmp(ssid, WiFi.SSID(i).c_str())) {
              return WiFi.channel(i);
          }
      }
  }
  return 0;
}
// // Create a struct_message called myData
// unsigned long lastTime = 0;  
// unsigned long timerDelay = 2000;  // send readings timer

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 delay(10);
 Serial.println("Adafruit MPU6050 test!");

if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
   WiFi.mode(WIFI_STA);
  int32_t channel = getWiFiChannel(WIFI_SSID);

  WiFi.printDiag(Serial); // Uncomment to verify channel number before
   // set WiFi channel   
  wifi_promiscuous_enable(1);
  wifi_set_channel(channel);
  wifi_promiscuous_enable(0);
  WiFi.printDiag(Serial); 
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

  // esp_wifi_set_promiscuous(true);
  // esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
  // esp_wifi_set_promiscuous(false);
  // WiFi.printDiag(Serial); // Uncomment to verify channel change after


  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE,11, NULL, 0);
}
 
void loop() {
sensors_event_t ac1, g1, temp;
  mpu.getEvent(&ac1, &g1, &temp);
  // Read DHT22 module values
  myData.a1 = ac1.acceleration.x;
  myData.a2 = ac1.acceleration.y;
  myData.a3 = ac1.acceleration.z;
  delay(10);
  myData.b1 = g1.gyro.x;
  myData.b2 = g1.gyro.y;
  myData.b3 = g1.gyro.z;
  myData.c = ident;
  delay(10);
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
  delay(500);
  // Add to structured data object
  ;

    // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    delay(1000);
  
  }
