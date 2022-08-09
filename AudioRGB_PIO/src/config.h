#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

  // define pins
  #define LED_L_R 6
  #define LED_L_G 5
  #define LED_L_B 3

  #define LED_R_R 11
  #define LED_R_G 10
  #define LED_R_B 9

  #define TCH_1 8
  #define TCH_2 7
  #define TCH_3 4
  #define TCH_4 2

  #define AUX_L A0
  #define AUX_R A1

  #define RNG_1 A2
  #define RNG_2 A3

  // define helper 'pins'
  #define LED_L 0
  #define LED_R 1

  // define constants
  #define BUFFER_SIZE_AUX 2  
  #define ARRAY_SIZE_RGB 3
  #define ARRAY_SIZE_TCH 4

  #define VOLUME_MIN 0
  #define VOLUME_MAX 100
  #define VOLUME_BOOST 2 //30%->5, 100%->1

  #define COLOR_MIN 0
  #define COLOR_MAX 255
  #define COLOR_HALF 127.5f

  #define COLOR_L_CYCLE 30
  #define COLOR_L_FADE 10

  #define COLOR_R_CYCLE 50
  #define COLOR_R_FADE 2

  #define DELAY 1

#endif