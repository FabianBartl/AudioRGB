#ifndef F_CPU
  #define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <Arduino.h>
#include <util/delay.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"
#include "config.h"

// define globals
unsigned long int time, timer = 0;
int mic_a;
int r, g, b, rgb;

// set pin modes
void setup()
{
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(MIC_A, INPUT);
}


// sets rgb of led
void writeRGB(float r, float g, float b)
{
  analogWrite(LED_R, fit(r));
  analogWrite(LED_G, fit(g));
  analogWrite(LED_B, fit(b));
}

// helper function for saturation of color values
int fit(float v) { return v<0 ? 0 : (v>255 ? 255 : (int)v); }

// function generator
float generator(float x, float f, float s)
{
  return (255.0 / 2.0) * sin(f * (x - SHIFT + time + s)) + (255.0 / 2.0);
}

// main
void loop()
{
  // left channel
  int *bufArrL = (int *)malloc(BUFFER_SIZE * sizeof(int));
  size_t bufIndL = 0;

  Serial.begin(9600);
  while(1)
  {
    mic_a = analogRead(MIC_A);
    
    r = generator(mic_a, 0.5, 0 * (2 * PI) / 0.5);
    g = generator(mic_a, 0.5, 1 * (2 * PI) / 0.5);
    b = generator(mic_a, 0.5, 2 * (2 * PI) / 0.5);
    rgb=r+g+b;
    writeRGB(r, g, b);
    
    bufferAppend(rgb, bufArrL, &bufIndL);
    Serial.println(bufferFilter(bufArrL));

    // update timer
    timer++;
    time = timer / PRESCALE;
    _delay_ms(DELAY);
  }
}
