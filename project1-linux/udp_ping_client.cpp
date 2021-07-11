// UDP Pinger

#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
// #include <ws2tcpip.h> 
#include <sys/types.h> 
//#include <winsock2.h> 

#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <chrono>

using namespace std ;

#define PORT	 12000

int main() {
	int sockfd, n;
	socklen_t len ;
	char buffer[1024];
	struct sockaddr_in servaddr, cliaddr; 
	// clock_t start, end ;
	
	// Create a UDP socket
	// Notice the use of SOCK_DGRAM for UDP packets
	// AF_INET = IPv4
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// bind unnecessary for client
	// Fill server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number
	
	// establishes timeout value of exactly 1.0 seconds
	struct timeval timeout ;
	timeout.tv_sec = 1 ;
	timeout.tv_usec = 0 ;
	
	// sets timeout option for socket 
	setsockopt( sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof( timeout )) ;
	
	// using for loop to send 10 pings
	for( int i = 0; i < 10; i++ ){
		// start time
		auto start = std::chrono::steady_clock::now();		
		// cout << "start time: " + to_string( start ) << endl ;
		
		// send msg to server
		sendto( sockfd, (const char*)buffer, sizeof( buffer ), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof( servaddr )) ;
		
		// receive response from server
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		
		// end time
		auto end = std::chrono::steady_clock::now();
       	std::chrono::duration<double, std::milli> diff = end - start ;	// get the time in ms
	
		if( diff.count()/1000.0 >= 1.0 ) { // convert millisecond time to seconds, then compare
			cout << to_string( i ) + ": Timeout occured (" << diff.count() << " milliseconds elapsed)" << endl ;
		}
		else { // does not exceed timeout 
			cout << to_string( i ) + ": RTT: " << diff.count() << " milliseconds\n" ;
		}
	}
	
	close( sockfd ) ;
	return 0 ;
}