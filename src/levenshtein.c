#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "include/levenshtein.h"

#define MIN3(a, b, c) a < b ? (a < c ? a : c) : (b < c ? b : c)

int levenshtein_dist(char* mot1, char* mot2) {
    int x, y, m1_long, m2_long, dernier_calc, tmp;
    int* tab;

    m1_long = strlen(mot1);
    m2_long = strlen(mot2);
    tab = malloc(m1_long + 1);

    for (x = 1; x <= m1_long; x++)
        tab[x] = x;

    for (x = 1; x <= m2_long; x++) {
        tab[0] = x;
        for (y = 1, dernier_calc = x - 1; y <= m1_long; y++) {
            tmp = tab[y];
            tab[y] = MIN3(tab[y] + 1, tab[y - 1] + 1, dernier_calc + (mot1[y - 1] == mot2[x - 1] ? 0 : 1));
            dernier_calc = tmp;
        }
    }
    
    return tab[m1_long];
}
