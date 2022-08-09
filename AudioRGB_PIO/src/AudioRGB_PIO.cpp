#ifndef F_CPU
  #define F_CPU 16000000UL
#endif

#include <Arduino.h>
#include <util/delay.h>
#include <stdlib.h>

#include "functions.h"
#include "config.h"

unsigned long int ticks = 0;

void setup()
{
  // set pin modes
  pinMode(LED_L_R, OUTPUT);
  pinMode(LED_L_G, OUTPUT);
  pinMode(LED_L_B, OUTPUT);

  pinMode(LED_R_R, OUTPUT);
  pinMode(LED_R_G, OUTPUT);
  pinMode(LED_R_B, OUTPUT);

  pinMode(TCH_1, INPUT_PULLUP);
  pinMode(TCH_2, INPUT_PULLUP);
  pinMode(TCH_3, INPUT_PULLUP);
  pinMode(TCH_4, INPUT_PULLUP);

  pinMode(AUX_L, INPUT);
  pinMode(AUX_R, INPUT);

  pinMode(RNG_1, INPUT);
  pinMode(RNG_2, INPUT);
  
  // start serial
  Serial.begin(9600);
}

// main, not a loop
void loop()
{
  // left channel
  int *bufArrL = (int *)malloc(BUFFER_SIZE_AUX * sizeof(int));
  emptyArray(bufArrL, BUFFER_SIZE_AUX);
  size_t bufIndL = 0;
  int aux_l, aux_l_filter;
  // right channel
  int *bufArrR = (int *)malloc(BUFFER_SIZE_AUX * sizeof(int));
  emptyArray(bufArrR, BUFFER_SIZE_AUX);
  size_t bufIndR = 0;
  int aux_r, aux_r_filter;

  // rgb led left
  int *rgbArrL = (int *)malloc(ARRAY_SIZE_RGB * sizeof(int));
  emptyArray(rgbArrL, ARRAY_SIZE_RGB);
  int colSelL = 0, colValL = COLOR_HALF;
  int colSelPrevL = 0, colValPrevL = COLOR_HALF;
  // rgb led right
  int *rgbArrR = (int *)malloc(ARRAY_SIZE_RGB * sizeof(int));
  emptyArray(rgbArrR, ARRAY_SIZE_RGB);
  int colSelR = 0, colValR = COLOR_HALF;
  int colSelPrevR = 0, colValPrevR = COLOR_HALF;
  
  // touch sensor
  int *touchArr = (int *)malloc(ARRAY_SIZE_TCH * sizeof(int));

  // plot array
  int pltLen = 7;
  int *pltArr = (int *)malloc(pltLen * sizeof(int));
  emptyArray(pltArr, pltLen);

  while(1)
  {
    // analog read aux
    aux_l = analogRead(AUX_L);
    aux_r = analogRead(AUX_R);
    // write circular buffer
    bufferAppend(aux_l, bufArrL, &bufIndL);
    bufferAppend(aux_r, bufArrR, &bufIndR);
    // apply filter
    aux_l_filter = bufferFilter(bufArrL);
    aux_r_filter = bufferFilter(bufArrR);

    // digital read touch
    touchArr[0] = digitalRead(TCH_1);
    touchArr[1] = digitalRead(TCH_2);
    touchArr[2] = digitalRead(TCH_3);
    touchArr[3] = digitalRead(TCH_4);

    // color generator for left side
    // rgbArrL[0] = generator(aux_l_filter);
    // rgbArrL[1] = generator(aux_l_filter);
    // rgbArrL[2] = generator(aux_l_filter);
    // color generator for right side
    rgbArrR[0] = generator(aux_r_filter);
    rgbArrR[1] = generator(aux_r_filter);
    rgbArrR[2] = generator(aux_r_filter);

    // modify left color
    if(ticks % COLOR_L_CYCLE == 0)
    {
      // save previous color
      colSelPrevL = colSelL;
      colValPrevL = colValL;
      // get next color
      colSelL = noiseLimit(RNG_1, ARRAY_SIZE_RGB);
      colValL = rgbArrL[colSelL];
    }
    // fade in previous color
    colValPrevL += COLOR_L_FADE;
    rgbArrL[colSelPrevL] = min(colValPrevL, rgbArrL[colSelPrevL]);
    // fade out next color, if unequal to the previous color
    if(colSelL != colSelPrevL)
    {
      colValL -= COLOR_L_FADE;
      rgbArrL[colSelL] = colValL;
    }

    // modify right color
    if(ticks % COLOR_R_CYCLE == 0)
    {
      // save previous color
      colSelPrevR = colSelR;
      colValPrevR = colValR;
      // get next color
      colSelR = noiseLimit(RNG_2, ARRAY_SIZE_RGB);
      colValR = rgbArrR[colSelR];
    }
    // fade in previous color
    colValPrevR += COLOR_R_FADE;
    rgbArrR[colSelPrevR] = min(colValPrevR, rgbArrR[colSelPrevR]);
    // fade out next color, if unequal to the previous color
    if(colSelR != colSelPrevR)
    {
      colValR -= COLOR_R_FADE;
      rgbArrR[colSelR] = colValR;
    }

    // select side
    switch(touchArr[0])
    {
      // left side
      case 0:
        // select color
        if(touchArr[1]) rgbArrL[0] = 255;
        if(touchArr[2]) rgbArrL[1] = 255;
        if(touchArr[3]) rgbArrL[2] = 255;
        break;
      // right side
      case 1:
        // select color
        if(touchArr[1]) rgbArrR[0] = 255;
        if(touchArr[2]) rgbArrR[1] = 255;
        if(touchArr[3]) rgbArrR[2] = 255;
        break;
    }
    
    // set rgb of leds
    // writeRGB(LED_L, rgbArrL);
    writeRGB(LED_R, rgbArrR);

    // plot
    pltArr[0] = aux_l;                // blue
    pltArr[1] = aux_l_filter;         // red
    pltArr[3] = rgbArrR[0];           // green
    pltArr[4] = saturate(rgbArrR[0]); // yellow
    plot(pltArr, pltLen);

    // update timers
    ticks++;
    _delay_ms(DELAY);
  }
}
