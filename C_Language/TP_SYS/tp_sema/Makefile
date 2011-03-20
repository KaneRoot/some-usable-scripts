CC = gcc
CONS = consommateur
PROD = producteur
CFLAGS = -Wall -g 
COMMUN = sema.o global.o 
all: $(COMMUN) consommateur.o producteur.o
		$(CC) consommateur.o -o $(CONS) -std=c99 sema.o
		$(CC) producteur.o -o $(PROD) sema.o

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

