#include <wiringPi.h>//包含wiringPi头文件
#include <unistd.h>
#include <string.h>
#include "./asr_record_sample.h"
#include "./WakeUpRecorder.h"

void *wake_string(char *instr) {
  int ret = 0;
  char str[100] = " ";
  wiringPiSetup();    // wiringPi库初始化
  pinMode(11, INPUT);  //设置1口为输出模式
  pinMode(0, OUTPUT); //设置0口为输出模式
  printf("in Wake***\n");
  printf("ret in weak %d\n",ret);
  for(;;){
      ret = digitalRead(11);
      if (ret == 1) {
  	   printf("打开录音文件,ret = %d\n %d",ret,HIGH);
  	   retString(str);
  	   printf("in wakeString.c retstr %s\n",str);
	   break;
     }
  }
  strcpy(instr, str);
  return instr;
}
