CC          := gcc
INCLUDES    := -I ./libircclient/include $(shell pkg-config --cflags glib-2.0)
CFLAGS      := -Wall -o ircbot
LFLAGS      := -L ./libircclient/src -lircclient $(shell pkg-config --libs glib-2.0)
SOURCES     := main.c

all: ircbot

ircbot:
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) $(LFLAGS)

clean:
	rm -rf ircbot *.o
