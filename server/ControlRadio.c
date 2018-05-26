#include "./ControlRadio.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
{DO,ONESEC*2}
};

void beep(int freq,int t_ms)
{
      int range;
      if(freq<2000||freq>5000)
      {
	printf("invalid freq");
	return;
      }
      range=600000/freq;
      pwmSetRange(range);
      pwmWrite(1,range/2);
      if(t_ms>0)
      {
	delay(t_ms);
      }
}

int radioInit()
{
  if (wiringPiSetup () == -1)
       return -1;
  pinMode (1, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(32);
}



int ControlRadio(int opt)
{
  int index=0 ;
  radioInit();

  if (opt == 0)
  {
      for (;index<sizeof(star_notation)/sizeof(TONE);index++)
      {
        beep(star_notation[index].freq,star_notation[index].t_ms);
        pwmWrite(1,0);
        delay(100);
      }
      pwmWrite(1,0);
  }
  else
  {
    //pinMode (6, 0) ;
  }
  return 0 ;
}
