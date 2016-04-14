CC          := gcc
INCLUDES    := -I ../libircclient/include
CFLAGS      := -Wall -o ircbot $(shell pkg-config --cflags glib-2.0)
LFLAGS      := -L ../libircclient/src -lircclient $(shell pkg-config --libs glib-2.0)
SOURCES     := main.c

all: ircbot

ircbot: $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) $(LFLAGS)

clean:
	rm -rf ircbot *.o
