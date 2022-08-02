/*
 * functions.c
 *
 *  Created on: Aug 2, 2022
 *      Author: FabianBartl
 */

#include "config.h"

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

// apply an average-filter to the buffer array
int bufferFilter(int *arr)
{
	int sum = 0;
	for(size_t i=0; i < BUFFER_SIZE_AUX; i++) sum += arr[i];
	return sum / BUFFER_SIZE_AUX;
}

// ----------------------------
// saturate, transform, amplify
// ----------------------------

int saturate(int val) { return saturate(val, COLOR_MIN, COLOR_MAX); }
int saturateLimits(int val, int lowerLim, int upperLim) { return (val < lowerLim) ? lowerLim : ((val > upperLim) ? upperLim : val); }

int transform(int val, int inMin, int inMax, int outMin, int outMax)
{
	int inHalf = inMin + (inMax - inMin) / 2;
	int outHalf = outMin + (outMax - outMin) / 2;
	return val - (inHalf - outHalf);
}

int amplify(int val) { return amplify(val, VOLUME_BOOST); }
int amplifyFactor(int val, int fac) { return val * fac; }

// --------------
// serial plotter
// --------------

/*
// blue, red, green, yellow, purple
void plotArduino(int *valArr, int lenArr)
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

void writeRGB(int pin, int *rgb)
{
	switch(pin)
	{
		case LED_L:
			analogWrite(LED_R_R, saturate(rgb[0]));
			analogWrite(LED_R_G, saturate(rgb[1]));
			analogWrite(LED_R_B, saturate(rgb[2]));
			break;
		case LED_R:
			analogWrite(LED_L_R, saturate(rgb[0]));
			analogWrite(LED_L_G, saturate(rgb[1]));
			analogWrite(LED_L_B, saturate(rgb[2]));
			break;
	}
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

void emptyArray(int *arr, size_t arrLen) { fillArray(0, arr, arrLen); }
void fillArray(int val, int *arr, size_t arrLen) { for(int i=0; i < arrLen; i++) arr[i] = val; }

int arrayAvr(int *arr, int arrLen) { return arraySum(arr, arrLen) / arrLen; }
int arraySum(int *arr, int arrLen)
{
	int sum = 0;
	for(int i=0; i < arrLen; i++) sum += arr[i];
	return sum;
}
