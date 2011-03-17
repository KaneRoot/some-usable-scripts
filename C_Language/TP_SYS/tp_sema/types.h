#include "constantes.h"

typedef struct msg_s
{
	char c;	// caractère émi
	int idp; // indice du producteur
} MSG;
typedef struct memp_s // Structure de sémaphore
{
	int max_prod;
	int tete;
	int queue;
	int tpa[MAX_PROD]; // -1 de tpa[i] alors libre, 0 sinon
	MSG f[MAX_BUF]; // Buffer stockant les caractères émis par les différents producteurs
} MEMP;

// Arrêt sur ^D du consommateur, arrêt de tous les IPC et on s'arrête
//				du producteur, arrêt des IPC, met à jour le tableau à -1 sur sa case et il s'arrête

