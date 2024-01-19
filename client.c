#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void parser(int *parsed_message, char *message, size_t len)
{
	for (int i = 0; i < len; i++)
	{
		parsed_message[i] = message[i];
	}
	parsed_message[len-1] = len;

}


int main(int argc, char const *argv[])
{
	char message[] = "Hello World";

	size_t len = sizeof(message)/sizeof(char);
	
	int new_message[len + 1];
	printf("HERE\n");

	parser(new_message, message, len);
	printf("HERE 2\n");

	for (int i = 0; i < len + 1; i++)
	{
		union sigval value;
		int pid = atoi(argv[1]);

		value.sival_int = new_message[i];
		printf("%i\n", new_message[i]);
		if(sigqueue(pid, SIGUSR1, value) != 0)
			printf("Message failed\n");
		sleep(1);
	}

	return 0;
}