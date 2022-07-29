#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

  // define pins
  #define LED_R 11
  #define LED_G 10
  #define LED_B 9

  #define TCH_1 6
  #define TCH_2 5
  #define TCH_3 4
  #define TCH_4 3

  #define AUX_L A0
  #define AUX_R A1

  #define RNG A2

  // define constants
  #define BUFFER_SIZE_AUX 3
  #define BUFFER_SIZE_RNG 5

  #define VOLUME_MIN 180
  #define VOLUME_MAX 580
  #define FREQUENCY 0.5f

  #define COLOR_MIN 0
  #define COLOR_MAX 255
  #define COLOR_HALF 127.5f

  #define DELAY 10
  #define PRESCALE 16

  #define ADC_MAX 1023 //10 bit

#endif