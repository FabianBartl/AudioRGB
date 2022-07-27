// define pins
#define LED_R 11
#define LED_G 10
#define LED_B 9
#define MIC_D 12
#define MIC_A A0

// define constants
#define DELAY 10
#define PRESCALE 32
#define BUFFER_SIZE 10

// define globals
unsigned long int time=0, timer=0;
int mic_a=0;
int r=0, g=0, b=0;
int *buffer = malloc(BUFFER_SIZE * sizeof(int));
