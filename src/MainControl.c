#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>



int main()
{
	pid_t pid = 0;
	while (1)
	{
		while ((pid = fork()) < 0)
			;
		if (pid == 0)
		{
			execl("./test","test","green","on",NULL);
		}
		else if (pid > 0)
		{
			sleep(10);
			waitpid(pid,NULL,0);
			execl("./test","test","green","off",NULL);
		}
	}
	return 0;
}
