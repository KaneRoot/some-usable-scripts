
void erreur(char *s);
int open_sem(key_t cle);
/* recherche le semaphore cle
   retourne l'identificateur du semaphore >=0 ou -1 si erreur
*/
void P(int semid);
void V(int semid);

/*-----------------------------------------------------------*/

int creat_sem(key_t cle, int val);
/* creation du semaphore cle ayant comme valeur initiale val
   retourne un identificateur de semaphore >=0 ou -1 si erreur
*/

/*--------------------------------------------------------------*/

int del_sem(key_t cle);
/* destruction du semaphore cle 
   retourne:
	0 si la destruction du semaphore s est effectuee correctement
       -1 si erreur
*/

