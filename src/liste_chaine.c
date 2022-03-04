#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/liste_chaine.h"

Cellule* alloue_cellule(char* mot) {
    Cellule* cel;
    cel = malloc(sizeof(Cellule));
    if (cel != NULL) {
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
    if (*lst == NULL)
        return;
    
    libere_liste((*lst)->suivant);
    free(lst);
}

void affiche_liste(Liste lst) {
    if (lst == NULL)
        return;

    printf("%s\n", lst->mot);
    affiche_liste(lst->suivant);
}