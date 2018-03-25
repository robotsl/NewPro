#include "ControlLEDS.h"
  
void ControlLEDS(int yellow,int red,int green,char *control)  
{  
	int flag = 0,ret = 0;
    wiringPiSetup();        //wiringPi库初始化  
    pinMode(0, OUTPUT);     //设置0口为输出模式  
    pinMode(28, OUTPUT);     //设置0口为输出模式  
    pinMode(29, OUTPUT);     //设置0口为输出模式  
	
	if (!strcmp(argv[1],"yellow"))
	{
		flag = 1;
	}
	else if (!strcmp(argv[1],"red"))
	{
		flag = 2;
	} 
	else if (!strcmp(argv[1],"green"))
	{
		flag = 3;
	}
	switch (flag){
		case 1:
			if (!strcmp(argv[2],"on"))
			{
				digitalWrite(0,  HIGH); //GPIO.0输出高电平  
			}        //延迟1000ms  
			if (!strcmp(argv[2],"off"))
			{
				digitalWrite(0,  LOW); //GPIO.0输出高电平  
			}  
			break;
		case 2:
			if (!strcmp(argv[2],"on"))
			{
				digitalWrite(28,  HIGH); //GPIO.0输出高电平  
			}        //延迟1000ms  
			if (!strcmp(argv[2],"off"))
			{
				digitalWrite(28,  LOW); //GPIO.0输出高电平  
			} 
			break;
		case 3:
			if (!strcmp(argv[2],"on"))
			{
				digitalWrite(29,  HIGH); //GPIO.0输出高电平  
			}        //延迟1000ms  
			if (!strcmp(argv[2],"off"))
			{
				digitalWrite(29,  LOW); //GPIO.0输出高电平  
			}  
			break;
		default:
			ret = -1;
			break;
	}
    return ret;  
}  
