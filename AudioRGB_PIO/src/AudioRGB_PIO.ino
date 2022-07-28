#ifndef F_CPU
  #define F_CPU 16000000UL
#endif

#include <Arduino.h>
#include <util/delay.h>
#include <stdlib.h>

#include "functions.h"
#include "config.h"

unsigned long int ticks = 0, time = 0; 

// sets rgb of led
void writeRGB(int *rgb)
{
  analogWrite(LED_R, saturate(rgb[0]));
  analogWrite(LED_G, saturate(rgb[1]));
  analogWrite(LED_B, saturate(rgb[2]));
}

// function generator
float generator(float val, float frequency, float phase)
{
  return COLOR_HALF * sin(TWO_PI * frequency * (val + time) + phase) + COLOR_HALF;
  // return COLOR_HALF * sin(frequency * (val - SHIFT + TIME + phase)) + COLOR_HALF;
}

void setup()
{
  // set pin modes
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(AUX_L, INPUT_PULLUP);
  
  Serial.begin(9600);
}

// main, not a loop
void loop()
{
  // left channel
  int *bufArrL = (int *)malloc(BUFFER_SIZE * sizeof(int));
  size_t bufIndL = 0;
  int aux_l, aux_l_filter;

  // right channel
  int *bufArrR = (int *)malloc(BUFFER_SIZE * sizeof(int));
  size_t bufIndR = 0;
  int aux_r, aux_r_filter;

  // rgb led
  int *rgbArr = (int *)malloc(3 * sizeof(int));

  while(1)
  {
    // analog read
    aux_l = analogRead(AUX_L);
    aux_r = analogRead(AUX_R);
    // write circular buffer
    bufferAppend(aux_l, bufArrL, &bufIndL);
    bufferAppend(aux_r, bufArrR, &bufIndR);
    // apply filter
    aux_l_filter = bufferFilter(bufArrL);
    aux_r_filter = bufferFilter(bufArrR);
    
    // color generator
    rgbArr[0] = generator(aux_l_filter, 0.5, 0);
    rgbArr[1] = generator(aux_r_filter, 0.5, 2);
    rgbArr[2] = generator(0, 0.5, 4);
    // set rgb of led
    writeRGB(rgbArr);

    // plot color as graph
    plot(rgbArr, 3);

    // update timer
    ticks++;
    time = ticks / PRESCALE;
    _delay_ms(DELAY);
  }
}
