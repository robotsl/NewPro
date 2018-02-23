#include "dht11_1.h"
  
uint8 readSensorData(void)  
{  
    uint8 crc;   
    uint8 i;  
   
    pinMode(pinNumber,OUTPUT); // set mode to output  
    digitalWrite(pinNumber, 0); // output a high level   
    delay(25);  
    digitalWrite(pinNumber, 1); // output a low level   
    pinMode(pinNumber, INPUT); // set mode to input  
    pullUpDnControl(pinNumber,PUD_UP);  
  
    delayMicroseconds(27);  
    if(digitalRead(pinNumber)==0) //SENSOR ANS  
       {  
         while(!digitalRead(pinNumber)); //wait to high  
  
      for(i=0;i<32;i++)  
       {  
       while(digitalRead(pinNumber)); //data clock start  
       while(!digitalRead(pinNumber)); //data start  
          delayMicroseconds(HIGH_TIME);  
          databuf*=2;  
           if(digitalRead(pinNumber)==1) //1  
           {  
                databuf++;  
           }  
        }  
  
      for(i=0;i<8;i++)  
       {  
       while(digitalRead(pinNumber)); //data clock start  
       while(!digitalRead(pinNumber)); //data start  
          delayMicroseconds(HIGH_TIME);  
          crc*=2;    
          if(digitalRead(pinNumber)==1) //1  
           {  
                crc++;  
           }  
        }  
    return 1;  
       }  
   else  
        {  
        return 0;  
         }  
}  
   
DHT *readData (DHT *dht)  
{  
  if (-1 == wiringPiSetup()) 
  {  
    printf("Setup wiringPi failed!");  
    return 1;  
  }  
   
  pinMode(pinNumber, OUTPUT); // set mode to output  
  digitalWrite(pinNumber, 1); // output a high level   
  
    pinMode(pinNumber,OUTPUT); // set mode to output  
    digitalWrite(pinNumber, 1); // output a high level   
    delay(3000);  
    if(readSensorData())  
    {  
		dht.RH = (databuf>>24)&0xff + 0.1 * (databuf>>16)&0xff)；
		dht.TMP = (databuf>>8)&0xff + 0.1 * databuf&0xff;
       //printf("Congratulations ! Sensor data read ok!\n");  
       //printf("RH:%d.%d\n",(databuf>>24)&0xff,(databuf>>16)&0xff);   
       //printf("TMP:%d.%d\n",(databuf>>8)&0xff,databuf&0xff);  
       databuf=0;  
     }  
    else  
     {  
        printf("Sorry! Sensor dosent ans!\n");  
       databuf=0;  
      }    
  return &dht;  
}  
