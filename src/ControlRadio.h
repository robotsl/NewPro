#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

TONE star_notation[]=
{
{DO,ONESEC},
{DO,ONESEC},
{SO,ONESEC},
{SO,ONESEC},
{LA,ONESEC},
{LA,ONESEC},
{SO,ONESEC*2},

{FA,ONESEC},
{FA,ONESEC},
{MI,ONESEC},
{MI,ONESEC},
{RE,ONESEC},
{RE,ONESEC},
{DO,ONESEC*2},

{SO,ONESEC},
{SO,ONESEC},
{FA,ONESEC},
{FA,ONESEC},
{MI,ONESEC},
{MI,ONESEC},
{RE,ONESEC*2},

{SO,ONESEC},
{SO,ONESEC},
{FA,ONESEC},
{FA,ONESEC},
{MI,ONESEC},
{MI,ONESEC},
{RE,ONESEC*2},

{DO,ONESEC},
{DO,ONESEC},
{SO,ONESEC},
{SO,ONESEC},
{LA,ONESEC},
{LA,ONESEC},
{SO,ONESEC*2},


{FA,ONESEC},
{FA,ONESEC},
{MI,ONESEC},
{MI,ONESEC},
{RE,ONESEC},
{RE,ONESEC},
{DO,ONESEC*2},
};


void beep(int freq,int t_ms);

void init();

void ControlRadio(int opt)£»

