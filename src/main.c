#include <stdlib.h>
#include <stdio.h>

#include "include/arbre_lexico.h"
#include "include/affiche_arbre.h"

int main(int argc, char const *argv[])
{
    ArbreLexico a = NULL;
    visualise("arbre", a);
    getchar();

    ajoute_mot("salut", &a);
    ajoute_mot("le", &a);
    ajoute_mot("les", &a);
    ajoute_mot("ordinateur", &a);
    visualise("arbre", a);

    return 0;
}
