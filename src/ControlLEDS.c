#include<wiringPi.h>//包含wiringPi头文件
#include <stdio.h>
#include <string.h>
  
int main(int argc,char *argv[])  
{  
    wiringPiSetup();        //wiringPi库初始化  
    pinMode(0, OUTPUT);     //设置0口为输出模式  
    pinMode(28, OUTPUT);     //设置0口为输出模式  
    pinMode(29, OUTPUT);     //设置0口为输出模式  
	if (!strcmp(argv[1],"yellow"))
	{   
		if (!strcmp(argv[2],"on"))
		{
   			digitalWrite(0,  HIGH); //GPIO.0输出高电平  
		}        //延迟1000ms  
		if (!strcmp(argv[2],"off"))
		{
   			digitalWrite(0,  LOW); //GPIO.0输出高电平  
		}        //延迟1000ms  
	}
	else if (!strcmp(argv[1],"red"))
	{   
		if (!strcmp(argv[2],"on"))
		{
   			digitalWrite(28,  HIGH); //GPIO.0输出高电平  
		}        //延迟1000ms  
		if (!strcmp(argv[2],"off"))
		{
   			digitalWrite(28,  LOW); //GPIO.0输出高电平  
		}        //延迟1000ms  
	}
	else if (!strcmp(argv[1],"green"))
	{   
		if (!strcmp(argv[2],"on"))
		{
   			digitalWrite(29,  HIGH); //GPIO.0输出高电平  
		}        //延迟1000ms  
		if (!strcmp(argv[2],"off"))
		{
   			digitalWrite(29,  LOW); //GPIO.0输出高电平  
		}        //延迟1000ms  
	}
    return 0;  
}  
