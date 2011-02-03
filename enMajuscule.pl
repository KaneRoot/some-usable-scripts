#!/usr/bin/perl -w
# communication par tube (fonction PIPE qui retourne 
# un descripteur pour lire et un 2ième our écrire)
# le fils envoie le résultat de ls -l
# le père récupère le résultat et le met en majuscules

use IO::Handle;
  # chargement du package contenant autoflush()
system("clear");

pipe ( ENTREE, SORTIE );
  # création du tube avec les 2 decripteurs
# pipe (d1, d2) :
# d1 : descripteur pour lire ce qui est en sortie du tube
# d2 : descripteur pour écrire (envoyer dans le tube)

SORTIE->autoflush(1);
 # pour rendre disponible immédiatement tout caractère contenu dans SORTIE

$pid = fork();
if ($pid == 0) { # proc. fils (PRODUCTEUR)
  # fermeture du tube en lecture
  close (ENTREE);

  open (COMMANDE, "ls -l |");
	while (<COMMANDE>)
		print SORTIE $_;
 
  close (COMMANDE);
  close (SORTIE);
}
else { # proc. père (CONSOMMATEUR)
  # fermeture du tube non-utilisé
  close (SORTIE);
  while (<ENTREE>) 
    print uc($_);
 
  close (ENTREE);
  exit(0);
}
