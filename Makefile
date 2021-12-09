CC = g++
CFLAGS = -g -Wall -std=c++2a

TARGET = clox

default: $(TARGET)

$(TARGET): main.o token.o scanner.o util.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o token.o scanner.o util.o

main.o: main.cpp token.h
	$(CC) $(CFLAGS) -c main.cpp

scanner.o: scanner.cpp scanner.h token.h util.h
	$(CC) $(CFLAGS) -c scanner.cpp

token.o: token.cpp token.h
	$(CC) $(CFLAGS) -c token.cpp

util.o: util.cpp util.h
	$(CC) $(CFLAGS) -c util.cpp

clean:
	$(RM) $(TARGET) *.o *~
