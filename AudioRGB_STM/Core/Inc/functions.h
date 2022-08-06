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
int bufferFilter(int *arr);

// saturate, transform, amplify
int saturate(int val);
int saturateLimits(int val, int lowerLim, int upperLim);
int transform(int val, int inMin, int inMax, int outMin, int outMax);
int amplify(int val);
int amplifyFactor(int val, int fac);

// serial plotter
void plotArduino(int *valArr, size_t lenArr);

// noise generator
int noise(int pin);
int noiseLimit(int pin, int mod);

// rgb
void writeRGB(int r, int g, int b);
void writeRGBArray(int *rgb);
float generator(float val);

// arrays
void emptyArray(int *arr, size_t arrLen);
void fillArray(int val, int *arr, size_t arrLen);
int arrayAvr(int *arr, size_t arrLen);
int arraySum(int *arr, size_t arrLen);

#endif /* INC_FUNCTIONS_H_ */