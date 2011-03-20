CC = gcc
CONS = consommateur
PROD = producteur
CFLAGS = -lncurses -Wall -g -std=c99 -D_XOPEN_SOURCE -D_SVID_SOURCE
COMMUN = sema.o global.o 
all: $(COMMUN) consommateur.o producteur.o
		$(CC) consommateur.o -o $(CONS) sema.o $(CFLAGS)
		$(CC) producteur.o -o $(PROD) sema.o $(CFLAGS)

sema.o : sema.c sema.h
	$(CC) -o $@ -c $< $(CFLAGS)

global.o : global.c
	$(CC) -o $@ -c $< $(CFLAGS)

consommateur.o : consommateur.c consommateur.h constantes.h types.h sema.h
	$(CC) -o $@ -c $< $(CFLAGS)

producteur.o : producteur.c producteur.h constantes.h types.h sema.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf *.o *.out
mrproper: clean
	@rm $(PROD) $(CONS) 2>/dev/null

