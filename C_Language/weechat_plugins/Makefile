#	$@ : nom de la cible
#	$< : nom de la première dépendance
#	$^ : liste des dépendances
#	$? : liste des dépendances plus récentes que la cible
#	$* : nom du fichier sans suffixe

CC=gcc
CFLAGS = -Wall -fPIC
EXEC = currentsong

all: $(EXEC)

$(EXEC) : $(EXEC).o 
	$(CC) -fPIC -shared -o lib$(EXEC).so $<
			   
%.o : %.c 
	$(CC) $(CFLAGS) -c $<  

clean:
	@rm -rf *.o *.out
mrproper: clean
	@rm lib$(EXEC).so 2>/dev/null
