int i=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
i=analogRead(A1);
Serial.println(i);
delay(15);

}
