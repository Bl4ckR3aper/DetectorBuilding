#include <math.h>
#include <Wire.h>

int inputA = A0;

int redLight= 2;
int blueLight= 3;
int greenLight= 4;

int R1 = 5;
int R2 = 6;

const float V = 3.3;


void setup()
{
 Wire.begin(4);                // join i2c bus with address #4
  pinMode(redLight, OUTPUT);
  pinMode(greenLight, OUTPUT);
  pinMode(blueLight, OUTPUT);
  pinMode(inputA, INPUT);
  Serial.begin(9600);           // start serial for output
 Wire.onRequest(requestEvent);   
 float Voltage = (analogRead(inputA) * (3.3/1023.));
       

}



void loop()
{
  
  const float R1 = 15000;
  float Voltage = (analogRead(inputA) * (5./1023.))*10;

 float V1 = Voltage - (analogRead(inputA) * (5./1023.));
 
 float I = V1/R1;
 float R2 = (Voltage - V1)/I;
 const float A = 1.12 * 0.8;
 const float l = 0.87;
 float resistivity = R2 * l/A;
 float conductivity = 1./resistivity*1000000;
 float ppm = 5;
  Serial.println("\n");
  Serial.println(analogRead(inputA));
  Serial.println(analogRead(inputA) * (5./1023.));
  Serial.println(V1);
  Serial.println(R2);
  Serial.println(conductivity);
  Serial.println(ppm);
  Serial.println(Voltage);
  //Serial.println(ppmfromvltg);
  //Serial.println(resultB * 5./ 1023);
  //Serial.println(resultB);
  //Serial.println(resultA - resultB);
  if (ppm < R1){
    digitalWrite(redLight, HIGH);
    digitalWrite(blueLight, LOW);
    digitalWrite(greenLight, LOW);
  }

   else if (ppm >= R1 && R2 < ppm){
    digitalWrite(redLight, LOW);
    digitalWrite(blueLight, HIGH);
    digitalWrite(greenLight, LOW);
  }

  else if (ppm >= R2){
    digitalWrite(greenLight, HIGH);
    digitalWrite(blueLight, LOW);
    digitalWrite(redLight, LOW);
  }
byte v = (byte)Voltage;
Serial.println(v);
Wire.write((byte)50);
delay(500);
}

void requestEvent()  
{  
  float Voltage = (analogRead(inputA) * (5./1023.))*100;
  byte SlaveSend = Voltage;   
  Wire.write(SlaveSend);        
}
