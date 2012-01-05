/* travaille avec msgProd.c
lit les messages du type donne en parametre sur la ligne de cde
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

/* Defines */
#define cle 17

typedef struct msgbuf_EXD
{
    long type;
    char text  [30];
} MSGP;;


/* Global variables */
int msqid;

int main(int argc, char **argv)
{
    MSGP *m = (MSGP *)malloc (sizeof(MSGP));
    int type;
    
    if(argc!=2)
    {
        printf ( "usage : msgCons <type> " ) ;
        exit(-1);
    }

    type = atoi(argv[1]);
    
   msqid = msgget(cle, 0);  // ouverture file message
   
  // lecture
   
   
   while(msgrcv(msqid, m, sizeof(MSGP) ,type,1) != -1)
   {
   
   // decodage du message 
   
         printf("un message de type %d recu ( %s )\n", m->type, m->text);
   }
   return 0;
}
