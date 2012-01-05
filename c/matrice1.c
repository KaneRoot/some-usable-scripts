/* programme matrice1.c */
/* tableau de dimension 2 version STATIQUE */

#include <stdio.h>
#include <stdlib.h>
#define NB_LIGNES_MAX 10
#define NB_COLS_MAX 10

void lire_mat( int mat[NB_LIGNES_MAX][NB_COLS_MAX], int nbl, int nbc )
{
    // nbl, nbc: resp. nb de lignes et colonnes effectif	
    int i, j;
    for ( i = 0 ; i < nbl ; i++ ) {
        for ( j = 0 ; j < nbc ; j++ ) {
            printf( "[%d][%d] : ", i, j );
            scanf( "%d", &mat[i][j] );
        }
    }
}

void affich_mat( int mat[NB_LIGNES_MAX][NB_COLS_MAX], int nbl, int nbc )
{
    // nbl, nbc: resp. nb de lignes et colonnes effectif	
    int i, j;
    printf( "     " );
    for ( i = 0 ; i < nbc ; i++ ) 
        printf( " %4d", i ); 
    printf( "\n     " );
    for ( i = 0 ; i < nbc ; i++ ) 
        printf( "-----" ); 
    printf( "\n" );
		
    for ( i = 0 ; i < nbl ; i++ ) {		
        printf( " %2d |", i );	
        for ( j = 0 ; j < nbc ; j++ ) {
            printf( " %4d", mat[i][j] );
        }
        printf( "\n" );
    }
    printf( "\n" );
}

main()
{ int t[NB_LIGNES_MAX][NB_COLS_MAX];
  int n,m ;
  printf("Nb de lignes ? "); scanf("%d", &n);
  printf("Nb de colonnes ? "); scanf("%d", &m);
  if ( n > NB_LIGNES_MAX || m > NB_COLS_MAX) {
      puts("erreur, nombre depassant la taille tableau");
      exit(1);
  }
  lire_mat(t,n,m);	
  affich_mat(t, n,m) ;
  
}

