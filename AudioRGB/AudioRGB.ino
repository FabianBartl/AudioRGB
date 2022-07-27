#include <Arduino.h>
#include <util/delay.h>

#define LED_R 11
#define LED_G 10
#define LED_B 9
#define MIC_D 12
#define MIC_A A0
#define DELAY 1
#define PRESCALE 64

volatile unsigned long int time=0, timer=0;
volatile int mic_a=0;
int r=0, g=0, b=0;

void setup()
{
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(MIC_D, INPUT);
  pinMode(MIC_A, INPUT);
}

void writeRGB(float r, float g, float b)
{
  analogWrite(LED_R, fit(r));
  analogWrite(LED_G, fit(g));
  analogWrite(LED_B, fit(b));
}

int fit(float v) { return v<0 ? 0 : (v>255 ? 255 : (int)v); }

int genR(int v) { return 127.5 * sin(0.01 * (float)v * (float)time) + 127.5; }
int genG(int v) { return time; }
int genB(int v) { return 0; }

void loop()
{
  Serial.begin(9600);
  while (1)
  {
    mic_a = analogRead(MIC_A);
    r = genR(mic_a);
    g = genG(mic_a);
    b = genB(mic_a);
    writeRGB(r, g, b);
    Serial.println(time);

    timer++;
    time = timer / PRESCALE;
    _delay_ms(DELAY);
    }
}
