#include "ControlLEDS.h"

void ControlLEDS(char *led,char *control)
{
	  int flag = 0,ret = 0;
    wiringPiSetup();        //wiringPi库初始化
    pinMode(0, OUTPUT);     //设置0口为输出模式
    pinMode(28, OUTPUT);     //设置0口为输出模式
    pinMode(29, OUTPUT);     //设置0口为输出模式

	if (!strcmp(led,"yellow"))
	{
		flag = 1;
	}
	else if (!strcmp(led,"red"))
	{
		flag = 2;
	}
	else if (!strcmp(led,"green"))
	{
		flag = 3;
	}
	switch (flag){
		case 1:
			if (!strcmp(control,"on"))
			{
				digitalWrite(0,  HIGH); //GPIO.0输出高电平
			}        //延迟1000ms
			if (!strcmp(control,"off"))
			{
				digitalWrite(0,  LOW); //GPIO.0输出高电平
			}
			break;
		case 2:
			if (!strcmp(control,"on"))
			{
				digitalWrite(28,  HIGH); //GPIO.0输出高电平
			}        //延迟1000ms
			if (!strcmp(control,"off"))
			{
				digitalWrite(28,  LOW); //GPIO.0输出高电平
			}
			break;
		case 3:
			if (!strcmp(control,"on"))
			{
				digitalWrite(29,  HIGH); //GPIO.0输出高电平
			}        //延迟1000ms
			if (!strcmp(control,"off"))
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
