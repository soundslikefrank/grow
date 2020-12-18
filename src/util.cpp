// Copyright 2020 Christian Maniewski.

#include "util.h"

// Interleave bits
// @TODO Maybe we can find a more efficient way if that's needed
uint32_t joinBits(uint16_t a, uint16_t b) {
  uint32_t result = 0;
  for (int8_t ii = 15; ii >= 0; ii--) {
    result |= (a >> ii) & 1;
    result <<= 1;
    result |= (b >> ii) & 1;
    if (ii != 0) {
      result <<= 1;
    }
  }
  return result;
}
