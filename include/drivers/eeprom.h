// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef EEPROM_H_
#define EEPROM_H_

#include <eeprom_emul.h>

class EEPROMClass {
 private:
  uint32_t dataStore32Bit_;

 public:
  EEPROMClass();
  void Init();
  void DeInit();
  void WriteFloat(uint16_t address, float data);
  float ReadFloat(uint16_t address);
};

extern EEPROMClass EEPROM;

#endif  // EEPROM_H_

