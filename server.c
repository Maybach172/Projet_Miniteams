#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int buffer[251];

void startup()
{
	printf("Miniteams starting...\n");
	printf("My PID is %i\n", getpid());
	printf("Waiting for new messages\n");
	buffer[250] = -1;
}

void parser(int len)
{
	printf("HERE\n");
	printf("%i\n", len);
	int i = 0;
	char message[len];
	for (int i = 0; i < len; ++i)
	{
		message[i] = buffer[i];
		printf("%c\n", message[i]);
	}

	printf("%s\n", message);
}

void sig_handler(int sig, siginfo_t* info, void* vp)
{
	printf("received: %i\n", info->si_value.sival_int);

	int character = info->si_value.sival_int;

	if (*buffer != -1)
		if (character != '\0')
		{
			*buffer = character;
			printf("%i\n", *buffer);
			buffer+sizeof(int);
		}
		else
		{
			parser(*(buffer-(2 *sizeof(int))));
			buffer - (*(buffer) + 1) * sizeof(int);
		}
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
		sleep(10);
	}
	return 0;
}

