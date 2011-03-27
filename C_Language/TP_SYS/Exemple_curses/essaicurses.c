/* 
 * RSc 
 * essaicurses.c : 
 * Illustration de l'utilisation de curses pour creer deux fenetres 
 * avec un cadre.
 */

#include <curses.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------------------------------
 *
 * creation_fenetre() : cree une fenetre de dialogue avec un cadre 
 *			sur n lignes debutant a la ligne d et comportant
 *			le texte t centre sur le bord superieur du cadre
 *			La fenetre occupe toutes les colonnes disponibles (COLS)
 * ENTREE:
 *		n: 	nombre de lignes du cadre
 *		d: 	ligne debut du cadre
 *		t: 	texte affiche dans le haut du cadre
 * RESULTAT:
 *		un pointeur sur la fenetre de dialogue creee
 *
 * REMARQUES:
 *	- 	Afin de dessiner un cadre, une fenetre 	speciale (cadre) 
 *		est creee et la fonction box() est appelee pour cette fenetre.
 *	-	La fenetre de dialogue (w) est creee a l'interieur du cadre.
 *	-	La fonction newwin() admet 4 parametres :
 *		- le nombre de lignes et le nombre de colonnes
 *		- la ligne debut et la colonne debut
 *-------------------------------------------------------------------*/

WINDOW *creation_fenetre(int n,int d,char *t)
{
    WINDOW *cadre ;			/* la fenetre pour le cadre */
    WINDOW *w ;			/* la fenetre de dialogue */
    
    /* creation du cadre */

    cadre= newwin(n,COLS,d,0) ;
    box(cadre,0,0) ;
    mvwprintw(cadre,0,COLS/2-strlen(t)/2,t) ;
    wrefresh(cadre) ;
    
    /* creation de la fenetre de dialogue */

    w= newwin(n-2,COLS-2,d+1,1) ;
    idlok(w,TRUE) ;
    scrollok(w,TRUE) ;	   /* mise en place du defilement (scrolling) */
    wclear(w) ;
    wrefresh(w) ;
    return w ;
}

/*-----------------------------------------------------------------------*/

main()
{
    const char CTRL_D = 4 ;

    WINDOW *f_haut, *f_bas ;	/* les 2 fenetres de dialogue */
    WINDOW *w ;
    char c ;
    int i ;

    initscr() ;			/* initialisation (obligatoire) de curses */
    noecho() ;			/* suppression de l'echo des caracteres tapes*/
    cbreak() ;			/* lecture non bufferisee */

/* creation des cadres et des fenetres de dialogue */

    f_haut= creation_fenetre(LINES/2,0,"EMISSION") ;
    f_bas = creation_fenetre(LINES/2, LINES/2 ,"RECEPTION") ;

/* lecture  et affichage des caracteres */

    while (( c= wgetch(f_bas)) != CTRL_D)
    {
        w= islower(c) ? f_haut : f_bas;  /* minuscules -> haut; autres -> bas */
        waddch(w,c) ;
        wrefresh(w) ; 
    }

    endwin() ;			/* remet l'ecran dans son etat initial 
				   endwin() est obligatoire pour terminer 
			 	   correctement un pg utilisant curses */
}
