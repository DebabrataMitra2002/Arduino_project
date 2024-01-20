#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(5);  // attaches the servo on pin 5 to the servo object
}

void loop() {
  // myservo.write(1);     //t to d             // sets the servo position to the middle position
  //  delay(1000);                        // waits for a second
  myservo.write(72000);   //d to t              // sets the servo position to the maximum position
                       // waits for a second                        // waits for a second
}
