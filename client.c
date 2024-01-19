#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void parser(int *parsed_message, char *message, int len)
{
	for (int i = 0; i < len; i++)
	{
		parsed_message[i] = message[i];
	}
	parsed_message[len] = len;
	parsed_message[len + 1] = '\0';

}


int main(int argc, char const *argv[])
{
	int len = strlen(argv[2]);

	printf("%i\n", len);

	char message[len];
	
	if (len >= 1000)
	{
    	fprintf(stderr, "message is too long!\n");
    	printf("HERE\n");
    }
    else
    {
    	strcpy(message, argv[2]);

		int new_message[len + 2];
	
		parser(new_message, message, len);
	
		for (int i = 0; i < len + 2; i++)
		{
			union sigval value;
			int pid = atoi(argv[1]);
	
			value.sival_int = new_message[i];
			if(sigqueue(pid, SIGUSR1, value) != 0)
				printf("Message failed\n");
			sleep(0.01);
		}
	}

	return 0;
}