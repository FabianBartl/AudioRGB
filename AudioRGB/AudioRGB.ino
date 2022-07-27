#include <Arduino.h>
#include <util/delay.h>
#include "config.h"

// define globals
unsigned long int time=0, timer=0;
int mic_a=0;
int r=0, g=0, b=0;
int *buffer = malloc(BUFFER_SIZE * sizeof(int));

// set pin modes
void setup()
{
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(MIC_D, INPUT);
  pinMode(MIC_A, INPUT);
}

void bufferAppend(int v)
{
  
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
int generator(int x, float f) { return 127.5 * sin(f * (float)x * (float)time) + 127.5; }

// main
void loop()
{
  Serial.begin(9600);
  while (1)
  {
    
    mic_a = analogRead(MIC_A);
    r = generator(mic_a, 0.01);
    g = generator(mic_a, 0.01);
    b = generator(mic_a, 0.01);
    writeRGB(r, g, b);
    Serial.println((r+g+b)/3);

    // update timer
    timer++;
    time = timer / PRESCALE;
    _delay_ms(DELAY);
  }
}
