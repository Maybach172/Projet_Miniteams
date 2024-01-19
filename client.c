#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void parser(int *parsed_message, char *message, int len)
{
	for (int i = 0; i < len; i++)
	{
		parsed_message[i] = message[i];
	}
	parsed_message[len] = len;
	parsed_message[len + 1] = '\0';

}

int arg_check(int argc)
{
	return argc == 3;
}

int main(int argc, char const *argv[])
{
	if (!arg_check(argc))
	{
		fprintf(stderr, "wrong number of arguments\n");
		return 0;
	}

	int len = strlen(argv[2]);

	printf("%i\n", len);

	char message[len];
	
	if (len > 1000)
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

			if (!isascii(new_message[i]))
			{
				fprintf(stderr, "the character after %c is not an ASCII character\n", new_message[i-1]);
				break;
			}

			value.sival_int = new_message[i];
			
			if(sigqueue(pid, SIGUSR1, value) != 0)
			{
				fprintf(stderr, "message could not be send\n");
				break;
			}
			sleep(0.01);
		}
	}

	return 0;
}