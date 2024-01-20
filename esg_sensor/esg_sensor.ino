 void setup() {
// initialize the serial communication:
Serial.begin(9600);
pinMode(22, INPUT); // Setup for leads off detection LO +
pinMode(23, INPUT); // Setup for leads off detection LO -
// pinMode(34, INPUT);
pinMode(4, OUTPUT); 
}
 
void loop() {
 
if((digitalRead(22) == 1)||(digitalRead(23) == 1)){
Serial.println('!');
}
else{
// send the value of analog input 0:
Serial.println(analogRead(4));
}
//Wait for a bit to keep serial data from saturating
delay(60);
}
