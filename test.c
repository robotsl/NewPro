#include <stdio.h>
#include <string.h>

int main()
{
	char *desc = "温湿度传感器";
	printf("%d\n",strlen("红灯"));
	printf("%d\n",strncmp(desc,"温湿度传感器",18));
	return 0;
}
