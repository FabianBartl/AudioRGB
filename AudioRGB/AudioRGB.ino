#include <Arduino.h>
#include <util/delay.h>
#include "config.h"

// define globals
unsigned long int time, timer = 0;
int mic_a;
int r, g, b, rgb;
int *bufferArray = malloc(BUFFER_SIZE * sizeof(int)), bufferIndex = 0;

// set pin modes
void setup()
{
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(MIC_D, INPUT);
  pinMode(MIC_A, INPUT);
}

// implements an append function for the buffer array containing the last measured elements
void bufferAppend(int v)
{
  bufferIndex = bufferIndex+1 > BUFFER_SIZE-1 ? 0 : bufferIndex+1;
  bufferArray[bufferIndex] = v;
}

// apply a filter to the last measured elements
int bufferFilter(int t)
{
  /* filter types:
   *  0 average (default)
   *  1 median (not implemented yet)
  */
  switch(t)
  {
    case 0:
      int avr=0;
      for(int i=0; i<BUFFER_SIZE; i++) { avr += bufferArray[i]; }
      return avr / BUFFER_SIZE;
    case 1:
      break;
    default:
      return bufferFilter(0);
  }
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

// color generator
int generator(int x, float f)
{
  return (255.0 / 2.0)
    * sin(f * (x-SHIFT_37) * time)
    + (255.0 / 2.0);
}

// main
void loop()
{
  Serial.begin(9600);
  while(1)
  {
    mic_a = analogRead(MIC_A);
    
    r = generator(mic_a, 0.001);
    g = 0; //generator(mic_a, 0.001);
    b = 0; //generator(mic_a, 0.001);
    rgb=r+g+b;
    writeRGB(r, g, b);
    
    bufferAppend(rgb);
    Serial.println(bufferFilter(0));

    // update timer
    timer++;
    time = timer / PRESCALE;
    _delay_ms(DELAY);
  }
}
