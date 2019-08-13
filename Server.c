/*
 * UDP Server based on https://www.geeksforgeeks.org/udp-server-client-implementation-c/
 * Made edits based on assigment specifcations
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 5432 
#define MAXLINE 1024 

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *message;
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	int len, n; 
	n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len);
	buffer[n] = '\0'; 
    strcat(buffer, " - UDP Packet into Bar walks a\n");
	printf("Client : %s\n", buffer); 
	sendto(sockfd, (char *)buffer, strlen(buffer), 
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
			len); 
	 
	
	return 0; 
} 

