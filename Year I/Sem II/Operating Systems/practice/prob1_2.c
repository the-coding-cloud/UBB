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
        char* message = (char*)malloc(256 * sizeof(char));
        //+ means that message can be sent
        //- means that message cannot be sent at the moment
        //* means that the session is over
	while(*communication_pointer != '*')
	{
		if(*communication_pointer == '-')
		{
			int sum = 0;
			char* i;
			for(i = text_pointer; *i != 0; i++)
			{
				if(*i == 'a' || *i == 'e' || *i == 'i' || *i == 'o' || *i == 'u')
					sum++;
			}
			i = text_pointer;
			while(sum>0)
			{
				*i = sum % 10 + '0';
				sum = sum / 10;
				i++;
			}
			*i = 0;
			*communication_pointer = '+';

		}
		if(*communication_pointer == '+')
		{
			sleep(1);
		}
	}
	free(message);
	return 0;
}
