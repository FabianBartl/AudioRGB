#include <Arduino.h>

#define LED_R 11
#define LED_G 10
#define LED_B 9
#define MIC_D 12
#define MIC_A A0

unsigned long int time = 0;
volatile int mic_a = 0;

void init()
{
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(MIC_D, INPUT);
  pinMode(MIC_A, INPUT);
}

void writeRGB(int r, int g, int b)
{
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}

int fit(int v) { return v<0 ? 0 : (v>255 ? 255 : v); }
int fit(float v) { return fit((int)v); }

int genR(int v) { return fit(127.5 * sin(0.001 * v * time) + 127.5); }
int genG(int v) { return genR(v); }
int genB(int v) { return genR(v); }

int main()
{
  init();
  Serial.begin(9600);

  while (1)
  {
    mic_a = analogRead(MIC_A);
    Serial.println(time);
    
    writeRGB(
      genR(mic_a),
      genG(mic_a),
      genB()
    );
    
    time++;
  }

  return 0;
}
