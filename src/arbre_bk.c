#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "include/arbre_bk.h"
#include "include/levenshtein.h"
#include "include/liste_chaine.h"

int inserer_dans_arbreBK(ArbreBK* a, char* mot) {
    int i;
    int distance;
    ArbreBK* courant;

    if (*a == NULL) {
        *a = malloc(sizeof(NoeudBK));
        if (*a == NULL) /* si l'allocation echoue */
            return 0;

        (*a)->dl_pere = 0;
        (*a)->fils_g = NULL;
        (*a)->frere_d = NULL;
        strcpy((*a)->mot, mot);
        return 1;
    }

    distance = levenshtein_dist((*a)->mot, mot);
    
    /* si il n y a pas de fils */
    if ((*a)->fils_g == NULL) {
        i = inserer_dans_arbreBK(&(*a)->fils_g, mot);
        if (i) {
            (*a)->fils_g->dl_pere = distance;
            return 1;
        }else 
            return 0;
    }else { 
        courant = &(*a)->fils_g;
        /* On trouve le fils dans le quel inserer le mot */
        while ((*courant) != NULL && (*courant)->dl_pere != distance) {
            courant = &(*courant)->frere_d;
        }
        if ((*courant) == NULL) { /* si aucun fils n'avait cette disance */
            i = inserer_dans_arbreBK(courant, mot);
            if (i) {
                (*courant)->dl_pere = distance;
                return 1;
            }else 
                return 0;
        }else
            return inserer_dans_arbreBK(courant, mot);
        
    }
    
}

static void recherche_rec(ArbreBK a, char* mot, Liste* lst, int* s) {
    int d;
    ArbreBK courant;
    if (a == NULL)
        return;
    
    d = levenshtein_dist(a->mot, mot);
    if (d == *s)
        inserer_en_tete(lst, a->mot);
    else if (d < *s) {
        libere_liste(lst);
        inserer_en_tete(lst, a->mot);
        *s = d;
    }
    courant = a->fils_g;
    while (courant != NULL) {
        if (abs(courant->dl_pere - d) <= *s)
            recherche_rec(courant, mot, lst, s);
        courant = courant->frere_d;
    }
}

Liste recherche_bk(ArbreBK a, char* mot) {
    int s;
    Liste lst;
    s = 2; lst = NULL;
    recherche_rec(a, mot, &lst, &s);

    return lst;
}

void liberer_arbreBK(ArbreBK* a) {
    if (*a == NULL)
        return;
    liberer_arbreBK(&(*a)->frere_d);
    liberer_arbreBK(&(*a)->fils_g);
    free(*a);
    *a = NULL;
}

static void affiche_arbreBK_rec(ArbreBK a, int i) {
    ArbreBK courant;
    int j;
    printf("%s\n", a->mot);
    courant = a->fils_g;
    while (courant != NULL ) {
        for (j = 0; j < i; j++)
            printf("\t");
        printf("|-%d-> ", courant->dl_pere);
        affiche_arbreBK_rec(courant, i+1);
        courant = courant->frere_d;
    }
}

void affiche_arbreBK(ArbreBK a) {
    affiche_arbreBK_rec(a, 0);
}
