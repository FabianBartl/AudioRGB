/*
 * functions.c
 *
 *  Created on: Aug 2, 2022
 *      Author: FabianBartl
 */

#include "config.h"
#include "tim.h"
#include "adc.h"

// --------
// min, max
// --------

float min(float a, float b) { return (a < b) ? a : b; }
float max(float a, float b) { return (a > b) ? a : b; }

// ------
// arrays
// ------

void fillArray(int val, int *arr, const size_t arrLen) { for(int i=0; i < arrLen; i++) arr[i] = val; }
void emptyArray(int *arr, const size_t arrLen) { fillArray(0, arr, arrLen); }

int arraySum(int *arr, const size_t arrLen)
{
	int sum = 0;
	for(size_t i=0; i < arrLen; i++) sum += arr[i];
	return sum;
}
float arrayAvr(int *arr, const size_t arrLen) { return (float)arraySum(arr, arrLen) / (float)arrLen; }

int arrayMin(int *arr, const size_t arrLen)
{
	int minVal = MAX_INT32;
	for (size_t i=0; i < arrLen; i++) minVal = min(minVal, arr[i]);
	return minVal;
}
int arrayMax(int *arr, const size_t arrLen)
{
	int maxVal = MIN_INT32;
	for (size_t i=0; i < arrLen; i++) maxVal = max(maxVal, arr[i]);
	return maxVal;
}

// ---------------
// circular buffer
// ---------------

// implements an append function for a circular array
// when the array is full, the values at the beginning are overwritten
// the buffer array contains the last measured ADC elements to smooth the audio signal
void bufferAppend(int val, int *arr, size_t *ind)
{
	*ind = (*ind+1 > BUFFER_SIZE_AUX-1) ? 0 : *ind+1;
	arr[*ind] = val;
}

// apply an average-filter to the last elements of the buffer array
float bufferFilter(int *arr)
{
	return arrayAvr(arr, BUFFER_SIZE_AUX);
}

// ----------------------------
// saturate, transform, amplify
// ----------------------------

float saturateLimits(float val, float lowerLim, float upperLim) { return (val < lowerLim) ? lowerLim : ((val > upperLim) ? upperLim : val); }
float saturate(float val) { return saturateLimits(val, COLOR_MIN, COLOR_MAX); }

float transform(float val, float inMin, float inMax, float outMin, float outMax)
{
	float inHalf = inMin + (inMax - inMin) / 2;
	float outHalf = outMin + (outMax - outMin) / 2;
	return val - (inHalf - outHalf);
}

float amplifyFactor(float val, float fac) { return val * fac; }
float amplify(float val) { return amplifyFactor(val, VOLUME_BOOST); }

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
	return -1;
}
int noiseLimit(int mod) { return noise() % mod; }

// ----
// rgbs
// ----

void writeRGB(int r, int g, int b)
{
	// prevent higher pulses than period
	TIM4->CCR1 = (int)min(saturate(r), TIM4->ARR);
	TIM3->CCR2 = (int)min(saturate(g), TIM3->ARR);
	TIM3->CCR1 = (int)min(saturate(b), TIM3->ARR);
}
void writeRGBArray(int *rgb) { writeRGB(rgb[0], rgb[1], rgb[2]); }

// color generator
float generatorLimit(float val, float lowerLim, float upperLim)
{
	return transform(
		val,
		lowerLim,
		upperLim,
		COLOR_MIN,
		COLOR_MAX
	);
}
float generator(float val) { return generatorLimit(amplify(val), VOLUME_MIN, VOLUME_MAX); }
