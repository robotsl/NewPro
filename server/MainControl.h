/*************************************************************************
>FileName: MainControl.h
>Author: liaoxingbin
>CreatedTime:2018��04��10�� 19:53:16
************************************************************************/

#ifndef __MAINCONTROL_H__
#define __MAINCONTROL_H__

typedef struct operate {
    char operators[10];
    char object[10];
}OP;

extern char *retString(char *string);

char  *split(char *str,OP *op);

char* substring(char *desc,const char *src,int start,int ends);

int local_command(char *operators, char *object);

#endif
