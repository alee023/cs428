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
#include <chrono>

using namespace std ;

#define PORT	 12000

int main() {
	int sockfd, n;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr, cliaddr; 
	
	// Create a UDP socket
	// Notice the use of SOCK_DGRAM for UDP packets
	// AF_INET = IPv4
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// bind unnecessary for client
	
	// establishes timeout value of exactly 1.0 seconds
	DWORD timeout = 2000 ;
	
	// sets timeout option for socket 
	setsockopt( sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof( timeout )) ;
	
	// using for loop to send 10 pings
	for( int i = 0; i < 10; i++ ){
		auto start = std::chrono::steady_clock::now();
		// cout << "start time: " + to_string( start ) << endl ;
		
		// send msg to server
		sendto( sockfd, (const char*)buffer, strlen( buffer ), 0, (const struct sockaddr *)&servaddr, len ) ;
		
		// receive response from server
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), MSG_WAITALL, ( struct sockaddr *) &servaddr, &len);
		
		auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> diff = end - start ;

		// cout << "end time: " + to_string( end ) << endl ;
		
		if( diff.count()/1000.0 > 1.0 ) {
			cout << to_string( i ) + ": Timeout occured (" << diff.count() << " milliseconds elapsed)" << endl ;
		}
		else {
			cout << to_string( i ) + ": RTT: " << diff.count() << " milliseconds\n" ;
		}
	}
	
	close( sockfd ) ;
	return 0 ;
}