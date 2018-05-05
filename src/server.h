#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "./ControlTempSensor.h"

char *opt[6] = {
  "red_led",
  "yellow_led",
  "blue_led",
  "radio",
  "temp_sensor"
}

int command((int head,int operator)
{
  int ret = 0;
  switch (head) {
  case 1:
      ret = local_command(opt[1],operator==1?"off","on");
      break;
  case 2:
      ret = local_command(opt[2],operator==1?"off","on");
      break;
  case 3:
      ret = local_command(opt[3],operator==1?"off","on");
      break;
  case 4:
        ret = local_command(opt[4],operator==1?"off","on");
        break;
  case 5:
        ret = local_command(opt[5],operator==1?"off","on");
        break;
  case 7:
    // shutdown
    break;
    return ret;
  }
}
