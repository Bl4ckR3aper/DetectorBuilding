#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);



void setup()
{
  Wire.begin(); 
  lcd.begin(16, 2);                          // put your LCD parameters here
  lcd.print("Voltage: ");
  lcd.setCursor(0,1);
  lcd.print("PPM: ");
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
}


void loop()
{
  Wire.requestFrom(4,8);
  byte MasterReceive = Wire.read();
  Wire.beginTransmission(4);
  Wire.endTransmission();   
  long ppm = (pow(10700000000000, (-18.07*MasterReceive)) + 164.9);
  float Voltage = MasterReceive;
  float v = Voltage/100;
  if (Voltage > 243){
    v = 5.0;
  }
  lcd.print("Voltage: ");
  lcd.setCursor(0,1);
  lcd.print("PPM: ");
  lcd.setCursor(9,0);
  lcd.print(v);
  lcd.setCursor(5,1);
  lcd.print(ppm);
  lcd.clear();
  lcd.print("Voltage: ");
  lcd.setCursor(0,1);
  lcd.print("PPM: ");
  lcd.setCursor(9,0);
  lcd.print(v);
  lcd.setCursor(5,1);
  lcd.print(ppm);

  
  
  delay(400);
  
  }
