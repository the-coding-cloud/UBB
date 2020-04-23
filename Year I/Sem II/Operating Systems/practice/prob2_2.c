#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#define maxinput 20
#define maxoutput 1000
int main(int argc, char** argv) 
{ 
    int fifo; 
  
    char* fifo_file = "/tmp/myfifo"; 
    int code;	   
    mkfifo(fifo_file, 0666); 
    
    char command[maxinput]; 
    while (1) 
    {  
        fifo = open(fifo_file, O_RDONLY); 
        code = read(fifo, command, maxinput); 
        if(code==-1)
	{write(fifo, "error reading", 13i); }
	else
	{
	close(fifo);  
        fifo = open(fifo_file, O_WRONLY);  
    
    	FILE *fp;
	char output[maxoutput];
	printf("%s\n", command);
	fp = popen(command, "r");
	if(fp != NULL)
	{
	while( fgets(output, maxoutput, fp) != NULL)
	{
		write(fifo, output, strlen(output));
	}
	write(fifo, "\0", 1);
	pclose(fp);
	}
	close(fifo);
	}
     }
 
    return 0; 
} 
