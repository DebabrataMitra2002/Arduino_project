int pir1=2;
int pir2=3;
int pir3=4;
int pir4=5;
int pir1state=LOW;
int pir2state=LOW;
int pir3state=LOW;
int pir4state=LOW;
// int relay1=8;
// int relay2=9;
// int relay3=10;
// int relay4=11;
int val1=0;
int val2=0;
int val3=0;
int val4=0;
void setup()
{
  // pinMode(relay1, OUTPUT);
  // pinMode(relay2, OUTPUT);
  // pinMode(relay3, OUTPUT);
  // pinMode(relay4, OUTPUT);
  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  pinMode(pir3, INPUT);
  pinMode(pir4, INPUT);
  Serial.begin(9600);
}

void loop()
{
  val1 = digitalRead(pir1);  // read input value
  val2 = digitalRead(pir2);  // read input value
  val3 = digitalRead(pir3);  // read input value
  val4 = digitalRead(pir4);  // read input value
  // Serial.println("ok");
  if (val1 == HIGH)	// check if the input is HIGH
  {            
    // digitalWrite(relay1, HIGH);  // turn relay1 ON
	
    if (pir1state == LOW) 
	{
      Serial.println("Motion 1 detected!");	// print on output change
      pir1state = HIGH;
    }
  //   delay(1);
  } 
  else 
  {
    // digitalWrite(relay1, LOW); // turn relay1 OFF
	  if (pir1state == HIGH)
  	{
      Serial.println("Motion 1 ended!");	// print on output change
      pir1state = LOW;} delay(1);
      }
  


  if (val2 == HIGH)	// check if the input is HIGH
  {            
  //   digitalWrite(relay2, HIGH);  // turn relay2 ON
	
    if (pir2state == LOW) 
	{
      Serial.println("Motion 2 detected!");	// print on output change
      pir2state = HIGH;
    }
  } 
  else 
  {
  //   digitalWrite(relay2, LOW); // turn relay2 OFF
	
    if (pir2state == HIGH)
	{
      Serial.println("Motion 2 ended!");	// print on output change
      pir2state = LOW;}
      }
  
  if (val3 == HIGH)	// check if the input is HIGH
   {            
  //   digitalWrite(relay3, HIGH);  // turn relay3 ON
	
    if (pir3state == LOW) 
	{
      Serial.println("Motion 3 detected!");	// print on output change
      pir3state = HIGH;
    }
  } 
  else 
  {
  //   digitalWrite(relay3, LOW); // turn relay3 OFF
	
    if (pir3state == HIGH)
	{
      Serial.println("Motion 3 ended!");	// print on output change
      pir3state = LOW;}
      }
  
  if (val4 == HIGH)	// check if the input is HIGH
  {            
  //   digitalWrite(relay4, HIGH);  // turn relay4 ON
	
    if (pir4state == LOW) 
	{
      Serial.println("Motion 4 detected!");	// print on output change
      pir4state = HIGH;
    }
  } 
  else 
  {
  //   digitalWrite(relay4, LOW); // turn relay4 OFF
	
    if (pir4state == HIGH)
	{
      Serial.println("Motion 4 ended!");	// print on output change
  
  }
  // delay(1000);
  }
}