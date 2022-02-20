#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/arbre_lexico.h"

static void ecrire_debut(FILE* fichier) {
    fprintf(fichier, "digraph arbre {\n");
    fprintf(fichier, "    node [shape=record, height=.1]\n");
    fprintf(fichier, "    edge [tailclip=false, dir=forward];\n");
}

static void ecrire_fichier(FILE* fichier, ArbreLexico a) {
    if (a == NULL) {
        fprintf(fichier, "  n0 [label=\"<gauche> | <valeur> | <droit>\"];\n");
        return;
    }

    if (a->c == '\0') {
        fprintf(fichier, "  n%p [label=\"<gauche> | <valeur> \\\\0 | <droit>\"];\n", (void*)a);
    }else {
        fprintf(fichier, "  n%p [label=\"<gauche> | <valeur> %c | <droit>\"];\n", (void*)a, a->c);
    }
    
    if (a->fg != NULL) {
        fprintf(fichier, "  n%p:gauche:c -> n%p:valeur;\n", (void*)a, (void*)a->fg);
        ecrire_fichier(fichier, a->fg);
    }
    if (a->f != NULL) {
        fprintf(fichier, "  n%p:valeur:c -> n%p:valeur;\n", (void*)a, (void*)a->f);
        ecrire_fichier(fichier, a->f);
    }
    if (a->fd != NULL) {
        fprintf(fichier, "  n%p:droit:c -> n%p:valeur;\n", (void*)a, (void*)a->fd);
        ecrire_fichier(fichier, a->fd);
    }
}

static void ecrire_fin(FILE* fichier) {
    fprintf(fichier, "}\n");
}

static void dessine_arbre(FILE* fichier, ArbreLexico a) {
    ecrire_debut(fichier);
    ecrire_fichier(fichier, a);
    ecrire_fin(fichier);
}

static void creer_pdf(char* dot, char* pdf, ArbreLexico a) {
    int len = strlen(dot) + strlen(pdf) + 15;
    char cmd[len];
    FILE* fichier = fopen(dot, "w");
    dessine_arbre(fichier, a);
    fclose(fichier);
    strcpy(cmd, "dot -Tpdf ");
    strcat(cmd, dot);
    strcat(cmd, " -o ");
    strcat(cmd, pdf);
    system(cmd);
}

void visualise(char* nom_fichier, ArbreLexico a) {
    int len = strlen(nom_fichier) + 3;;
    char dot[len];
    char pdf[len];
    char cmd[len + 6];

    strcpy(dot, nom_fichier);
    strcat(dot, ".dot");
    strcpy(pdf, nom_fichier);
    strcat(pdf, ".pdf");
    creer_pdf(dot, pdf, a);

    strcpy(cmd, "evince");
    strcat(dot, pdf);
}
