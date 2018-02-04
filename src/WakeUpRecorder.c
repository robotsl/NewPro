#include <wiringPi.h>//包含wiringPi头文件  
#include <unistd.h>  
int main(void)  
{  
    int ret = 0;
    wiringPiSetup();        //wiringPi库初始化  
    pinMode(1, INPUT);     //设置0口为输出模式  
    pinMode(0, OUTPUT);     //设置0口为输出模式
    for(;;)
    { 
	if ((ret = digitalRead(1)) == 0)
	{		
    		execl("./asr_record_sample","asr_record_sample",NULL);
	}else{
		digitalWrite(0,HIGH);
	}
    }
    return 0;  
}  
