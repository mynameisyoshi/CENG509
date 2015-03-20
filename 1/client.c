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
int num;//to store number of bytes
  
 
char buffer[5000];

writeFd=open(argv[1],O_WRONLY,0200);

if(writeFd==-1) { perror("Couldn't Open for writing"); exit(errno); }

readFd=open(argv[2],O_RDONLY,0400);
if(readFd==-1) { perror("Couldnt open for reading"); exit(errno); }
   
   
while(true)
{

num=read(readFd,buffer,sizeof buffer);
buffer[num]='\0';
fprintf(stdout,"New message received from Server:  %s",buffer);
 

fprintf(stdout,"Reply: ");
fflush(stdout);
fgets(buffer,sizeof(buffer),stdin);
write(writeFd,buffer,strlen(buffer));

}
 
close(readFd);
close(writeFd);
return 0;
}