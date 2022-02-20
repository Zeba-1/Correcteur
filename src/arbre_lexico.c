#include <stdlib.h>
#include <stdio.h>

#include "include/arbre_lexico.h"

Noeud* alloue_noeud(char c) {
    Noeud* n = malloc(sizeof(Noeud));
    if (n != NULL) {
        n->c = c;
        n->f = NULL;
        n->fg = NULL;
        n->fd = NULL;
    }
    return n;
}

int ajoute_mot(char* mot, ArbreLexico* arbre) {
    if (*arbre == NULL) {
        Noeud* courant = alloue_noeud(*mot);
        if (courant == NULL)
            return 0;
        if (*mot != '\0')
            ajoute_mot(mot+1, &courant->f);
        *arbre = courant;
        return 1;
    }

    if ((*arbre)->c == *mot) {
        return ajoute_mot(mot+1, &(*arbre)->f);
    }
    if ((*arbre)->c == '\0' || (*arbre)->c < *mot) {
        return ajoute_mot(mot, &(*arbre)->fd);
    }
    if ((*arbre)->c > *mot) {
        return ajoute_mot(mot, &(*arbre)->fg);
    }
    return 0;
}
