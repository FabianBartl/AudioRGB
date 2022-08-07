/*
 * functions.c
 *
 *  Created on: Aug 2, 2022
 *      Author: FabianBartl
 */

#include "config.h"
#include "tim.h"
#include "adc.h"

#define min(a,b) (a<b?a:b)

// ---------------
// circular buffer
// ---------------

// implements an append function for a circular array
// when the array is full, the values at the beginning are overwritten
// the buffer array contains the last measured ADC elements to smooth the audio signal
void bufferAppend(int val, int *arr, int *ind)
{
	*ind = (*ind+1 > BUFFER_SIZE_AUX-1) ? 0 : *ind+1;
	arr[*ind] = val;
}

// apply an average-filter to the last elements of the buffer array
int bufferFilter(int *arr, int *ind)
{
	int sum = 0;
	for(int i=0, p=0; i < FILTER_SIZE_AUX; i++)
	{
		p = (*ind-i < 0) ? BUFFER_SIZE_AUX-1 : *ind-i;
		sum += arr[p];
	}
	return sum / BUFFER_SIZE_AUX;
}

// ----------------------------
// saturate, transform, amplify
// ----------------------------

int saturateLimits(int val, int lowerLim, int upperLim) { return (val < lowerLim) ? lowerLim : ((val > upperLim) ? upperLim : val); }
int saturate(int val) { return saturateLimits(val, COLOR_MIN, COLOR_MAX); }

int transform(int val, int inMin, int inMax, int outMin, int outMax)
{
	int inHalf = inMin + (inMax - inMin) / 2;
	int outHalf = outMin + (outMax - outMin) / 2;
	return val - (inHalf - outHalf);
}

int amplifyFactor(int val, int fac) { return val * fac; }
int amplify(int val) { return amplifyFactor(val, VOLUME_BOOST); }

// ---------------
// noise generator
// ---------------

int noise()
{
	// get noise from adc
	ADC_Select_CH12();
	HAL_ADC_Start(&hadc1);
	if (HAL_ADC_PollForConversion(&hadc1, TIMEOUT_ADC) == HAL_OK)
	{
		return HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);
	}
}
int noiseLimit(int mod) { return noise() % mod; }

// ----
// rgbs
// ----

void writeRGB(int r, int g, int b)
{
	// prevent higher pulses than period
	TIM4->CCR1 = min(saturate(r), TIM4->ARR);
	TIM3->CCR2 = min(saturate(g), TIM3->ARR);
	TIM3->CCR1 = min(saturate(b), TIM3->ARR);
}
void writeRGBArray(int *rgb) { writeRGB(rgb[0], rgb[1], rgb[2]); }

// color generator
int generator(int val)
{
	return transform(
		amplify(val),
		VOLUME_MIN,
		VOLUME_MAX,
		COLOR_MIN,
		COLOR_MAX
	);
}

// ------
// arrays
// ------

void fillArray(int val, int *arr, const size_t arrLen) { for(int i=0; i < arrLen; i++) arr[i] = val; }
void emptyArray(int *arr, const size_t arrLen) { fillArray(0, arr, arrLen); }

int arraySum(int *arr, const size_t arrLen)
{
	int sum = 0;
	for(int i=0; i < arrLen; i++) sum += arr[i];
	return sum;
}
int arrayAvr(int *arr, const size_t arrLen) { return arraySum(arr, arrLen) / arrLen; }
