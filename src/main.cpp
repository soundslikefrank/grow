// Copyright 2020 <Christian Maniewski>

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#define DAC_PIN 6
#define FADER_PIN 7
#define FADER_SPI_CLOCK_MAX 8000000
#define DAC_SPI_CLOCK_MAX 2000000
#define MCP23017_ADDRESS 0x20

SPISettings FADER_READER(FADER_SPI_CLOCK_MAX, MSBFIRST, SPI_MODE0);
SPISettings DAC_SETTER(DAC_SPI_CLOCK_MAX, MSBFIRST, SPI_MODE0);

// setVoltage -- Set DAC voltage output
// dacpin: chip select pin for DAC.  Note and velocity on DAC1, pitch bend and
// CC on DAC2 channel: 0 (A) or 1 (B).  Note and pitch bend on 0, velocity and
// CC on 2. gain: 0 = 1X, 1 = 2X. mV: integer 0 to 4095.  If gain is 1X, mV is
// in units of half mV (i.e., 0 to 2048 mV). If gain is 2X, mV is in units of mV
void setVoltage(uint8_t pin, bool channel, bool gain, unsigned int mV) {
  unsigned int command = channel ? 0x9000 : 0x1000;

  // 1 1 0 1 0 0 0 0 0 0 0 0 0 1 1 1  /// 2000 (dec) little endian
  // 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1     - 0x0FFF
  command |= gain ? 0x0000 : 0x2000;
  command |= (mV & 0x0FFF);  // Limit to 12 bit (max 4096)

  // 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0     - 0x1000
  // 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0     - 0x2000
  // | -----------------------------
  // 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0
  //
  // 0 0 0 0 0 1 1 1 1 1 0 1 0 0 0 0     - 2000 (mV)
  // 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1     - 0x0FFF
  // & -----------------------------
  // 0 0 0 0 0 1 1 1 1 1 0 1 0 0 0 0
  // 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0     - 0x9000 | 0x2000
  // | -----------------------------
  // 0 0 0 1 0 1 1 1 1 1 0 1 0 0 0 0     - command
  // 0 0 0 0 0 0 0 0 0 0 0 1 0 1 1 1     - command >> 8

  // 0 0 0 1 0 1 1 1 1 1 0 1 0 0 0 0     - command
  // 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1     - 0xff
  // & -----------------------------
  // 0 0 0 0 0 0 0 0 1 1 0 1 0 0 0 0     - command & 0xff

  SPI.beginTransaction(DAC_SETTER);
  digitalWrite(pin, LOW);
  // first part of command, zero padded with a byte
  SPI.transfer(command >> 8);
  // last part of command, zero padded with a byte
  SPI.transfer(command & 0xFF);
  digitalWrite(pin, HIGH);
  SPI.endTransaction();
}

// See https://rheingoldheavy.com/mcp3008-tutorial-02-sampling-dc-voltage/
int readFader(byte channel) {
  byte dataMSB = 0;
  byte dataLSB = 0;
  byte JUNK = 0x00;
  SPI.beginTransaction(FADER_READER);
  digitalWrite(FADER_PIN, LOW);
  SPI.transfer(0x01);
  // Get the first byte of data, masked to the last two bits (0x03)
  // 0x08 for channel 0
  dataMSB = SPI.transfer(0x09 << 4) & 0x03;
  // Send a bunch of junk (MCP  don't care but we want data back)
  dataLSB = SPI.transfer(JUNK);
  digitalWrite(FADER_PIN, HIGH);
  SPI.endTransaction();
  // return two bytes of data [dataMSB, dataLSB]
  return dataMSB << 8 | dataLSB;
}

void setLedRegister(uint8_t registerValue) {
  Wire.beginTransmission(MCP23017_ADDRESS);
  Wire.write((uint8_t)0x13);
  Wire.write((uint8_t)registerValue);
  Wire.endTransmission();
}

int val = 0;

void setup() {
  // Set up SPI stuff
  SPI.begin();
  // DAC setup
  pinMode(DAC_PIN, OUTPUT);
  digitalWrite(DAC_PIN, HIGH);
  // Fader setup
  pinMode(FADER_PIN, OUTPUT);
  digitalWrite(FADER_PIN, LOW);  // cycle the MCP3008 as per datasheet
  digitalWrite(FADER_PIN, HIGH);
  // LED setup
  Wire.beginTransmission(MCP23017_ADDRESS);
  // Set IODIRB register (0x01) to all zeros (output)
  Wire.write((uint8_t)0x01);
  Wire.write((uint8_t)0x00);
  Wire.endTransmission();
  // Debug
  Serial.begin(9600);

  setLedRegister(B11111111);
}

int i = 8;

void loop() {
  val = readFader(FADER_PIN);  // read the input pin
  Serial.println(val);
  setVoltage(DAC_PIN, 0, 1, 2000);
  delay(2000);
}
