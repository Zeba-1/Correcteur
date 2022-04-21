#ifndef __ARBRE_BK__
#define __ARBRE_BK__

#include "liste_chaine.h"
#include "arbre_bk.h"

#define MAX_MOT 100

typedef struct noeudBK {
    char mot[MAX_MOT];
    int dl_pere;
    struct noeudBK* fils_g;
    struct noeudBK* frere_d;
}NoeudBK, *ArbreBK;

int inserer_dans_arbreBK(ArbreBK* a, char* mot);
void affiche_arbreBK(ArbreBK a);
void liberer_arbreBK(ArbreBK* a);
Liste recherche_bk(ArbreBK a, char* mot);

#endif
