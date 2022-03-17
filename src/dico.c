#include <stdio.h>
#include <stdlib.h>

#include "include/dico.h"
#include "include/liste_chaine.h"
#include "include/arbre_lexico.h"

#define MAX_MOT 100

static void init_buffer(char** buffer) {
    *buffer = malloc(MAX_MOT);
    *buffer[0] = '\0';
}

static int char_valide(char c) {
    if (c >= 'a' && c <= 'z') {
        return c;
    }else {
        c += 'A' - 'a';
        if (c >= 'a' && c <= 'z') {
            return c;
        }else
            return -2;
    }
}

static char lire_espace(FILE* fichier) {
    char c;
    do {
        c = fgetc(fichier);
    } while (c == ' ');
    return c;
}

static char lire_jusqua_espace(FILE* fichier) {
    char c;
    do {
        c = fgetc(fichier);
    } while (c != ' ' && c != EOF);
    return c;
}

char* lire_mot(FILE* fichier) {
    char* buffer;
    char courant;
    int i;
    init_buffer(&buffer);
    i = 0;

    courant = lire_espace(fichier);
    do {
        if (char_valide(courant) != -2) {
            courant = char_valide(courant);
            buffer[i] = courant;
            i++;
        }else {
            if (courant == EOF && buffer[0] != '\0') {
                break;
            }else if (courant == EOF && buffer[0] == '\0'){
                free(buffer);
                return NULL;
                lire_jusqua_espace(fichier);
                return lire_mot(fichier);
            }else {
                free(buffer);
                lire_jusqua_espace(fichier);
                return lire_mot(fichier);
            }
        }
        courant = fgetc(fichier);
    } while (courant != ' ' && courant != '\n');
    
    buffer[i+1] = '\0';
    return buffer;
}

void creer_dico(ArbreLexico* a, char* nom_dico) {
    char* mot;
    FILE* dico = fopen(nom_dico, "r");

    while ((mot = lire_mot(dico)) != NULL) {
        ajoute_mot(mot, a);
    }
}

void corrige(char* nom_texte, ArbreLexico dico) {
    char* mot;
    Liste lst;
    FILE* texte = fopen(nom_texte, "r");
    lst = NULL;

    while ((mot = lire_mot(texte)) != NULL) {
        if (!recherche(mot, dico)) {
            inserer_en_tete(&lst, mot);
        }
    }

    while (lst != NULL) {
        printf("%s\n", lst->mot);
        lst = lst->suivant;
    }
}
