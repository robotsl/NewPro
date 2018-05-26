#ifndef __CONTROLRADIO_H__
#define  __CONTROLRADIO_H__

typedef struct _TONE{
  int freq;
  int t_ms;
} TONE,*PTONE;

#define ONESEC 1000/2

#define DO 2093
#define RE  2349
#define MI 2637
#define FA 2794
#define SO 3136
#define LA 3520
#define XI 3951
#define DO1 4186
#define RI1 4698



void beep(int freq,int t_ms);

int radioInit();

int ControlRadio(int opt);
#endif
