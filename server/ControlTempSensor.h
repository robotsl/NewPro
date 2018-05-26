#ifndef __CONTROLTEMPSENSOR_H__
#define __CONTROLTEMPSENSOR_H__

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;

#define HIGH_TIME 32

uint32 databuf;

typedef struct dht11 {
  float RH;
  float TMP;
}DHT;

uint8 readSensorData(void);
DHT *readData(DHT *dht);
int ControlTempSensor(int opt);

#endif
