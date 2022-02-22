#include <stdlib.h>
#include <stdio.h>

#include "include/arbre_lexico.h"
#include "include/affiche_arbre.h"
#define MAX_MOT 100 /* longueur max d'un mot */

int main(int argc, char const *argv[]) {
    ArbreLexico a = NULL;
    char mot_recherche[MAX_MOT];

    /* ajout de mot dans le langage */
    ajoute_mot("salut", &a);
    ajoute_mot("le", &a);
    ajoute_mot("la", &a);
    ajoute_mot("les", &a);
    ajoute_mot("ordinateur", &a);
    visualise("arbre", a);
    
    /* recherche d'un prefix dans ce langage */
    printf("rechercher un prefixe dans le langage:\n");
    scanf("%s", mot_recherche);
    if (!recherche(mot_recherche, a)) {
        printf("ce prefixe n'existe pas\n");
    }

    libere_arbre(a); /* On libère la place que l'arbre avait pris */

    return 0;
}
