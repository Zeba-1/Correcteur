typedef struct noeud {
    char c;
    struct noeud* fg;
    struct noeud* f;
    struct noeud* fd;
} Noeud, *ArbreLexico;

Noeud* alloue_noeud(char c);

int ajoute_mot(char* mot, ArbreLexico* arbre);