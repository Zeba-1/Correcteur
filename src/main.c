#include <stdlib.h>
#include <stdio.h>

#include "include/arbre_lexico.h"
#include "include/affiche_arbre.h"
#include "include/liste_chaine.h"
#include "include/dico.h"

int main(int argc, char const *argv[]) {
    ArbreLexico a;
    a = NULL;

    creer_dico(&a);
    corrige(argv[1], a);

    return 0;
}
