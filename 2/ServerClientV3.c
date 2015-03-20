#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/times.h>
#include <sys/time.h>

#define PORT "40064"  // the port users will be connecting to

#define BACKLOG 10     // how many pending connections queue will hold

void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
	void hello();
    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    freeaddrinfo(servinfo);

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("server: got connection from %s\n", s);

        if (!fork()) { 
		char buffer[1000],buffer2[1000];
		char againMsg[]="Enter another message\n";
             do {
		size_t nBytes;
		close(sockfd); 
		nBytes=recv(new_fd,buffer,sizeof buffer,0); 
		if(nBytes<0) { perror("Problem in receive"); exit(1); }
		buffer[nBytes-2]='\0'; 
		fprintf(stdout,"I got a message: %s\n",buffer);
                if(strcasecmp(buffer,"Quit")==0) break; 
		sprintf(buffer2,"Your message '%s' was %d bytes long.\n",buffer,nBytes-1);            
		fprintf(stdout,"Sending this to client: %s\n",buffer2);
		if (send(new_fd,buffer2,strlen(buffer2), 0) == -1)
		    perror("send");
		send(new_fd,againMsg,strlen(againMsg),0);

		struct timeval currtime;
		struct tm* current;
		char times_string[50];
	
		gettimeofday(&current, NULL);
		current = localtime(&currtime.tv_sec);
		strftime(times_string, sizeof(times_string), "%H:%M:%S", current);
		fprintf(stdout,"Current time of day: %s\n", times_string);



		} //fork loop
               while(true); 
            close(new_fd);
            exit(0);
        } //while loop
        close(new_fd); 
    }
/*
void hello(){

	struct timeval currtime;
	struct tm* current;
	char times_string[50];

	gettimeofday(&current, NULL);
	current = localtime(&currtime.tv_sec);
	strftime(times_string, sizeof(times_string), "%H:%M:%S", current);
	fprintf(stdout,"Current time of day: %s\n", times_string);
}*/ 

    return 0;
}
