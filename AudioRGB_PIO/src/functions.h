#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

  // circular buffer functions
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
  int noise();
  int noise(int mod);

  // rgb
  void writeRGB(int *rgb);
  float generator(float val);

#endif