
#include <Arduino.h>
#include <util/delay.h>

#include "config.h"

void init()
{
  pinMode(LED_B, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);

  pinMode(MIC_D, INPUT);
  pinMode(MIC_A, INPUT);

  Serial.begin(9600);
}

int main()
{
  init();
  int mic_d = 0;

  while (1)
  {
    mic_d = digitalRead(MIC_D);
    
    Serial.println(mic_d);
    Serial.flush();

    _delay_ms(100);
  }
  
  return 0;
}

