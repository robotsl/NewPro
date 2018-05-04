#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;

#define HIGH_TIME 32

int pinNumber = 1; // use gpio1 to read data
uint32 databuf;

typedef struct dht11 {
  float RH;
  float TMP;
} DHT;

uint8 readSensorData(void);
DHT *readData(DHT *dht);
void closeSensor();
void openSensor();
