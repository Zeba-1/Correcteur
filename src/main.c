#include <stdlib.h>
#include <stdio.h>

#include "include/arbre_lexico.h"
#include "include/affiche_arbre.h"
#include "include/liste_chaine.h"
#include "include/dico.h"

int main(int argc, char const *argv[]) {
    ArbreLexico a;
    Liste erreurs;
    a = NULL;
    erreurs = NULL;

    if (argc < 3) {
        fprintf(stderr, "PAS ASSEZ D'ARGUMENT");
    }

    creer_dico(&a, argv[2]);
    erreurs = trouve_erreur(argv[1], a);
    propose_correction(erreurs, argv[2]);

    return 0;
}
