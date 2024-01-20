
int IN_1=4;
int IN_2=5;
int c=100;

void setup() {
  // put your setup code here, to run once:
pinMode(IN_1,OUTPUT);
pinMode(IN_2,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(IN_1,c);
delay(2000);
analogWrite(IN_1,0);
delay(20);
analogWrite(IN_2,c);
delay(2000);
analogWrite(IN_2,0);
delay(20);

}
