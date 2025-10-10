// C++ code
//
int light_pin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(light_pin,INPUT);
  pinMode(7,OUTPUT);
}

void loop() {
  int value = analogRead(light_pin);
  Serial.println(value);
  if(value < 500){
  	digitalWrite(7,HIGH);
  }
  else{
    digitalWrite(7,LOW);
  }
  delay(1000);
}