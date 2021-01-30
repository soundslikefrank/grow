// Copyright 2020 Christian Maniewski.

#include "util.h"
#include <math.h>

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

uint64_t rol(uint64_t num, uint8_t rotation, uint8_t size) {
  rotation %= size - 1;
  while (rotation--) {
    num = (num << 1) | (1 & (num >> (size - 1)));
  }
  return num;
}

uint64_t ror(uint64_t num, uint8_t rotation, uint8_t size) {
  rotation %= size - 1;
  while (rotation--) {
    num = (((num >> 1) & (~(1 << (size - 1)))) | ((num & 1) << (size - 1)));
  }
  return num;
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

// Calculate quadratic polynomial regression of n points
void quadReg(uint8_t n, const double* x, const double* y, double* a, double* b,
             double* c) {
  double sumX = 0;
  uint16_t sumY = 0;
  double sumX2 = 0;
  double sumX3 = 0;
  double sumX4 = 0;
  double sumYX = 0;
  double sumYX2 = 0;

  for (uint8_t i = 0; i < n; i++) {
    sumX += x[i];
    sumX2 += pow(x[i], 2);
    sumX3 += pow(x[i], 3);
    sumX4 += pow(x[i], 4);
    sumY += y[i];
    sumYX += y[i] * x[i];
    sumYX2 += y[i] * pow(x[i], 2);
  }

  double s11 = sumX2 - (pow(sumX, 2) / n);
  double s12 = sumX3 - (sumX * sumX2) / n;
  double s22 = sumX4 - (pow(sumX2, 2) / n);
  double sy1 = sumYX - (sumY * sumX) / n;
  double sy2 = sumYX2 - (sumY * sumX2) / n;
  double mX1 = sumX / n;
  double mX2 = sumX2 / n;
  double mY = (double)sumY / n;

  // y = a * x^2 + b * x + c
  *a = (sy2 * s11 - sy1 * s12) / (s22 * s11 - pow(s12, 2));
  *b = (sy1 * s22 - sy2 * s12) / (s22 * s11 - pow(s12, 2));
  *c = mY - *b * mX1 - *a * mX2;
}
