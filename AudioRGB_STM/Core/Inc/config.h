/*
 * config.h
 *
 *  Created on: Aug 2, 2022
 *      Author: FabianBartl
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#define BUFFER_SIZE_AUX 20
#define FILTER_SIZE_AUX 2

#define CHANNEL_COUNT_RGB 3
#define CHANNEL_COUNT_TCH 4
#define CHANNEL_COUNT_ADC 2

#define VOLUME_MIN 100
#define VOLUME_MAX 500
#define VOLUME_BOOST 4

#define COLOR_MIN 0
#define COLOR_MAX 255
#define COLOR_HALF 127.5f

#define COLOR_CYCLE 30
#define COLOR_FADE 10

#define DELAY 10
#define TIMEOUT_ADC 3

#define MIN_INT32 -4294967296
#define MAX_INT32 4294967295

#define MIN_UINT16 0
#define MAX_UINT16 65535

#endif /* INC_CONFIG_H_ */
