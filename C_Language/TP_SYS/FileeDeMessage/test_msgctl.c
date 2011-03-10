/* fichier test_msgctl.c */
/*
* le programme recupere l'identificateur d'une file existante (creee
* avec test_msgget.c) et affiche la structure msqid_ds associee a la file
*/
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLE 123
main()
{
struct msqid_ds buf ;
char *path = "nom2_de_fichier_existant" ;
int msqid ;
/* recuperation de l'identificateur de la file de messages de cle 123 */
if (( msqid = msgget(ftok(path,(key_t)CLE),0)) == -1 ) {
perror ("Erreur msgget()") ;
exit(1) ;
}
/* on recupere dans la structure buf les parametres de al file */
if (msgctl(msqid,IPC_STAT,&buf) == -1){
perror("Erreur msgctl()") ;
exit(1) ;
}
else
{
printf("id de la file de messages : %d\n",msqid) ;
printf("id du proprietaire : %d\n",buf.msg_perm.uid) ;
printf("id du groupe du proprietaire : %d\n",buf.msg_perm.gid) ;
printf("id du createur : %d\n",buf.msg_perm.cuid) ;
printf("id du groupe du createur : %d\n",buf.msg_perm.cgid) ;
printf("droits d'acces : %d\n",buf.msg_perm.mode) ;
printf("nb courant d'octets dans la file : %d\n",buf.msg_cbytes) ;
printf("nb de messages dans la file : %d\n",buf.msg_qnum) ;
printf("nb maximal d'octets de la file : %d\n",buf.msg_qbytes) ;
printf("pid du dernier ecrivain : %d\n",buf.msg_lspid) ;
printf("pid du dernier lecteur : %d\n",buf.msg_lrpid) ;
printf("date de la derniere ecriture : %s\n",ctime(&buf.msg_stime)) ;
printf("date de la derniere lecture : %s\n",ctime(&buf.msg_rtime)) ;
printf("date du dernier changement : %s\n",ctime(&buf.msg_ctime)) ;
}
}