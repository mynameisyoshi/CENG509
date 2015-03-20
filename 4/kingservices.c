#include <stdio.h>
#include <netdb.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void displayProtocolInfo(struct protoent *p)
{
    char ** alias;
    fprintf(stdout,"name:  %s   num: %d aliases: ", p->p_name, p->p_proto);
    //loop over the list of aliases
    if(p->p_aliases) //In case there are no aliases, this pointer is null
                     //In fact all protocols (at present) have at least 1 alias
        for(alias=p->p_aliases;*alias;alias++) fprintf(stdout,"%s;",*alias);
    fprintf(stdout,"\n");
  }

int main(int argc, char * argv[],char * envp[])
{
  //Display all protocol entries
  struct protoent * protocol_entry;
  char pname[20];
  char pnum[10];
  setprotoent(true); //rewind to the start of /etc/protocols
  while(protocol_entry=getprotoent())
     displayProtocolInfo(protocol_entry);
     
  //Part 2:  Get aliases by name and by number
  fprintf(stdout,"Enter a protocol  name and then another protocol number.\n");
  fprintf(stdout,"This demonstrates the lookup capability of getprotobyname\n");
  fprintf(stdout,"Enter 'bye' to quit\n");  
  while(true)
  {
    fprintf(stdout,"Enter a protocol name: ");
    fflush(stdout);
    fgets(pname,sizeof pname,stdin);
    pname[strlen(pname)-1]='\0';  //strip off newline character

    if(strcasecmp(pname,"bye")==0) break;
    protocol_entry=getprotobyname(pname);
    if(protocol_entry) displayProtocolInfo(protocol_entry);
        else  fprintf(stderr,"Protocol %s not found\n", pname);

    fprintf(stdout,"Enter a protocol number: ");
    fflush(stdout);
    fgets(pnum,sizeof pnum,stdin);
    protocol_entry=getprotobynumber(atoi(pnum));
    if(protocol_entry) displayProtocolInfo(protocol_entry);
        else fprintf(stderr,"Protocol #%d not found\n",atoi(pnum));
    }

   fprintf(stdout,"Thanks for using this demo\n");

   endprotoent();  //close the file
  return 0;
  }
