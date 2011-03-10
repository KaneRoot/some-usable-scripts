void erreur(char *s);
int creat_sem(key_t cle,ushort val);
int del_sem(key_t cle);
int open_sem(key_t cle);
void P(int semid);
void V(int semid);

