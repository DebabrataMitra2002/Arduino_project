void setup() {
  // Robojax.com push button tutorial
  pinMode(4,INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Robojax Push button Tutorial");
  

}

void loop() {
  // Robojax.com push button tutorial
  int pushButton = digitalRead(4);
  if(pushButton == LOW)
  {
    Serial.println("Pin 4 LOW");
  }else if(pushButton == HIGH)
  {
    Serial.println("Pin 4 HIGH");
  }

delay(500);
}
 