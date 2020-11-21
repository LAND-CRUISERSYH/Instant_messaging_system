CXX = g++

all:ClientMain.cpp ServerMain.cpp Server.o Client.o
	$(CXX) ServerMain.cpp Server.o -o chatroom_server
	$(CXX) ClientMain.cpp Client.o -o chatroom_client
Server.o:Server.cpp Server.h Common.h
	$(CXX) -c Server.cpp
Client.o:Client.cpp Client.h Common.h
	$(CXX) -c Client.cpp

clean:
	rm -f *.o chatroom_server chatroom_client
