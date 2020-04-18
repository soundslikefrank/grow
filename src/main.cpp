// Copyright 2020 <Christian Maniewski>

#include <Arduino.h>
#include <SPI.h>

int val = 0;

#define DAC 8

// setVoltage -- Set DAC voltage output
// dacpin: chip select pin for DAC.  Note and velocity on DAC1, pitch bend and
// CC on DAC2 channel: 0 (A) or 1 (B).  Note and pitch bend on 0, velocity and
// CC on 2. gain: 0 = 1X, 1 = 2X. mV: integer 0 to 4095.  If gain is 1X, mV is
// in units of half mV (i.e., 0 to 2048 mV). If gain is 2X, mV is in units of mV
void setVoltage(int dacpin, bool channel, bool gain, unsigned int mV) {
  unsigned int command = channel ? 0x9000 : 0x1000;

  command |= gain ? 0x0000 : 0x2000;
  command |= (mV & 0x0FFF);

  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  digitalWrite(dacpin, LOW);
  SPI.transfer(command >> 8);
  SPI.transfer(command & 0xFF);
  digitalWrite(dacpin, HIGH);
  SPI.endTransaction();
}

void setup() {
  SPI.begin();
  Serial.begin(9600); //  setup serial
  pinMode(DAC, OUTPUT);
  digitalWrite(DAC, HIGH);
}

void loop() {
  val = analogRead(A0); // read the input pin
  Serial.println(val);  // debug value
  setVoltage(DAC, 0, 1, val * 4);
  delay(500);
}
