all: server clientX clientY

server: server.o
	g++ -o server server.cpp

clientX: clientX.o
	g++ -o clientX clientX.cpp

clientY: clientY.o
	g++ -o clientY clientY.cpp
clean:
	rm -rf *.o clientX clientY server