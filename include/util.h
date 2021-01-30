// Copyright 2020 Christian Maniewski <code@chmanie.com>

#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>

#define CONSTRAIN(var, min, max) \
  if (var < min) {               \
    var = min;                   \
  } else if (var > max) {        \
    var = max;                   \
  }

template <class T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi) {
  return (v < lo) ? lo : (hi < v) ? hi : v;
}

uint32_t joinBits(uint16_t a, uint16_t b);

uint64_t ror(uint64_t num, uint8_t rotation, uint8_t size);

uint64_t rol(uint64_t num, uint8_t rotation, uint8_t size);

void linReg(uint8_t n, const double* x, const double* y, double* slope,
            double* intercept);

void quadReg(uint8_t n, const double* x, const double* y, double* a, double* b,
             double* c);

inline uint16_t clampU16(int32_t x) {
  return (x < 0) ? 0 : (UINT16_MAX < x) ? UINT16_MAX : x;
}

#endif  // UTIL_H_
