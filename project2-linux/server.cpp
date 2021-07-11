#include <iostream>
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
	int sockfd ;
	int client1, client2 ;
	socklen_t len ;
	char msg1[1024];
	char msg2[1024];
	char greeting[ 1024 ] = "Connected to server." ;
	char response[ 1024 ] ;
	struct sockaddr_in servaddr, cli1Addr, cli2Addr ; 
	len1 = sizeof( cli1Addr ) ;
	len2 = sizeof( cli2Addr ) ;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	// Fill server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number
	
	// Bind the socket with the server address 
	bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	
	listen( sockfd, 5 ) ;
	
	// accepting connections for each client socket
	client1 = accept( sockfd, (struct sockaddr *)&cli1Addr, &len1 ) ;
	client2 = accept( sockfd, (struct sockaddr *)&cli2Addr, &len2 ) ;
	
	// send initial msg to both clients indicating successful connection
	send( client1, greeting, sizeof( greeting ), 0 ) ;
	send( client2, greeting, sizeof( greeting ), 0 ) ;
	
	// receive messages from each client
	recv( client1, &msg1, sizeof( msg1 )) ;
	recv( client2, &msg2, sizeof( msg2 )) ;
	
	// compare first string and set appropriate acknowledgement
	if( strcmp( msg1, "Client X: Alice" ) == 0 ) {
		response = "X: Alice received before Y: Bob" ;
	}
	else {
		response = "Y: Bob received before X: Alice" ;
	}
	
	// send the acknowledgement
	send( client1, response, sizeof( response ), 0 ) ;
	send( client2, response, sizeof( response ), 0 ) ;
	
	// close socket
	close( sockfd ) ;
	return 0 ;
}