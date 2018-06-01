TARGET = sterling.out
LIBS = -lm -lncurses
CC = gcc
CFLAGS = -g -Wall

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^
