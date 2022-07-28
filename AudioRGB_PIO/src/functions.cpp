#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>

#include "functions.h"
#include "config.h"

// -------------
// pin functions
// -------------

// helper pin -> PORT
int _pin2port(int pin)
{
  // find out the appropriate PORT
  switch(pin)
  {
    case B0: return PB0;
    case B1: return PB1;
    case B2: return PB2;
    case B3: return PB3;
    case B4: return PB4;
    case B5: return PB5;
    case C0: return PC0;
    case C1: return PC1;
    case C2: return PC2;
    case C3: return PC3;
    case C4: return PC4;
    case C5: return PC5;
    case D0: return PD0;
    case D1: return PD1;
    case D2: return PD2;
    case D3: return PD3;
    case D4: return PD4;
    case D5: return PD5;
    case D6: return PD6;
    case D7: return PD7;
  }
}

// helper pin -> DDR
int _pin2ddr(int pin)
{
  // find out the appropriate DDR
  switch(pin)
  {
    case B0: return DDB0;
    case B1: return DDB1;
    case B2: return DDB2;
    case B3: return DDB3;
    case B4: return DDB4;
    case B5: return DDB5;
    case C0: return DDC0;
    case C1: return DDC1;
    case C2: return DDC2;
    case C3: return DDC3;
    case C4: return DDC4;
    case C5: return DDC5;
    case D0: return DDD0;
    case D1: return DDD1;
    case D2: return DDD2;
    case D3: return DDD3;
    case D4: return DDD4;
    case D5: return DDD5;
    case D6: return DDD6;
    case D7: return DDD7;
  }
}

// set pin mode
void _pinMode(int pin, int mode)
{
  // find out the appropriate DDR-, PORT- and PIN-register
  volatile uint8_t *DDR, *PORT;
  switch(pin)
  {
    case B0:
    case B1:
    case B2:
    case B3:
    case B4:
    case B5:
      DDR = &DDRB;
      PORT = &PORTB;
      break;
    case C0:
    case C1:
    case C2:
    case C3:
    case C4:
    case C5:
      DDR = &DDRC;
      PORT = &PORTC;
      break;
    case D0:
    case D1:
    case D2:
    case D3:
    case D4:
    case D5:
    case D6:
    case D7:
      DDR = &DDRD;
      PORT = &PORTD;
      break;
  }
  // set pin mode
  switch(mode)
  {
    case _INPUT:
      *DDR &= ~(1<<pin); //input
      *PORT |= (1<<pin); //pull-up
      break;
    case _OUTPUT:
      *DDR |= (1<<pin); //output
      break;
  }
}

// read analog pin
int _analogRead(int pin)
{
  return 0;
}

// write analog pin
void _analogWrite(int pin)
{

}

// read digital pin
int _digitalRead(int pin)
{
  return 0;
}

// write digital pin
void _digitalWrite(int pin)
{

}

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
