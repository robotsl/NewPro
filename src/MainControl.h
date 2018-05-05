/*************************************************************************
>FileName: MainControl.h
>Author: liaoxingbin
>CreatedTime:2018年04月10日 19:53:16
************************************************************************/

#include <stdio.h>

void split(char *str,OP *op){
    if (!strcnmp("打开",6)){
        strcpy(op->operators,"on");
    } else if (!strcnmp("关闭",6)){
        strcpy(op->operators,"off");
    }
    if (!strncmp(substring(desc,str,5,strlen(str)),"红灯",6)){
        strcpy(op->object,"red_led");
    }
    if (!strncmp(substring(desc,str,5,strlen(str)),"黄灯",6)){
        strcpy(op->object,"ello_led");
    }
    if (!strncmp(substring(desc,str,5,strlen(str)),"绿灯",6)){
        strcpy(op->object,"blue_led");
    }
    if (!strncmp(substring(desc,str,5,strlen(str)),"音响",6)){
        strcpy(op->object,"radio");
    }
    if (!strncmp(substring(desc,str,5,strlen(str)),"温湿度传感器",18)){
        strcpy(op->object,"temp");
    }
}

char* substring(char *desc,const char *src,int start,int ends){
    char *s = desc;
    int i = start;
    if (start > ends || start < 0 || ends < 0 || strlen(src) < start || strlen(src) < ends || src == NULL){
        return NULL;
    } else if (start > 0 && ends > start && strlen(src) > start && strlen(src) > ends){
        while (i < ends && *(src + i) != '\0'){
            *s++ = *(src + i++);
        }
        s = '\0';
        return desc;
    }
}

int local_command(char *operators, char *object) {
  int opt = 0;
  char *str[6] = {"red_led","yellow_led","blue_led","radio","temp_sensor","fire_sensor};
  if (!strcmp(operators, "on")) opt = 0;
  else if (!strcmp(operators, "off")) opt = 1;

  if (!strcmp(object,"red_led"))
    ControlLEDS("red_led",opt==0?"on":"off");
  if (!strcmp(object,"yellow_led"))
    ControlLEDS("yellow_led",opt==0?"on":"off");
  if (!strcmp(object,"blue_led"))
    ControlLEDS("blue_led",opt==0?"on":"off");

  if (!strcmp(object,"radio"))
    ControlRadio("radio",opt==0?"on":"off");
  if (!strcmp(object,"temp_sensor"))
    ControlTempSensor("temp_sensor",opt==0?"on":"off");
  if (!strcmp(object,"fire_sensor"))
    ControlFireSensor("fire_sensor",opt==0?"on":"off");
}
