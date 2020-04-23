#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#define maxinput 20
int main(int argc, char** argv) 
{ 
    int fifo; 
    char* fifo_file = "/tmp/myfifo"; 
 
    mkfifo(fifo_file, 0666); 
  
    char input_command[maxinput]; 
    while (1) 
    { 
       	//write only
        fifo = open(fifo_file, O_WRONLY);  
        fgets(input_command, maxinput, stdin); 
  
        write(fifo, input_command, strlen(input_command)+1); 
        close(fifo); 

        //reads the needed data
        fifo = open(fifo_file, O_RDONLY); 
  
        // Read from FIFO 
	char c;
	int code = 1;
	read(fifo, &c, sizeof(char));
        while(c != 0 || code == -1)
	{
		printf("%c", c);
		code = read(fifo, &c, sizeof(char));
	}
	close(fifo); 
    } 
    return 0; 
} 
