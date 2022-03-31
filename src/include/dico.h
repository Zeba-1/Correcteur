#ifndef __DICO__
#define __DICO__

#include "arbre_lexico.h"
#include "liste_chaine.h"

void creer_dico(ArbreLexico* a, char* nom_dico);
Liste trouve_erreur(char* nom_texte, ArbreLexico dico);
void propose_correction(Liste erreurs, char* nom_dico);

#endif
