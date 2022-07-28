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

  // define constants
  #define BUFFER_SIZE 5

  #define SCALE 1
  #define SHIFT 380.0 / 1.5
  #define FREQUENCY 0.5f

  #define COLOR_MIN 0
  #define COLOR_MAX 255
  #define COLOR_HALF 127.5f

  #define DELAY 1
  #define PRESCALE 16

  #define TCH1 1
  #define TCH2 2
  #define TCH3 3
  #define TCH4 4

#endif