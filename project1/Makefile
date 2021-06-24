all : udp_ping_server udp_ping_client

udp_ping_server:	udp_ping_server.o
	g++ -o udp_ping_server udp_ping_server.cpp -lws2_32

udp_ping_client:	udp_ping_client.o
	g++ -o udp_ping_client udp_ping_client.cpp -lws2_32

clean :
	rm -rf *.o udp_ping_server udp_ping_client