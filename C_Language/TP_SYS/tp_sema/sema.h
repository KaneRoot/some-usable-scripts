#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

void erreur(char *s);
int creat_sem(key_t cle, ushort val);
int del_sem(key_t cle);
int open_sem(key_t cle);
void P(int semid);
void V(int semid);

