#include <stdlib.h>
#include <stdio.h>

#include "include/arbre_lexico.h"
#include "include/liste_chaine.h"
#include "include/dico.h"
#include "include/arbre_bk.h"

int main(int argc, char const *argv[]) {
    ArbreBK a;
    a = NULL;

    if (argc < 3) {
        fprintf(stderr, "PAS ASSEZ D'ARGUMENT");
    }

    creer_arbreBK(&a, argv[2]);
    trouve_erreur_bk(argv[1], a);

    return 0;
}
