#SOURCE= vlc
#CFLAGS=$(shell pkg-config --libs vlc)
#
#all: compilationvlc
#
#compilationvlc:
#	$(CC) $(SOURCE).c -o $(SOURCE) $(CFLAGS)

CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=
CFILES=$(wildcard *.c) # CFILES => recompiles everything on a C file change
EXEC=$(basename $(wildcard *.c))
#SOURCES=$(wildcard *.c)
TESTS=$(addsuffix .test, $(EXEC))

all: $(SOURCES) $(EXEC)

$(EXEC): $(CFILES)
	$(CC) $(LDFLAGS) $@.c -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@-rm $(EXEC)

# to test a binary "prog" : make prog.test

$(TESTS):
	valgrind --leak-check=full -v --track-origins=yes ./$(basename $@)

test: all $(TESTS)
