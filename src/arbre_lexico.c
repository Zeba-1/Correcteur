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
    if (arbre == NULL && *mot != '\0') {
        return 0;
    }
    if (*mot == '\0') { /* on a fini de rentrer le prefixe dans l'arbre */ 
        affiche_langage_rec(arbre, buffer, index);
        return 1;
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
 * @return int 1 si le mot ou le prefixe est dans le langage, 0 sinon
 */
int recherche(char* mot, ArbreLexico arbre) {
    char buffer[MAX_MOT];
    return recherche_rec(mot, arbre, buffer, 0);
}
