CC=gcc
CFLAG=-Wall -pedantic -ansi
LDFLAG=
OBJ=main.o arbre_lexico.o liste_chaine.o dico.o levenshtein.o arbre_bk.o
HEAD=src/include/arbre_lexico.h src/include/liste_chaine.h src/include/dico.h src/include/levenshtein.h src/include/arbre_bk.h
EXEC=correcteur_2

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(CFLAG) $(LDFLAG)

main.o: $(HEAD)

src/arbre_lexico.o: src/include/arbre_lexico.h

src/liste_chaine.o: src/include/liste_chaine.h

src/dico.o: src/include/dico.h src/include/levenshtein.h src/include/arbre_bk.h

src/levenshtein.o: src/include/levenshtein.h

src/arbre_bk.o: src/include/arbre_bk.h src/include/liste_chaine.h src/include/levenshtein.h

%.o: src/%.c
	$(CC) $< -c $(CFLAG) $(LDFLAG)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)