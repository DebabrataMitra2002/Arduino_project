#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "html.h"

Adafruit_MPU6050 mpu;

WebServer server(80);

const char* ssid = "Ping Me";         /*Enter Your SSID*/
const char* password = "Abhishek@12345"; /*Enter Your Password*/

float x_acceleration, y_acceleration, z_acceleration;
float x_gyro, y_gyro, z_gyro;
float tempe;

void MainPage() {
  String _html_page = html_page;              /*Read The HTML Page*/
  server.send(200, "text/html", _html_page);  /*Send the code to the web server*/
}

void Web_MPU6050() {
  String data = "[\""+String(x_acceleration)+"\",\""+String(y_acceleration)+"\",\""+String(z_acceleration)+"\",\""+String(x_gyro)+"\",\""+String(y_gyro)+"\",\""+String(z_gyro)+"\",\""+String(tempe)+"\"]";
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
 

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
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

  Serial.println("");
  delay(100);

  server.on("/", MainPage);             /*Display the Web/HTML Page*/
  server.on("/read_Web_MPU6050", Web_MPU6050); /*Display the updated Distance value(CM and INCH)*/
  server.begin();                       /*Start Server*/
  delay(1000);                          /*Wait for 1000mS*/
 
}

void loop(void){
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
 
  x_acceleration = a.acceleration.x;
  y_acceleration = a.acceleration.y;
  z_acceleration = a.acceleration.z;
  x_gyro = g.gyro.x;
  y_gyro = g.gyro.y;
  z_gyro = g.gyro.z;
  tempe = temp.temperature;
 
  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(x_acceleration);
  Serial.print(", Y: ");
  Serial.print(y_acceleration);
  Serial.print(", Z: ");
  Serial.print(z_acceleration);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(x_gyro);
  Serial.print(", Y: ");

  Serial.print(y_gyro);
  Serial.print(", Z: ");
  Serial.print(z_gyro);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(tempe);
  Serial.println(" degC");

  Serial.println("");
  delay(500);

  server.handleClient();
}
