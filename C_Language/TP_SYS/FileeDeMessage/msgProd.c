/* msgProd.c.c

works with msgCons.c

Create a message queue et saisit un message et un type et envoie le message
*/

/* Includes */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>

/* Defines */
#define cle 17

/* Global variables */
int msqid;

#define TAILLE_NOM 15


typedef struct msgbuf_EXD
{
    long mtype;
    char text  [30];
} MSGP;;


int main()
{
   /* Create the message queue */
   msqid = msgget(cle, IPC_CREAT|IPC_EXCL|0660);
   
   /* Fill in the structure */
   MSGP m1,m2,m3;
   int type;
   char mess[20 ];
   
   
   printf("Taille de la structure MSGP = %d\n ", sizeof(MSGP));
   
   while( 1)
   {   
        printf("\nSaisir type destinataire ( 1-5 ) ");
        scanf("%d",&m1.mtype);  
        printf("\nSaisir un message) ");
        scanf("%s", m1.text);
        
        /* Send the message */
        msgsnd(msqid, &m1, sizeof(MSGP),0);

   }
   return 0;
}

    
