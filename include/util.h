// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef UTIL_H_
#define UTIL_H_

#include <stm32l4xx_hal.h>

// @TODO this is weird
template <class T>
const T& constrain(const T& amt, const T& low, const T& high) {
  if (amt < low) {
    return low;
  }
  if (high < amt) {
    return high;
  }
  return amt;
}

extern uint32_t joinBits(uint16_t a, uint16_t b);

void linReg(uint8_t n, const double* x, const double* y, double* slope,
            double* intercept);

void quadReg(uint8_t n, const double* x, const double* y, double* a, double* b,
             double* c);

#endif  // UTIL_H_
