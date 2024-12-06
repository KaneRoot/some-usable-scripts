CC ?= clang
CFLAGS ?= -Wall -Wextra -std=c11

all: compilation

compilation: by-line

by-line: by-line.c
	$(Q)$(CC) -o by-line $(CFLAGS) $(LDFLAGS) $^
