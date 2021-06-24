// UDP Pinger

#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <ws2tcpip.h> 
//#include <sys/types.h> 
#include <winsock2.h> 
/*
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
*/

using namespace std ;

#define PORT	 12000

int main() {
	int sockfd, n;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr, cliaddr; 
	clock_t start, end ;
	
	// Create a UDP socket
	// Notice the use of SOCK_DGRAM for UDP packets
	// AF_INET = IPv4
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// bind unnecessary for client
	
	// establishes timeout value of exactly 1.0 seconds
	struct timeval timeout ;
	timeout.tv_sec = 1 ;
	timeout.tv_usec = 0 ;
	
	// sets timeout option for socket 
	setsockopt( sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof( timeout )) ;
	
	// using for loop to send 10 pings
	for( int i = 0; i < 10; i++ ){
		start = time( 0 ) ;
		
		// send msg to server
		sendto( sockfd, (const char*)buffer, strlen( buffer ), 0, (const struct sockaddr *)&servaddr, len ) ;
		
		// receive response from server
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
		
		end = time( 0 ) ;
		double elapsed = end - start ; // calculate elapsed time
		
		if( elapsed >= 1 ) {
			cout << "Timeout occured (" + to_string( elapsed ) + "seconds elapsed)" << endl ;
		}
		else {
			cout << "RTT: " + to_string( elapsed ) + "seconds" << endl ;
		}
	}
	
	return 0 ;
}