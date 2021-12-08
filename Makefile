CC = g++
CFLAGS = -g -Wall -std=c++2a

TARGET = clox

default: $(TARGET)

$(TARGET): main.o token.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o token.o

main.o: main.cpp token.h
	$(CC) $(CFLAGS) -c main.cpp

token.o: token.cpp token.h
	$(CC) $(CFLAGS) -c token.cpp

clean:
	$(RM) $(TARGET) *.o *~
