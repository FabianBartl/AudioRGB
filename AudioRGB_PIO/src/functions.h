#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

    // states
    #define _INPUT 0
    #define _OUTPUT 1
    #define _LOW 0
    #define _HIGH 1

    // pin functions: mode, digital/analog read/write
    void _pinMode(int pin, int mode);
    int _analogRead(int pin);
    void _analogWrite(int pin);
    int _digitalRead(int pin);
    void _digitalWrite(int pin);

    // buffer functions: append, filter
    void bufferAppend(int val, int *arr, size_t *ind);
    int bufferFilter(int *arr);

#endif