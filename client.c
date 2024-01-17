#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>




int main(int argc, char const *argv[])
{
	char message[] = "Hello World!";

	union sigval value;
	int pid = atoi(argv[1]);

	value.sival_int = 42;

	if(sigqueue(pid, SIGUSR1, value) == 0)
		printf("Message send successfully !\n");
	else
		printf("Message failed\n");
	
	return 0;
}