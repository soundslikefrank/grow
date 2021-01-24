// Copyright 2020 Christian Maniewski.

#include "util.h"

// Interleave bits
// @TODO Maybe we can find a more efficient way
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

// Calculate linear regression of n points
void linReg(uint8_t n, const double* x, const double* y, double* slope,
            double* intercept) {
  double sumX = 0;
  uint16_t sumY = 0;
  double sumX2 = 0;
  double sumXY = 0;

  for (uint8_t i = 0; i < n; i++) {
    sumX += x[i];
    sumY += y[i];
    sumX2 += x[i] * x[i];
    sumXY += x[i] * (double)y[i];
  }

  *slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
  *intercept = (sumY - *slope * sumX) / n;
}
