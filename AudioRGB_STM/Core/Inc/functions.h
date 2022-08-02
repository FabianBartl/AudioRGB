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
int bufferFilter(int *arr);

// saturate, transform, amplify
int saturate(int val);
int saturate(int val, int lowerLim, int upperLim);
int transform(int val, int inMin, int inMax, int outMin, int outMax);
int amplify(int val);
int amplify(int val, int fac);

// serial plotter
void plot(int *valArr, int lenArr);
void plot(int *valArr, char *symArr, int lenArr);

// noise generator
int noise(int pin);
int noise(int pin, int mod);

// rgb
void writeRGB(int pin, int *rgb);
float generator(float val);

// arrays
void emptyArray(int *arr, size_t arrLen);
void fillArray(int val, int *arr, size_t arrLen);
int arrayAvr(int *arr, int arrLen);
int arraySum(int *arr, int arrLen);

#endif /* INC_FUNCTIONS_H_ */
