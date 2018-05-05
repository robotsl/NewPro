#include "ControlRadio.h"

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

void init()
{
  if (wiringPiSetup () == -1)
       exit (1) ;
  pinMode (1, PWM_OUTPUT) ;
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(32);
}`



void controlRadio(int opt)
{
  int index=0 ;

  init();

  if (opt == 1)
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
      //¹Øµôadio
  }
  return 0 ;
}
