#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int *buffer;

void startup()
{
	printf("Miniteams starting...\n");
	printf("My PID is %i\n", getpid());
	printf("Waiting for new messages\n");
	buffer = malloc(1010 * sizeof *buffer);
}

void parser(int len)
{
	char message[len + 1];

	for (int i = 0; i < len + 1; i++)
	{
		message[i] = *(buffer + i);
	}

	message[len] = '\0';

	printf("%s \n", message);
}

void sig_handler(int sig, siginfo_t* info, void* vp)
{
	int character = info->si_value.sival_int;

	*buffer = character;

	if (*buffer == '\0')
	{
		int len = *(buffer - 1);
		buffer -= len + 1;
		parser(len);
		
	}	
	else
		buffer++;
}

int main(int argc, char const *argv[])
{
	startup();
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;

	sigaction(SIGUSR1, &sa, NULL);

	while(1)
	{
		pause();
	}

	free(buffer);
	return 0;
}

