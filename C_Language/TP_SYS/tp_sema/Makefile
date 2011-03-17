C = gcc
SER = server
CONS = consommateur
PROD = producteur
CFLAGS = -Wall -g
COMMUN = sema.o global.o 
CONSOM = consommateur.o
PRODUCT = producteur.o
all: $(CONSOM) $(PRODUCT) 
		$(CC) $(CONSOM) -o $(CONS)
		$(CC) $(PRODUCT) -o $(SER)

consommateur.o : consommateur.h consommateur.c
	$(CC) -o $@ -c $< $(CFLAGS)

producteur.o : producteur.h producteur.c
	$(CC) -o $@ -c $< $(CFLAGS)

sema.o : sema.h sema.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf *.o *.out
mrproper: clean
	@rm $(PROD) $(CONS) 2>/dev/null

