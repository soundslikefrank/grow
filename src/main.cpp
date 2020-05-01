// Copyright 2020 <Christian Maniewski>

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#define arrayLength(a) (sizeof(a) / sizeof(*a))

#define BUTTON_PIN 2
#define TRIGGER_PIN 3
#define DAC_PIN 6
#define FADER_PIN 7
#define FADER_SPI_CLOCK_MAX 8000000
#define DAC_SPI_CLOCK_MAX 2000000
#define MCP23017_ADDRESS 0x20

// Our DAC voltage (4096mA max) gets multiplied by this value to output a proper
// V/Oct voltage
#define DAC_VOLTAGE_MULTIPLIER 1.77

#define NoteA 0
#define NoteA_ 1
#define NoteB 2
#define NoteC 3
#define NoteC_ 4
#define NoteD 5
#define NoteD_ 6
#define NoteE 7
#define NoteF 8
#define NoteF_ 9
#define NoteG 10
#define NoteG_ 11

#define MAJOR 0
#define MINOR 1

// Any number is fine, but difference can't be more than 256
#define BPM_LOWER 44
#define BPM_UPPER 300

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
  dataMSB = SPI.transfer((0x08 + channel) << 4) & 0x03;
  // Send a bunch of junk (MCP  don't care but we want data back)
  dataLSB = SPI.transfer(JUNK);
  digitalWrite(FADER_PIN, HIGH);
  SPI.endTransaction();
  // return two bytes of data [dataMSB, dataLSB]
  return dataMSB << 8 | dataLSB;
}

uint8_t flipByte(uint8_t byte) {
  // https://gcc.gnu.org/onlinedocs/gcc/AVR-Built-in-Functions.html#AVR-Built-in-Functions
  return __builtin_avr_insert_bits(0x01234567, byte, 0);
}

void setLedRegister(uint8_t registerValue) {
  Wire.beginTransmission(MCP23017_ADDRESS);
  Wire.write((uint8_t)0x13);
  // Bytes in register are in reversed order to GPIO pin numbers
  Wire.write(flipByte(registerValue));
  Wire.endTransmission();
}

class Quantizer {
 private:
  bool majorScale[7] = {1, 1, 0, 1, 1, 1, 0};
  bool minorScale[7] = {1, 0, 1, 1, 0, 1, 1};
  uint8_t currentTonic = NoteC;
  bool currentKey = MAJOR;
  uint8_t currentOctave = 0;

 public:
  uint8_t notes[8] = {NoteA};
  uint8_t octaves[8] = {0};
  void setTonic(uint8_t tonic) { currentTonic = tonic; }
  void setKey(bool key) { currentKey = key; }
  void setOctave(uint8_t octave) { currentOctave = octave; }
  void refresh() {
    // Pick the right scale array
    bool *scale = currentKey ? minorScale : majorScale;
    uint8_t note = currentTonic;
    uint8_t octave = currentOctave;
    // The first note of the scale is the one we start with
    notes[0] = note;
    octaves[0] = octave;
    for (int step = 0; step < 7; step++) {
      // Go up one semitone (because we do that in any case)
      if (++note == 12) {
        note = 0;
        octave++;
      }
      if (scale[step]) {
        // If the current step is a whole tone, bump again
        note++;
      }
      // If that got us out of the scale, start from 0
      if (note == 12) {
        note = 0;
        octave++;
      }
      notes[step + 1] = note;
      octaves[step + 1] = octave;
    }
  }
};

int getNoteVoltage(uint8_t note, uint8_t octave) {
  // return A0 as the lowest note
  if (octave < 0) return 0;
  // return C7 as the highest note
  if ((octave == 7 && note > 3) || octave > 7) {
    return getNoteVoltage(NoteC, 7);
  }
  // Calculate V/OCT value divided by the voltage multiplier
  float vValue = (float)octave + (float)note / 12.0;
  return floor(1000.0 * vValue / DAC_VOLTAGE_MULTIPLIER);
}

Quantizer quantizer;

uint8_t i = 0;
uint16_t bpm = 120;
uint32_t loopMillis = millis();
uint32_t shiftMillis = millis();
bool trigger = 0;
float tonicFaderDivisor = 1024 / 12;
float octaveFaderDivisor = 1024 / 7;
float keyFaderDivisor = 1024 / 2;
float bpmFaderDivisor = 1024 / (BPM_UPPER - BPM_LOWER);
byte previousTonicFaderPosition;
byte previousOctaveFaderPosition;
byte previousKeyFaderPosition;
byte previousBpmFaderPosition;

void setup() {
  // Debug
  Serial.begin(9600);
  // Set up button
  pinMode(BUTTON_PIN, INPUT);
  // Set up trigger
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  // Set up SPI stuff
  SPI.begin();
  // Set up I2C bus
  Wire.begin();
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
  // Set initial quantizer tonic, key and octave
  quantizer.refresh();
}

bool previousButtonPressed = 0;

void loop() {
  // Debounce 200ms
  if (digitalRead(BUTTON_PIN) && millis() - shiftMillis > 200) {
    byte tonicFaderPosition = floor(readFader(0) / tonicFaderDivisor);
    byte octaveFaderPosition = floor(readFader(1) / octaveFaderDivisor);
    byte keyFaderPosition = floor(readFader(2) / keyFaderDivisor);
    byte bpmFaderPosition = floor(readFader(3) / bpmFaderDivisor);
    if (!previousButtonPressed) {
      // Set all previous values to the current values to prevent immediate
      // change
      previousTonicFaderPosition = tonicFaderPosition;
      previousOctaveFaderPosition = octaveFaderPosition;
      previousKeyFaderPosition = keyFaderPosition;
      previousBpmFaderPosition = bpmFaderPosition;
      previousButtonPressed = 1;
    }
    shiftMillis = millis();
    if (previousTonicFaderPosition != tonicFaderPosition) {
      Serial.println("Setting tonic");
      quantizer.setTonic(tonicFaderPosition);
      previousTonicFaderPosition = tonicFaderPosition;
    }
    if (previousOctaveFaderPosition != octaveFaderPosition) {
      Serial.println("Setting octave");
      quantizer.setOctave(octaveFaderPosition);
      previousOctaveFaderPosition = octaveFaderPosition;
    }
    if (keyFaderPosition != previousKeyFaderPosition) {
      Serial.println("Setting key");
      quantizer.setKey(keyFaderPosition);
      previousKeyFaderPosition = keyFaderPosition;
    }
    if (bpmFaderPosition != previousBpmFaderPosition) {
      Serial.println("Setting bpm");
      bpm = bpmFaderPosition;
      previousBpmFaderPosition = bpmFaderPosition;
    }
    quantizer.refresh();
  }
  if (!digitalRead(BUTTON_PIN)) {
    previousButtonPressed = 0;
  }
  if (millis() - loopMillis > floor((60000.0 / (float)bpm))) {
    loopMillis = millis();
    trigger = 1;
    digitalWrite(TRIGGER_PIN, HIGH);
    float octaveDivisor = 1024 / arrayLength(quantizer.notes);
    byte position = floor(readFader(i) / octaveDivisor);
    float voltage =
        getNoteVoltage(quantizer.notes[position], quantizer.octaves[position]);
    setVoltage(DAC_PIN, 0, 1, voltage);
    setLedRegister(B10000000 >> i);
    if (i < 7) {
      i++;
    } else {
      i = 0;
    }
  }
  // 20ms after loopMillis was reset, set trigger to low again
  if (millis() > loopMillis + 20 && trigger) {
    digitalWrite(TRIGGER_PIN, LOW);
    trigger = 0;
  }
}
