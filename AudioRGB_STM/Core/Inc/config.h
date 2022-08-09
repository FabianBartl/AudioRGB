/*
 * config.h
 *
 *  Created on: Aug 2, 2022
 *      Author: FabianBartl
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#define DEBUG 1

#define BUFFER_SIZE_AUX 2

#define CHANNEL_COUNT_RGB 3
#define CHANNEL_COUNT_ADC 3

#define VOLUME_MIN 0
#define VOLUME_MAX 600
#define VOLUME_BOOST 2

#define COLOR_MIN 0
#define COLOR_MAX 255
#define COLOR_HALF 127.5f

#define COLOR_CYCLE 30
#define COLOR_FADE 10

#define DELAY 1
#define TIMEOUT_ADC 1

#define MIN_INT32 -2147483648
#define MAX_INT32 2147483647

#endif /* INC_CONFIG_H_ */
