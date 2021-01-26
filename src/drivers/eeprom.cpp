#include "drivers/eeprom.h"

EEPROMClass::EEPROMClass() = default;

void EEPROMClass::Init() {
  /* Unlock the Flash Program Erase controller */
  HAL_FLASH_Unlock();
  EE_Init(EE_FORCED_ERASE);
}

/* Definitely call this after you're done eeproming! */
void EEPROMClass::DeInit() { HAL_FLASH_Lock(); }

void EEPROMClass::WriteFloat(uint16_t address, float data) {
  // evil floating point bit level hacking
  if ((EE_WriteVariable32bits(1, *(uint32_t*)&data) &
       EE_STATUSMASK_CLEANUP) == EE_STATUSMASK_CLEANUP) {
    EE_CleanUp();
  }
}

// Only read and write sequentially. That's the deal here
float EEPROMClass::ReadFloat(uint16_t address) {
  EE_ReadVariable32bits(1, &dataStore32Bit_);

  // evil floating point bit level hacking reversed
  return *(float*)&dataStore32Bit_;
}

EEPROMClass EEPROM;
