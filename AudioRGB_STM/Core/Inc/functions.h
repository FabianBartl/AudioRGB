/*
 * functions.h
 *
 *  Created on: Aug 2, 2022
 *      Author: FabianBartl
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

// circular buffer
void bufferAppend(int val, int *arr, int *ind);
int bufferFilter(int *arr, int *ind);

// saturate, transform, amplify
int saturateLimits(int val, int lowerLim, int upperLim);
int saturate(int val);
int transform(int val, int inMin, int inMax, int outMin, int outMax);
int amplifyFactor(int val, int fac);
int amplify(int val);

// noise generator
int noise();
int noiseLimit(int mod);

// rgb
void writeRGB(int r, int g, int b);
void writeRGBArray(int *rgb);
float generator(float val);

// arrays
void fillArray(int val, int *arr, const size_t arrLen);
void emptyArray(int *arr, const size_t arrLen);
int arraySum(int *arr, const size_t arrLen);
int arrayAvr(int *arr, const size_t arrLen);

#endif /* INC_FUNCTIONS_H_ */
