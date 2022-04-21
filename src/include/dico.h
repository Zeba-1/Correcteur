#ifndef __DICO__
#define __DICO__

#include "arbre_lexico.h"
#include "liste_chaine.h"
#include "arbre_bk.h"

void creer_dico(ArbreLexico* a, char* nom_dico);
Liste trouve_erreur(char* nom_texte, ArbreLexico dico);
void propose_correction(Liste erreurs, char* nom_dico);
void creer_arbreBK(ArbreBK* a, char* nom_dico);
void trouve_erreur_bk(char* nom_texte, ArbreBK dico);

#endif
