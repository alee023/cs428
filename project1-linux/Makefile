all : udp_ping_server udp_ping_client

udp_ping_server:	udp_ping_server.o
	g++ -o udp_ping_server udp_ping_server.cpp 

udp_ping_client:	udp_ping_client.o
	g++ -o udp_ping_client udp_ping_client.cpp 

clean :
	rm -rf *.o udp_ping_server udp_ping_client