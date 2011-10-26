#	$@ : nom de la cible
#	$< : nom de la première dépendance
#	$^ : liste des dépendances
#	$? : liste des dépendances plus récentes que la cible
#	$* : nom du fichier sans suffixe

CC=gcc
CFLAGS = -Wall -fPIC
EXEC = currentsong

gcc -fPIC -Wall -c toto.c
gcc -shared -fPIC -o libtoto.so toto.o

all: $(EXEC)

$(EXEC) : $(EXEC).o 
	$(CC) -o lib$(EXEC).so -shared $<

%.o : %.c 
	$(CC) -c $< $(OPTIONS) 

clean:
	@rm -rf *.o *.out
mrproper: clean
	@rm lib$(EXEC).so 2>/dev/null
