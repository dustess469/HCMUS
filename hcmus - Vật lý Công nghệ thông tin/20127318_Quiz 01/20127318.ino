// C++ code
//
void setup()
{
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  digitalWrite(4, HIGH);
  delay(6000); // Wait for 6000 millisecond(s) 
  digitalWrite(4, LOW);
  
  digitalWrite(3, HIGH);
  delay(10000); // Wait for 10000 millisecond(s)
  digitalWrite(3, LOW);
  
  digitalWrite(2, HIGH);
  delay(7000); // Wait for 7000 millisecond(s)
  digitalWrite(2, LOW);
}