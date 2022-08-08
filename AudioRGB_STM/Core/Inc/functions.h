/*
 * functions.h
 *
 *  Created on: Aug 2, 2022
 *      Author: FabianBartl
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

// min, max
float min(float a, float b);
float max(float a, float b);

// arrays
void fillArray(int val, int *arr, const size_t arrLen);
void emptyArray(int *arr, const size_t arrLen);
int arraySum(int *arr, const size_t arrLen);
float arrayAvr(int *arr, const size_t arrLen);
int arrayMin(int *arr, const size_t arrLen);
int arrayMax(int *arr, const size_t arrLen);

// circular buffer
void bufferAppend(int val, int *arr, size_t *ind);
float bufferFilter(int *arr);

// saturate, transform, amplify
int saturateLimits(float val, int lowerLim, int upperLim);
int saturate(float val);
float transform(float val, float inMin, float inMax, float outMin, float outMax);
float amplifyFactor(float val, float fac);
float amplify(float val);

// noise generator
int noise();
int noiseLimit(int mod);

// rgb
void writeRGB(int r, int g, int b);
void writeRGBArray(int *rgb);
float generator(float val);
float generatorLimit(float val, float lowerLim, float upperLim);

#endif /* INC_FUNCTIONS_H_ */
