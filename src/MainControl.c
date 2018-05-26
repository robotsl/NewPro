#include "./WakeUpRecorder.h"
#include "./MainControl.h"
#include "./ControlRadio.h"
#include "./ControlLEDS.h"
#include "./asr_record_sample.h"
#include "./ControlTempSensor.h"
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>


char *split(char *str,OP *op){
    char desc[1024] = {NULL};
    int ret = strncmp(str,"打开",6);
    printf("in split,str : %s\n,ret = %d ,op->operators:%p\n",str,ret,op->operators);
    if (!ret){
        strcpy(op->operators,"on");
    } else if (!strncmp(str,"关闭",6)){
        strcpy(op->operators,"off");
    }else if (!strncmp(str,"关机",6)){
	 system("sudo poweroff");
    }
    substring(desc,str,6,strlen(str));
    ret = strncmp(desc,"红灯",6);
    if (!strncmp(desc,"红灯",6)){
        strcpy(op->object,"red_led");
	printf("红灯:%s\n",op->object);
    }
    else if (!strncmp(desc,"黄灯",6)){
        strcpy(op->object,"yellow_led");
    }
    else if (!strncmp(desc,"绿灯",6)){
        strcpy(op->object,"blue_led");
    }
    //else if (!strncmp(desc,"音响",6)){
      //  strcpy(op->object,"radio");
    //}
    else if (!strncmp(desc,"温湿度传感器",18)){
	printf("温湿度传感器\n");
        strcpy(op->object,"temp");
    }
    return op;
}

char* substring(char *desc,const char *src,int start,int ends){
    char *s = desc;
    int i = start;
    if (start > ends || start < 0 || ends < 0 || strlen(src) < start || strlen(src) < ends || src == NULL){
	printf("GG\n");
        return NULL;
    } else if (start > 0 && ends > start && strlen(src) > start && strlen(src) >= ends){
        while (i < ends && *(src + i) != '\0'){
            *s++ = *(src + i++);
        }
        s = '\0';
	printf("desc:%s\n",desc);
        return desc;
    } else {
	    return NULL;
    }
}

int local_command(char *operators, char *object) {
  int opt = 0,ret = 0;
  char *str[6] = {"red_led","yellow_led","blue_led","radio","temp_sensor","fire_sensor"};
  if (!strcmp(operators, "on")) opt = 0;
  else if (!strcmp(operators, "off")) opt = 1;

  if (!strcmp(object,"red_led"))
    ret = ControlLEDS("red_led",opt==0?"on":"off");
  if (!strcmp(object,"yellow_led"))
    ret = ControlLEDS("yellow_led",opt==0?"on":"off");
  if (!strcmp(object,"blue_led"))
    ret = ControlLEDS("blue_led",opt==0?"on":"off");

  if (!strcmp(object,"radio"))
    ret = ControlRadio(opt);
  if (!strcmp(object,"temp"))
    ret = ControlTempSensor(opt);
  //if (!strcmp(object,"fire_sensor"))
    //ret = ControlFireSensor("fire_sensor",opt==0?"on":"off");
  return ret;
}


int main() {
    int ret1 = 0;
    char ret[100] = {NULL};
    OP *op = (OP *)(malloc(sizeof(OP)));
    //wiringPiSetup();
    //radioInit();
    //pinMode(6, OUTPUT);
    //digitalWrite(6,HIGH);
    beforeRecord();
    while (1) {
	wake_string(ret);
	printf("in main,ret = %s\n",ret);
       	split(ret, op);
	printf("split over,op->op:%s,op->ob:%s",op->operators,op->object);
       	ret1 = local_command(op->operators, op->object);
       	bzero(op, sizeof(op));
       	ret1 = 0;
   }
    	logout();
   	return 0;
exit:
	logout();
	return 0;
}
