#include "./ControlTempSensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int pinNumber = 26; // use gpio1 to read data

uint8 readSensorData(void) {
    uint8 crc;
    uint8 i;

    pinMode(pinNumber, OUTPUT); // set mode to output
    digitalWrite(pinNumber, 0); // output a high level
    delay(25);
    digitalWrite(pinNumber, LOW); // output a low level
    pinMode(pinNumber, INPUT);  // set mode to input
    pullUpDnControl(pinNumber, PUD_UP);

    delayMicroseconds(27);
    if (digitalRead(pinNumber) == 0) { // SENSOR ANS
        while (!digitalRead(pinNumber))
            ; // wait to high
        for (i = 0; i < 32; i++) {
            while (digitalRead(pinNumber))
                ; // data clock start
            while (!digitalRead(pinNumber))
                ; // data start
            delayMicroseconds(HIGH_TIME);
            databuf *= 2;
            if (digitalRead(pinNumber) == 1) { // 1
                databuf++;
            }
        }

        for (i = 0; i < 8; i++) {
            while (digitalRead(pinNumber))
                ; // data clock start
            while (!digitalRead(pinNumber))
                ; // data start
            delayMicroseconds(HIGH_TIME);
            crc *= 2;
            if (digitalRead(pinNumber) == 1) { // 1
                crc++;
            }
        }
        return 1;
    } else {
        return 0;
    }
}

DHT *readData(DHT *dht) {
    if (-1 == wiringPiSetup()) {
        printf("Setup wiringPi failed!");
        return 1;
    }

    pinMode(pinNumber, OUTPUT); // set mode to output
    digitalWrite(pinNumber, 1); // output a high level

    pinMode(pinNumber, OUTPUT); // set mode to output
    digitalWrite(pinNumber, 1); // output a high level
    delay(3000);
    //while (1){
    	if (readSensorData()) {
    	    dht->RH = 1.0 * ((databuf>>24)&0xff) + 0.1 * ((databuf>>16)&0xff);
    	    dht->TMP = 1.0 * ((databuf>>8)&0xff) + 0.1 * (databuf&0xff);
    	    // printf("Congratulations ! Sensor data read ok!\n");
    	    // printf("RH:%d.%d\n",(databuf>>24)&0xff,(databuf2yy>>16)&0xff);
    	    // printf("TMP:%d.%d\n",(databuf>>8)&0xff,databuf&0xfpf);
    	    printf("RH:%f\n",dht->RH);
    	    printf("TMP:%f\n",dht->TMP);
    	    databuf = 0;
	   // break;
    	} else {
       	 printf("Sorry! Sensor dosent ans!\n");
       	 databuf = 0;
    	}
    //}
    return dht;
}

int ControlTempSensor(int opt) {
    DHT *dht = (DHT *)malloc(sizeof(DHT));
    dht->RH = 0.0;
    dht->TMP = 0.0;
    printf("opt = %d\n",opt);
    if (opt == 0) {
        //shutdown the sensor
        pinMode(pinNumber, OUTPUT); // set mode to output
        digitalWrite(pinNumber, 1); // output a high level
	readData(dht);
        return 0;
    } else if (opt == 1) {
      pinMode(pinNumber, OUTPUT); // set mode to output
      digitalWrite(pinNumber, 0); // output a high level
        //open the sensor
        return 0;
    }
}
