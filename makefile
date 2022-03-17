CC=gcc
CFLAG=-Wall -pedantic -ansi
LDFLAG=
OBJ=main.o affiche_arbre.o arbre_lexico.o liste_chaine.o dico.o
HEAD=src/include/affiche_arbre.h src/include/arbre_lexico.h src/include/liste_chaine.h src/include/dico.h
EXEC=correcteur_0

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(CFLAG) $(LDFLAG)

main.o: $(HEAD)

src/affiche_arbre.o: src/include/affiche_arbre.h src/include/arbre_lexico.h

src/arbre_lexico.o: src/include/arbre_lexico.h

src/liste_chaine.o: src/include/liste_chaine.h

src/dico.o: src/include/dico.h

%.o: src/%.c
	$(CC) $< -c $(CFLAG) $(LDFLAG)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)