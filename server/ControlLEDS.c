#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include "./ControlLEDS.h"

int ControlLEDS(char *led,char *control)
{
    int flag = 0,ret = 0;
    wiringPiSetup();        //wiringPi库初始化
    pinMode(27, OUTPUT);     //设置27口为输出模式,green
    pinMode(28, OUTPUT);     //设置28口为输出模式,yellow
    pinMode(29, OUTPUT);     //设置29口为输出模式,red

	if (!strcmp(led,"blue_led"))
	{
		flag = 1;
	}
	else if (!strcmp(led,"yellow_led"))
	{
		flag = 2;
	}
	else if (!strcmp(led,"red_led"))
	{
		flag = 3;
	}
	printf("flag = %d\n",flag);
	switch (flag){
		case 1:
			if (!strcmp(control,"on"))
			{
				digitalWrite(27,  HIGH); //GPIO.0输出高电平
			}        //延迟1000ms
			if (!strcmp(control,"off"))
			{
				digitalWrite(27,  LOW); //GPIO.0输出高电平
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
			ret = 1;
			break;
	}
    return ret;
}
