const int pingPin1 = 14;
const int pingPin2 = 25;
const int pingPin3 = 33;
const int pingPin4 = 32;

void setup() {
  Serial.begin(115200);
}

void loop() {
  sensorSonar(pingPin1,1);
  sensorSonar(pingPin2,2);
  sensorSonar(pingPin3,3);
  sensorSonar(pingPin4,4);

}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
void sensorSonar(int pingPin,int sensor_num)
{
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  if(cm>=10 && cm<=50 )
  {
   Serial.print("motion");
   Serial.print(sensor_num);
   Serial.println();
  }
  else{
        Serial.println("no movement");
  }
// Serial.print(inches);
  // Serial.print("in, ");
  // Serial.print(cm);
  // Serial.print("cm");
  delay(100);
}
