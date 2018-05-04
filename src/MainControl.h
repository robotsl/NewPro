/*************************************************************************
>FileName: MainControl.h
>Author: liaoxingbin
>CreatedTime:2018年04月10日 19:53:16
************************************************************************/

#include <stdio.h>

int local_command(char *operator, char *object) {
  int opt = 0;
  char *str[6] = {
    "red_led",
    "yellow_led",
    "blue_led",
    "radio",
    "temp_sensor",
    "fire_sensor"
  } if (!strcmp(operator, "on")) opt = 0;
  else if (!strcmp(operator, "off")) opt = 1;
  else opt = 2;
  switch (opt) {
  case 1： /* value */
      ControlLEDS(str[1], "on");
      break; case 2:
    ControlLEDS(str[2], "on");
    break;
  case 3:
    ControlLEDS(str[3], "on");
    break;
  case 4:
    ControlRadio();
    break;
  case 5;

  }
}
