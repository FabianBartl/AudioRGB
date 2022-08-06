/*
 * functions.c
 *
 *  Created on: Aug 2, 2022
 *      Author: FabianBartl
 */

#include "config.h"
#include "tim.h"

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

// apply an average-filter to the buffer array
int bufferFilter(int *arr)
{
	int sum = 0;
	for(int i=0; i < BUFFER_SIZE_AUX; i++) sum += arr[i];
	return sum / BUFFER_SIZE_AUX;
}

// ----------------------------
// saturate, transform, amplify
// ----------------------------

int saturate(int val) { return saturateLimits(val, COLOR_MIN, COLOR_MAX); }
int saturateLimits(int val, int lowerLim, int upperLim) { return (val < lowerLim) ? lowerLim : ((val > upperLim) ? upperLim : val); }

int transform(int val, int inMin, int inMax, int outMin, int outMax)
{
	int inHalf = inMin + (inMax - inMin) / 2;
	int outHalf = outMin + (outMax - outMin) / 2;
	return val - (inHalf - outHalf);
}

int amplify(int val) { return amplifyFactor(val, VOLUME_BOOST); }
int amplifyFactor(int val, int fac) { return val * fac; }

// --------------
// serial plotter
// --------------

/*
// blue, red, green, yellow, purple
void plotArduino(int *valArr, const size_t lenArr)
{
	for(int i=0; i < lenArr-1; i++)
	{
		Serial.print(valArr[i]);
		Serial.print(",");
	}
	Serial.print(valArr[lenArr-1]);
	// flush data
	Serial.println("");
	Serial.flush();
}
*/

// ---------------
// noise generator
// ---------------

int noiseLimit(int pin, int mod) { return noise(pin) % mod; }
int noise(int pin)
{
	return analogRead(pin);
}

// ----
// rgbs
// ----

void writeRGBArray(int *rgb) { writeRGB(rgb[0], rgb[1], rgb[2]); }
void writeRGB(int r, int g, int b)
{
	TIM3->CCR3 = saturate(r);
	TIM3->CCR1 = saturate(g);
	TIM3->CCR2 = saturate(g);
/*
	// prevent higher pulses than period
	if (TIM3->CCR3 > TIM3->ARR) TIM3->CCR3 = 0;
	if (TIM3->CCR1 > TIM3->ARR) TIM3->CCR1 = 0;
	if (TIM3->CCR2 > TIM3->ARR) TIM3->CCR2 = 0;
*/
}

// color generator
float generator(float val)
{
	return transform(
		amplify(val),
		amplify(VOLUME_MIN),
		amplify(VOLUME_MAX),
		COLOR_MIN,
		COLOR_MAX
	);
}

// ------
// arrays
// ------

void emptyArray(int *arr, const size_t arrLen) { fillArray(0, arr, arrLen); }
void fillArray(int val, int *arr, const size_t arrLen) { for(int i=0; i < arrLen; i++) arr[i] = val; }

int arrayAvr(int *arr, const size_t arrLen) { return arraySum(arr, arrLen) / arrLen; }
int arraySum(int *arr, const size_t arrLen)
{
	int sum = 0;
	for(int i=0; i < arrLen; i++) sum += arr[i];
	return sum;
}
