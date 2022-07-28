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
  *ind = (*ind+1 > BUFFER_SIZE-1) ? 0 : *ind+1;
  arr[*ind] = val;
}

// apply a filter to the buffer array
int bufferFilter(int *arr)
{
  int sum = 0;
  for(size_t i=0; i < BUFFER_SIZE; i++) { sum += arr[i]; }
  return sum / BUFFER_SIZE;
}

// --------------------------------------
// saturation / mapping of (color) values
// --------------------------------------

int saturate(int val) { return saturate(val, COLOR_MIN, COLOR_MAX); }
int saturate(int val, int lowerLim, int upperLim) { return (val < lowerLim) ? lowerLim : ((val > upperLim) ? upperLim : val); }

int map(int val, int inMin, int inMax, int outMin, int outMax)
{ return (val - inMin) * (outMax - outMin) / (inMax - inMin) + outMin; }

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
