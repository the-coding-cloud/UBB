#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#define SharedMemorySize 256
int main(int argc, char** argv)
{
	key_t key = 1234;
	int shared_memory = shmget(key, SharedMemorySize, IPC_CREAT | 0666);
	if(shared_memory < 0)
	{
		perror("Shared memory not created!\n");
		exit(1);
	}
	char* communication_pointer = shmat(shared_memory, NULL, 0);
	char* text_pointer = communication_pointer + 1;
	if(text_pointer == (char *) -1 )
	{
		perror("Text pointer is invalid!\n");
		exit(2);
	}
	int stop = 0;
	char* message = (char*)malloc(256 * sizeof(char));
	*communication_pointer = '+';
	//+ means that message can be sent
	//- means that message cannot be sent at the moment
	//* means that the session is over
	printf("Write 'exit' to leave.\n");
	printf("Also, don't forget to run the second program now.");
	printf("Please insert your text:");
	scanf("%s", message);
	while(stop == 0)
	{
		if(!strcmp(message, "exit"))
		{
			stop = 1;
			*communication_pointer = '*';
		}
		else
		{
			if(strlen(message) < SharedMemorySize-5)
			{	
				if(*communication_pointer == '+')
				{
					memcpy(text_pointer, message, strlen(message));
					*(text_pointer+strlen(message)) = 0;
					*communication_pointer = '-';
				}
				else
					printf("Something went wrong.\n");
			}
			while(*communication_pointer == '-')
                                sleep(1);
			printf("Your text contained %s vowels.\n", text_pointer);
			printf("Please insert your text:");
			scanf("%s", message);
			
		}



	}
	free(message);
	return 0;
}
