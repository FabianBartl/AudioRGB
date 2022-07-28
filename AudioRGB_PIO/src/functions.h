#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

    // states
    #define _INPUT 0
    #define _INPUT_PULLUP 1
    #define _OUTPUT 2
    #define _LOW 0
    #define _HIGH 1

    // helper constants for pins
    #define B0_5 0
    #define B0 0
    #define B1 1
    #define B2 2
    #define B3 3
    #define B4 4
    #define B5 5
    #define C0_5 1
    #define C0 6
    #define C1 7
    #define C2 8
    #define C3 9
    #define C4 10
    #define C5 11
    #define D0_7 2
    #define D0 12
    #define D1 13
    #define D2 14
    #define D3 15
    #define D4 16
    #define D5 17
    #define D6 18
    #define D7 19

    // pin functions: helper pin -> PORT/DDR, mode, digital/analog read/write
    int _pin2port(int pin);
    int _pin2ddr(int pin);
    void _pinMode(int pin, int mode);
    int _analogRead(int pin);
    void _analogWrite(int pin);
    int _digitalRead(int pin);
    void _digitalWrite(int pin);

    // buffer functions: append, filter
    void bufferAppend(int val, int *arr, size_t *ind);
    int bufferFilter(int *arr);

#endif