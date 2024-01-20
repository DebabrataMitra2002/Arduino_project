/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-ultrasonic-sensor
 */

#define TRIG_PIN 23 // ESP32 pin GPIO23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO1_PIN 22 // ESP32 pin GPIO22 connected to Ultrasonic Sensor's ECHO pin
#define ECHO2_PIN 21
float duration1_us,duration2_us,distance1_cm,distance2_cm;

void setup() {
  // begin serial port
  Serial.begin (9600);

  // configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO1_PIN, INPUT);
  pinMode(ECHO2_PIN, INPUT);
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration1_us = pulseIn(ECHO1_PIN, HIGH);
  duration2_us = pulseIn(ECHO2_PIN, HIGH);

  // calculate the distance
  distance1_cm = 0.017 * duration1_us;
  distance2_cm = 0.017 * duration2_us;

  // print the value to Serial Monitor
  Serial.print("distance1: ");
  Serial.print(distance1_cm);
  Serial.println(" cm");
  Serial.print("distance2: ");
  Serial.print(distance2_cm);
  Serial.println(" cm");
  delay(500);
}
