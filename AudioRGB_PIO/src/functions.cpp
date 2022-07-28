#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>

#include "functions.h"
#include "config.h"

// ----------------
// buffer functions
// ----------------

// implements an append function for the buffer array containing the last measured elements
void bufferAppend(int val, int *arr, size_t *ind)
{
  *ind = *ind+1 > BUFFER_SIZE-1 ? 0 : *ind+1;
  arr[*ind] = val;
}

// apply a filter to the buffer array
int bufferFilter(int *arr)
{
  int sum = 0;
  for(size_t i=0; i < BUFFER_SIZE; i++) { sum += arr[i]; }
  return sum / BUFFER_SIZE;
}
