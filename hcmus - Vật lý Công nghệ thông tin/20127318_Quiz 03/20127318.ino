// C++ code
//
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
  lcd_1.begin(16, 2);
  
  lcd_1.print("Degree(C):");
  pinMode(A0, INPUT);
  
}

void loop()
{
  float value = analogRead(A0);
  float celsius = (value * 5 / 1023) / 0.01 - 50;
  lcd_1.setCursor(0, 1);
  lcd_1.print(celsius);
}