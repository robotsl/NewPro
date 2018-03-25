#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

typedef struct operate{
	char operator[10];
	char object[10];
}OP;

int main()
{
	int ret = 0;
	char ret[20] = " ";
	OP *op = (OP *)(malloc(sizeof(OP)));
	while (1)
	{
		ret = wake_string(ret);
		split(ret,op);
		ret = local_command(getid(op->operator),getid(op->object));
		bzero(op,sizeof(op));
		ret = 0;

	}
	return 0;
}
