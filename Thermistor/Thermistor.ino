/*
  Thermistor is 10k NTC B57861S103F40
  Digikey Part No. 495-2142-ND
*/

#include <math.h>

// Constants
const int sensorPin = A0;
const int loadR = 1200;
const int Vref = 5.0;
const byte _flag = 0x7E; // Request Flag

// Steinhart-Hart Constants
const float A = 0.001125321; //Steinhart Const A
const float B = 0.000234857; //Steinhart Const B
const float C = 8.61058e-08; //Steinhart Const C

// Calculation Variables
volatile float R;
volatile float Temp;
volatile float Vt;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

volatile byte *_Temp = (byte *) &Temp;
void loop() {
  while(Serial.available()) {
    volatile byte buffer;
    buffer = Serial.read();
    if(buffer == _flag) {
      Serial.write(_Temp, 4);
    }
  }
  delay(100);
}

void getTemp() {
  Vt = Vref*analogRead(sensorPin)/1024;
  R = loadR*(Vref - Vt)/Vt;
  Temp = log(R);
  Temp = (1 / (A + (B * Temp) + (C * (Temp * Temp * Temp)))) - 273.15;
  Temp = (Temp * 9 / 5) + 32.0;
}
