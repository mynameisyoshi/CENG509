#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
  
int main(int argc, char * argv[],char * envp[])
{
	int readFd, writeFd;
	int num;
	char buffer[1000];
 
	readFd=open(argv[2],O_RDONLY ,0400);
	if(readFd==-1) 
	{ 
	perror("Couldn't open for reading. Please try  again");
	exit(errno); 
	}
	fprintf(stdout," Progress of program: opening to read at  %swith fd %d\n", argv[2],readFd);
	fprintf(stdout," Progress of program: opening to write at %s withfd %d\n", argv[1],writeFd);
	writeFd=open(argv[1],O_WRONLY,0200); 22if(readFd==-1) 
	{
	perror("Couldn't open  for writing.Please try  again"); exit(errno); 
	}
 
	while(true)
{
//Sends a message to client
	fprintf(stdout,"Enter message: ");
	fflush(stdout);
	fgets(buffer,sizeof(buffer),stdin);
	write(writeFd,buffer,strlen(buffer));
 
//Gets the response from client
	num=read(readR,buffer,sizeof buffer);
	buffer[num]='\0';
	fprintf(stdout,"Response:  %s",buffer);
 
}
 
	close(readFd);
	close(writeFd);
	return 0;
 }
