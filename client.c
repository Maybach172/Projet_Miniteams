#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void parser(int *parsed_message, char *message, int len)
{
	//copy message in an integer array
	for (int i = 0; i < len; i++)	
	{
		parsed_message[i] = message[i];
	}
	//add message length and null character for message end detection
	parsed_message[len] = len;
	parsed_message[len + 1] = '\0';

}

//check the number of arguments
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

	int len = strlen(argv[2]);						//message length

	char message[len];								//initialize buffer for message argument
	
	if (len > 1000)
	{
    	fprintf(stderr, "message is too long!\n");
    	printf("HERE\n");
    }
    else
    {
    	strcpy(message, argv[2]);					//copy argument into buffer

		int new_message[len + 2];					//initialize integer buffer in order to send message
	
		parser(new_message, message, len);
	
		for (int i = 0; i < len + 2; i++)			//send message
		{
			union sigval value;						//initialize structure containing character value
			
			int pid = atoi(argv[1]);				//get pid passed as an argument

			if (!isascii(new_message[i]))			//check if character is ASCII or not
			{
				perror("one of the character after is not an ASCII character\n");
				break;
			}

			value.sival_int = new_message[i];		

			if(sigqueue(pid, SIGUSR1, value) != 0)	//send character ASCII value
			{
				perror("message could not be send\n");
				break;
			}
			sleep(0.01);							//wait to allow server to correctly receive the signal
		}
	}

	return 0;
}