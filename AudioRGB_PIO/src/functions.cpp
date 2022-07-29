#include <Arduino.h>
#include <util/delay.h>
#include <stdlib.h>

#include "functions.h"
#include "config.h"

// -------------------------
// circular buffer functions
// -------------------------

// implements an append function for the buffer array containing the last measured elements
void bufferAppend(int val, int *arr, size_t *ind)
{
  *ind = (*ind+1 > BUFFER_SIZE_AUX-1) ? 0 : *ind+1;
  arr[*ind] = val;
}

// apply a filter to the buffer array
int bufferFilter(int *arr)
{
  int sum = 0;
  for(size_t i=0; i < BUFFER_SIZE_AUX; i++) { sum += arr[i]; }
  return sum / BUFFER_SIZE_AUX;
}

// --------------------------------------
// saturation / mapping of (color) values
// --------------------------------------

int saturate(int val) { return saturate(val, COLOR_MIN, COLOR_MAX); }
int saturate(int val, int lowerLim, int upperLim) { return (val < lowerLim) ? lowerLim : ((val > upperLim) ? upperLim : val); }

int transform(int val, int inMin, int inMax, int outMin, int outMax)
// { return (val - inMin) * (outMax - outMin) / (inMax - inMin) + outMin; }
// { return (val - inMin - outMin) * (outMax) / (inMax - inMin); }
// {
//   int deltaY = outMax - outMin;
//   int deltaX = inMax - inMin;
//   int offset = inMin - outMin;
//   return (val - offset) * (deltaY / deltaX);
// }
{
  int inHalf = inMin + (inMax - inMin) / 2;
  int outHalf = outMin + (outMax - outMin) / 2;
  return val - (inHalf - outHalf);
}

// --------------
// serial plotter
// --------------

// blue, red, green, yellow, purple
void plot(int *valArr, int lenArr)
{
  for(int i=0; i < lenArr-1; i++)
  {
    Serial.print(valArr[i]);
    Serial.print(",");
  }
  Serial.print(valArr[lenArr-1]);

  Serial.println("");
  Serial.flush();
}

// ---------------
// noise generator
// ---------------

int noise() { return analogRead(RNG); }
int noise(int mod) { return noise() % mod; }
