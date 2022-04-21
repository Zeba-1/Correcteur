#ifndef __LISTE_CHAINE__
#define __LISTE_CHAINE__

typedef struct cellule {
    char* mot;
    struct cellule* suivant;
}Cellule, *Liste;

Cellule* alloue_cellule(char* mot);

int inserer_en_tete(Liste* lst, char* mot);

void libere_liste(Liste* lst);

void affiche_liste(Liste lst);

#endif
