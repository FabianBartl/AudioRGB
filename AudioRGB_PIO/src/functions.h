#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

  // circular buffer functions
  void bufferAppend(int val, int *arr, size_t *ind);
  int bufferFilter(int *arr);
  
  // saturation of (color) values
  int saturate(int val);
  int saturate(int val, int lowerLim, int upperLim);

  // serial plotter
  void plot(int *valArr, int lenArr);
  void plot(int *valArr, char *symArr, int lenArr);

#endif