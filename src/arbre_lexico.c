#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/arbre_lexico.h"
#define MAX_MOT 100 /* longueur max d'un mot */

/* AJOUT D'UN MOT AU LANGAGE */

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

    /* si le prefix existe deja */
    if (*mot == '\0' && (*arbre)->c == '\0') /* tout le mot existe déjà */
        return 1;
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

/* SUPPRESION D'UN MOT DU LANGAGE */

static ArbreLexico connecte_enfant(ArbreLexico enfant_gauche, ArbreLexico enfant_droit) {
    if (enfant_gauche->fd == NULL) {
        enfant_gauche->fd = enfant_droit;
        return enfant_gauche;
    }
    if (enfant_droit->fg == NULL) {
        enfant_droit->fg = enfant_gauche;
        return enfant_droit;
    }
    return connecte_enfant(enfant_gauche->fd, enfant_droit);
}

static ArbreLexico enfant(ArbreLexico arbre) {
    if (arbre->fd != NULL && arbre->fg != NULL) {
        return connecte_enfant(arbre->fg, arbre->fd);
    } else if (arbre->fd != NULL) {
        return arbre->fd;
    } else if (arbre->fg != NULL) {
        return arbre->fg;
    } else {
        return NULL;
    }
}

static ArbreLexico supprime_mot_rec(char* mot, ArbreLexico* arbre) {
    ArbreLexico nv_fils;

    if (*arbre == NULL)
        return NULL;

    if((*arbre)->c == '\0' && *mot == '\0') {
        return enfant(*arbre);
    }

    if ((*arbre)->c == *mot) {
        nv_fils = supprime_mot_rec(mot+1, &(*arbre)->f);
        if ( nv_fils == NULL) {
            free((*arbre)->f);
            return enfant(*arbre);
        }else {
            if ((*arbre)->f != nv_fils) {
                free((*arbre)->f);
                (*arbre)->f = nv_fils;
            }
            return *arbre;
        }
    }else if ((*arbre)->c == '\0' || (*arbre)->c < *mot) {
        (*arbre)->fd = supprime_mot_rec(mot, &(*arbre)->fd);
        return *arbre;
    }else if ((*arbre)->c > *mot) {
        (*arbre)->fg = supprime_mot_rec(mot, &(*arbre)->fg);
        return *arbre;
    }
    return NULL;
}

void supprime_mot(char* mot, ArbreLexico* arbre) {
    *arbre = supprime_mot_rec(mot, arbre);
}

/* ENONCER DU LEXIQUE */

static void clear_buffer(char buffer[MAX_MOT], int index) {
    int i;
    for (i = index; i < MAX_MOT; i++)
        buffer[i] = '\0';
}

static void affiche_langage_rec(ArbreLexico arbre, char buffer[MAX_MOT], int index) {
    if (arbre == NULL) {
        return;
    }
    affiche_langage_rec(arbre->fg, buffer, index);
    if (arbre->c == '\0') { /* si on arrive sur la fin d'un mot */
        printf("%s\n", buffer); /* On affiche le mot que l'on construisait */
    }else { /* si ce n'est pas la fin on continue d'ajouter les lettres */
        buffer[index] = arbre->c;
        affiche_langage_rec(arbre->f, buffer, index+1);
    }
    /* On a fini d'afficher tout les suffix alors on pense a nettoyer (on est prorpe) */
    clear_buffer(buffer, index);
    affiche_langage_rec(arbre->fd, buffer, index);
}

void affiche_langage(ArbreLexico arbre) {
    char buffer[MAX_MOT];
    affiche_langage_rec(arbre, buffer, 0);
}

/* RECHERCHE D'UN MOT */

static int recherche_rec(char* mot, ArbreLexico arbre, char buffer[MAX_MOT], int index) {
    if (arbre == NULL)
        return 0;

    if (*mot == '\0') { /* j'ai fini de taper mon mot */
        if (arbre->c == '\0') {
            return 1;
        }else {
            return 0;
        }
    }else if (arbre->c == *mot) {
        buffer[index] = *mot;
        return recherche_rec(mot+1, arbre->f, buffer, index+1);
    }else if (arbre->c < *mot) {
        return recherche_rec(mot, arbre->fd, buffer, index);
    }else if (arbre->c > *mot) {
        return recherche_rec(mot, arbre->fg, buffer, index);
    }
    return 0;
}

/**
 * @return int 1 si le mot est dans le langage, 0 sinon
 */
int recherche(char* mot, ArbreLexico arbre) {
    char buffer[MAX_MOT];
    return recherche_rec(mot, arbre, buffer, 0);
}

/* LIBERATION DE L'ARBRE */

void libere_arbre(ArbreLexico a) {
    if (a == NULL) {
        return;
    }
    
    libere_arbre(a->fg);
    libere_arbre(a->f);
    libere_arbre(a->fd);
    free(a);
}
