/*
  Thermistor is 10k NTC B57861S103F40
  Digikey Part No. 495-2142-ND
*/

#include <math.h>

// Constants
const int sensorT1 = A0;
const int sensorT2 = A1;
const int sensorT3 = A2;
const int loadR = 1000;
const float Vref = 5.0;
const byte _flag = 0x7E; // Request Flag

// Steinhart-Hart Constants
const float A = 0.001125321; //Steinhart Const A
const float B = 0.000234857; //Steinhart Const B
const float C = 8.61058e-08; //Steinhart Const C

void setup() {
  Serial.begin(9600);
  pinMode(sensorT1, INPUT);
  pinMode(sensorT2, INPUT);
  pinMode(sensorT3, INPUT);
}

void loop() {
  while(Serial.available()) {
    volatile byte buffer;
    buffer = Serial.read();
    if(buffer == _flag) {
      Serial.print(getTemp(sensorT1), DEC);
      Serial.print(",");
      Serial.print(getTemp(sensorT2), DEC);
      Serial.print(",");
      Serial.print(getTemp(sensorT3), DEC);
      Serial.print("\n");
    }
  }
  delay(10);
}

float getTemp(int inputPin) {
  volatile float R;
  volatile float Vt;
  volatile float Temp;
  Vt = Vref*analogRead(inputPin)/1024;
  R = loadR*(Vref - Vt)/Vt;
  Temp = log(R);
  Temp = (1 / (A + (B * Temp) + (C * (Temp * Temp * Temp)))) - 273.15;
  Temp = (Temp * 9 / 5) + 32.0;
  return Temp;
}
