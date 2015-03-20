#include <stdio.h>
#include <netdb.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void displayService(struct servent *s){
int i = 0;
printf("%s %d %s ", s->s_name, ntohs(s->s_port), s->s_proto);
   for ( i = 0; s->s_aliases[i] != 0; i++ )
      printf("%s ", s->s_aliases[i]);
   printf("\n");
}


int main(int argc, char * argv[],char * envp[])
{

	char sname[20];
	int sport[10];

//Part 1
struct servent *s;
struct servent * serv;
setservent(true);
while ((s = getservent()) != NULL)
displayService(s);

//Part 2 Get aliases by name and by number
  fprintf(stdout,"Enter a service  name and then another service number.\n");
  fprintf(stdout,"Enter 'bye' to quit\n");

	while(true)
{
	printf("Enter a service name");
	fgets(sname,sizeof sname,stdin);
	printf("Enter a service port");
	fgets(sport,sizeof sport,stdin);

	serv = getservbyname(sname, sport);
	if (serv == NULL) {printf("Service "%s" not found for protocol "%s"\n",sname, sport);}
	else { printf("Name: %-15s, Port: %5d, Protocol: %-6s\n", serv->s_name,ntohs(serv->s_port),serv->s_proto);}

	if(strcasecmp(sname, "bye")==0) break;
}


endservent();  }
