CC=gcc
cflag=-Wall -pedantic -ansi
lflag=
OBJ=main.o affiche_arbre.o arbre_lexico.o
HEAD=src/include/affiche_arbre.h src/include/arbre_lexico.h
EXEC=correcteur

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(cflag) $(lflag)

main.o: $(HEAD)

src/affiche_arbre.o: src/include/affiche_arbre.h src/include/arbre_lexico.h

src/arbre_lexico.o: src/include/arbre_lexico.h

%.o: src/%.c
	$(CC) $< -c  $(cflag) $(lflag)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)