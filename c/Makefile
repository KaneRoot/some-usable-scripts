# Directory to store compiled binaries.
BINDIR ?= /tmp/bin/

CC=clang
CFLAGS=-c -Wall -g
LDFLAGS=

CFILES=$(wildcard *.c)
EXEC=$(patsubst %.c,$(BINDIR)%,$(CFILES))
TESTS=$(addsuffix .test, $(patsubst %.c,%,$(CFILES)))

all: $(BINDIR) $(EXEC)

$(BINDIR):;         -mkdir -p $(BINDIR)
$(EXEC): $(CFILES); $(CC) $(LDFLAGS) $< -o $@
clean:;             @-rm $(EXEC)

# to test a binary "prog" : make prog.test
$(TESTS):; valgrind --leak-check=full -v --track-origins=yes $(BINDIR)$(basename $@)

test: all $(TESTS)
