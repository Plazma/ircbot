CC          := gcc
INCLUDES    := -I ./libircclient/include
CFLAGS      := -Wall -o ircbot
LFLAGS      := -L ./libircclient/src -lircclient
SOURCES     := main.c

all: ircbot

ircbot:
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) $(LFLAGS)

clean:
	rm -rf ircbot *.o
