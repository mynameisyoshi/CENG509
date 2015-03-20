#include <stdio.h>
#include <netdb.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void displayServiceInfo(struct servent *s)
{
	char * alias;
	fprintf(stdout,"name:  %s   num: %d aliases:  %s ", s->s_name,htons(s->s_port),*s->s_aliases);
	//loop over the list of aliass
	if(s->s_aliases) //In case there are no aliases, this pointer is null
		//In fact all protocols (at present) have at least 1 alias
		for(alias=*s->s_aliases;alias&&*alias;alias++) fprintf(stdout,"%s;",alias);
	fprintf(stdout,"\n");
}

void getServByAnyName(char *serviceName)
{
	struct servent * service_entry=getservbyname(serviceName,NULL);
	if(service_entry) displayServiceInfo(service_entry);
	else  fprintf(stderr,"service %s not found\n", serviceName);
}


int main(int argc, char * argv[],char * envp[])
{
	//Display all protocol entrie
	struct servent * service_entry;
	char sname[20];
	char sport[10];
	setservent(true); //rewind to the start of /etc/protocols
	while(service_entry=getservent())
		displayServiceInfo(service_entry);

	//Part 2:  Get aliases by name and by number
	fprintf(stdout,"Enter a service  name and then another service number.\n");
	fprintf(stdout,"This demonstrates the lookup capability of getprotobyname\n");
	fprintf(stdout,"Enter 'bye' to quit\n");  
	while(true)
	{
		fprintf(stdout,"Enter a service name: ");
		fflush(stdout);
		fgets(sname,sizeof sname,stdin);
		sname[strlen(sname)-1]='\0';  //strip off newline character
		if(strcasecmp(sname,"bye")==0) break;

		getServByAnyName(sname);
		/*	service_entry=getservbyname(sname,NULL);
			if(service_entry) displayServiceInfo(service_entry);
			else  fprintf(stderr,"service %s not found\n", sname);
		 */
		fprintf(stdout,"Enter a service number: ");
		fflush(stdout);
		fgets(sport,sizeof sport,stdin);
		service_entry=getservbyport(htons(atoi(sport)),NULL);

		if(service_entry) displayServiceInfo(service_entry);
		else fprintf(stderr,"Service #%d not found\n",sport);// */
	}

	fprintf(stdout,"Thanks for using this demo\n");

	endservent();  //close the file
	return 0;

}
