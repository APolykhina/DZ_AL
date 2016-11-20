all: main.cpp server acceptor service factor
	g++	main.cpp server.o acceptor.o service.o factor.o -I/usr/local/include  -L/usr/local/lib  -lboost_system -lgmp -lgmpxx -std=c++1y

server: server.cpp server.h Acceptor.h
	g++ -c server.cpp -o server.o -I/usr/local/include -L/usr/local/lib -lboost_system -std=c++1y

acceptor: Acceptor.cpp Acceptor.h Service.h
	g++ -c Acceptor.cpp -o Acceptor.o -I/usr/local/include -L/usr/local/lib -lboost_system -std=c++1y

service: Service.cpp Service.h Factor.h
	g++ -c Service.cpp -o Service.o -I/usr/local/include -L/usr/local/lib -lboost_system -std=c++1y

factor: Factor.cpp Factor.h
	g++ -c Factor.cpp -o Factor.o  -I/usr/local/include -L/usr/local/lib -lgmp -lgmpxx -std=c++1y
test:
	./a.out

clean: 
	rm *.out *.o *.so
