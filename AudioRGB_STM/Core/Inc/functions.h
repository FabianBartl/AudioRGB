/*
 * functions.h
 *
 *  Created on: Aug 2, 2022
 *      Author: FabianBartl
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

// circular buffer
void bufferAppend(int val, int *arr, size_t *ind);
int bufferFilter(int *arr, size_t *ind);

// saturate, transform, amplify
int saturateLimits(int val, int lowerLim, int upperLim);
int saturate(int val);
int transform(int val, int inMin, int inMax, int outMin, int outMax);
int amplifyFactor(int val, int fac);
int amplify(int val);

// min, max
int min(int a, int b);
int max(int a, int b);

// noise generator
int noise();
int noiseLimit(int mod);

// rgb
void writeRGB(int r, int g, int b);
void writeRGBArray(int *rgb);
int generator(int val);
int generatorLimit(int val, int lowerLim, int upperLim);

// arrays
void fillArray(int val, int *arr, const size_t arrLen);
void emptyArray(int *arr, const size_t arrLen);
int arraySum(int *arr, const size_t arrLen);
int arrayAvr(int *arr, const size_t arrLen);
int arrayMin(int *arr, const size_t arrLen);
int arrayMax(int *arr, const size_t arrLen);

#endif /* INC_FUNCTIONS_H_ */
