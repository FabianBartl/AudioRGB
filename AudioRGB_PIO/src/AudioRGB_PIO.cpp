#ifndef F_CPU
  #define F_CPU 16000000UL
#endif

#include <Arduino.h>
#include <util/delay.h>
#include <stdlib.h>

#include "functions.h"
#include "config.h"

unsigned long int ticks = 0;

// sets rgb of led
void writeRGB(int *rgb)
{
  analogWrite(LED_R, saturate(rgb[0]));
  analogWrite(LED_G, saturate(rgb[1]));
  analogWrite(LED_B, saturate(rgb[2]));
}

// function generator
float generator(float val) { return transform(val, VOLUME_MIN, VOLUME_MAX, COLOR_MIN, COLOR_MAX); }

void setup()
{
  // set pin modes
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  pinMode(TCH_1, INPUT_PULLUP);
  pinMode(TCH_2, INPUT_PULLUP);
  pinMode(TCH_3, INPUT_PULLUP);
  pinMode(TCH_4, INPUT_PULLUP);

  pinMode(AUX_L, INPUT_PULLUP);
  pinMode(AUX_R, INPUT_PULLUP);

  pinMode(RNG, INPUT);
  
  // start serial
  Serial.begin(9600);
}

// main, not a loop
void loop()
{
  // left channel
  int *bufArrL = (int *)malloc(BUFFER_SIZE_AUX * sizeof(int));
  size_t bufIndL = 0;
  int aux_l, aux_l_filter;

  // right channel
  int *bufArrR = (int *)malloc(BUFFER_SIZE_AUX * sizeof(int));
  size_t bufIndR = 0;
  int aux_r, aux_r_filter;

  // rgb led
  int *rgbArr = (int *)malloc(3 * sizeof(int));
  int colSel = 0, colVal = COLOR_HALF;
  int colSelPrev = 0, colValPrev = COLOR_HALF;
  // touch sensor
  int *touchArr = (int *)malloc(4 * sizeof(int));

  // plot array
  int pltLen = 5;
  int *pltArr = (int *)malloc(pltLen * sizeof(int));

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

    // color generator
    rgbArr[0] = generator(aux_l_filter);
    rgbArr[1] = generator(aux_l_filter);
    rgbArr[2] = generator(aux_l_filter);

    // modify color
    if(ticks % COLOR_CYCLE == 0)
    {
      // save previous color
      colSelPrev = colSel;
      colValPrev = colVal;
      // get next color
      colSel = noise(3);
      colVal = rgbArr[colSel];
    }
    // fade in previous color
    colValPrev += COLOR_FADE;
    rgbArr[colSelPrev] = min(colValPrev, rgbArr[colSelPrev]);
    // fade out next color, if unequal to the previous color
    if(colSel != colSelPrev)
    {
      colVal -= COLOR_FADE;
      rgbArr[colSel] = colVal;
    }

    // if( touchArr[0]) rgbArr[0] = 0;
    // if( touchArr[1]) rgbArr[1] = 0;
    // if( touchArr[2]) rgbArr[2] = 0;

    // set rgb of led
    writeRGB(rgbArr);

    // plot
    pltArr[3] = aux_l;                // yellow
    pltArr[4] = aux_l_filter;         // purple
    pltArr[1] = saturate(rgbArr[0]);  // red
    pltArr[2] = saturate(rgbArr[1]);  // green
    pltArr[0] = saturate(rgbArr[2]);  // blue
    plot(pltArr, pltLen);

    // update timers
    ticks++;
    _delay_ms(DELAY);
  }
}
