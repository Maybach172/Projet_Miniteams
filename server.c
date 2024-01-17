#include <signal.h>
#include <unistd.h>
#include <stdio.h>


void startup()
{
	printf("Miniteams starting...\n");
	printf("My PID is %i\n", getpid());
	printf("Waiting for new messages\n");
}



void sig_handler(int sig, siginfo_t* info, void* vp)
{
	printf("received: %i\n", info->si_value.sival_int);
}


int main(int argc, char const *argv[])
{
	startup();
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while(1)
	{
		sleep(10);
	}
	return 0;
}

