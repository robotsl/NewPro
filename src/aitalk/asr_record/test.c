#include "formats.h"
#include "linuxrec.h"
#include "speech_recognizer.h"
#include <stdio.h>
int main()
{
	char *str = "\0";
	str = retString(str);
	if (str == NULL)
	{
		printf("error listening\n");
		return -1;
	}
	else
   	{
		printf("the result is:%s \n",str);
	}
	return 0;
}
