all: rsa.exe

rsa.exe : rsa.o main.o
	g++ rsa.o main.o -o rsa.exe

rsa.o : rsa.cpp rsa.h
	g++ -c rsa.cpp

main.o : main.cpp
	g++ -c main.cpp