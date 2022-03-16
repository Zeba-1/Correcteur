#ifndef __ARBRE__
#define __ARBRE__

typedef struct noeud {
    char c;
    struct noeud* fg;
    struct noeud* f;
    struct noeud* fd;
} Noeud, *ArbreLexico;

Noeud* alloue_noeud(char c);

int ajoute_mot(char* mot, ArbreLexico* arbre);
void affiche_langage(ArbreLexico arbre);
int recherche(char* mot, ArbreLexico arbre);
void libere_arbre(ArbreLexico a);
void supprime_mot(char* mot, ArbreLexico* arbre);

#endif
