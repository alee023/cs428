#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>

using namespace std ;

#define PORT	 12000

int main() {
	int sockfd, n;
	socklen_t len ;
	char response[1024];
	char msg[ 1024 ] = "Client Y: Bob" ;
	struct sockaddr_in servaddr ; 
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	// Fill server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number
	
	// handshake for TCP connections
	int connection = connect( sockfd, (const sockaddr*)&servaddr, sizeof( servaddr )) ;
	if( connection < 0 ) {
		cout << "Connection failed to establish." << endl ;
	}
	
	// receive initial response from server
	recv( sockfd, &response, sizeof( response ), 0 ) ;
	
	send( sockfd, msg, sizeof( msg ), 0 ) ;
	cout << "Sent: " + msg << endl ;
	recv( sockfd, &response, sizeof( response ), 0 ) ;
	cout << "Response: " + response << endl ;
	
	close( sockfd ) ;
	return 0 ;
}