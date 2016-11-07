################################################################
#                                                              #
#  Pierre CHEVALIER - ISIMA                                    #
#                                                              #
#  Fichier Makefile                                            #
#  Permet de creer les sources, les objets et l'executable     #
#  dans l'arborescence suivante :                              #
#                                                              #
#  					    $projectroot                           #
#                             |                                #
#             +---------------+----------------+               #
#             |        |           |           |               #
#           src/      obj/        res        build             #
#                                                              #
#                                                              #
################################################################

## CREATION DES VARIABLES ##

## Noms de l'arborescence ##
SRCDIR = src
OBJDIR = obj
EXEDIR = build

### Compilateur ###
CC = g++

### FLAGS ###
CFLAGS = -W -Wall -ansi -pedantic -g -O3
LDFLAGS = -I../CLHEP/include -L../CLHEP/lib -lm -static -lCLHEP-Random-2.1.0.0

### Nom de l'executable ###
_EXEC = stateGenerator pi hasard gattaca
EXEC = $(patsubst %,$(EXEDIR)/%,$(_EXEC))

## LISTE DES REGLES ##

all:$(EXEC)

$(EXEDIR)/stateGenerator: $(SRCDIR)/states.cpp
		@$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS)

$(EXEDIR)/pi: $(SRCDIR)/pi.cpp $(SRCDIR)/seq_splitting.cpp
		@$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS)
		
$(EXEDIR)/hasard: $(SRCDIR)/hasard.cpp $(SRCDIR)/seq_splitting.cpp
		@$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS)
		
$(EXEDIR)/gattaca: $(SRCDIR)/gattaca.cpp $(SRCDIR)/seq_splitting.cpp
		@$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS)
	
clean:
	rm $(EXEC); rm $(OBJ)
