#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/liste_chaine.h"
#define MAX_MOT 100 /* longueur max d'un mot */

Cellule* alloue_cellule(char* mot) {
    Cellule* cel;
    cel = malloc(sizeof(Cellule));
    if (cel != NULL) {
        cel->mot = malloc(MAX_MOT);
        strcpy(cel->mot, mot);
        cel->suivant = NULL;
    }
    return cel;
}

int inserer_en_tete(Liste* lst, char* mot) {
    Cellule* nv_tete;
    nv_tete = alloue_cellule(mot);
    if (nv_tete == NULL)
        return 0;

    nv_tete->suivant = *lst;
    *lst = nv_tete;
    return 1;
}

void libere_liste(Liste* lst) {
    if ((*lst) == NULL)
        return;
    
    libere_liste(&(*lst)->suivant);
    free((*lst));
    *lst = NULL;
}

void affiche_liste(Liste lst) {
    while (lst != NULL) {
        printf("\t%s\n", lst->mot);
        lst = lst->suivant;
    }
}
