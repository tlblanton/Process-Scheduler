CC = g++ -std=c++11

CFLAGS = -c -Wall

all: myscheduler

myscheduler: main.o Process.o DArray.o
	$(CC) main.o Process.o DArray.o -o myscheduler

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Process.o: Process.cpp
	$(CC) $(CFLAGS) Process.cpp

DArray.o: DArray.cpp
	$(CC) $(CFLAGS) DArray.cpp


clean:
	rm *o myscheduler
