#include <stdio.h>
#include <stdlib.h>

int** lire_mat( int nbl, int nbc ) {

	int i,j;
	int **t;
	t = (int **) malloc(nbl * sizeof(int*));
	for(i=0;i<nbl;i++)
		t[i] = malloc(nbc * sizeof(int));
	for(i=0;i<nbl;i++){
		for(j=0;j<nbc;j++){
			printf("Ligne %2d Colonne %2d : ",i,j);
			scanf("%d", &t[i][j]);
		}
	}
	return t;
}

void affich_mat( int** mat, int nbl, int nbc ) {
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

void liberer(int** mat, int nbl, int nbc) {
	int i;
	for ( i = 0 ; i < nbl ; i++ ) 		
		if (nbc >0)
		free(mat[i]) ;
	if (nbl >0)
	free(mat) ;
}

main()
{ 
  int **t ;
  int n,m ;
  printf("Nb de lignes ? "); scanf("%d", &n);
  printf("Nb de colonnes ? "); scanf("%d", &m);
	
  t = lire_mat(n,m);  
    	
  affich_mat(t, n,m) ;

  liberer(t,n,m);  
  //  affich_mat(t, n,m) ;
  return 0;
}


