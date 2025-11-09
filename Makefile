CC = gcc
CFLAGS = -Wall -Wextra -pedantic
CPPFLAGS = -I ./include

P_SRC = src
P_INCLUDE = include
P_OBJ = obj
P_BIN = bin
P_LABYRINTHS = labyrinths
P_SCORES = scores
P_DOCUMENTATION = documentation

EXEC = $(P_BIN)/labyrinth.bin
TEST = $(P_BIN)/tests.bin

all: labyrinth tests | mkdirs

labyrinth : $(EXEC)
tests : $(TEST)

$(EXEC): $(P_OBJ)/main.o $(P_OBJ)/labyrinth.o $(P_OBJ)/labyrinth_generator.o $(P_OBJ)/inputs.o $(P_OBJ)/labyrinth_repository.o $(P_OBJ)/user_interface.o $(P_OBJ)/game.o $(P_OBJ)/leaderboard.o $(P_OBJ)/menu.o $(P_OBJ)/monsters.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(TEST): $(P_OBJ)/mainTest.o $(P_OBJ)/labyrinth.o $(P_OBJ)/labyrinth_generator.o $(P_OBJ)/inputs.o $(P_OBJ)/labyrinth_repository.o $(P_OBJ)/user_interface.o $(P_OBJ)/game.o $(P_OBJ)/leaderboard.o $(P_OBJ)/menu.o $(P_OBJ)/monsters.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(P_OBJ)/main.o: $(P_SRC)/main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(P_OBJ)/mainTest.o: $(P_SRC)/tests/mainTest.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(P_OBJ)/labyrinth.o: $(P_SRC)/labyrinth.c $(P_INCLUDE)/labyrinth.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(P_OBJ)/labyrinth_generator.o: $(P_SRC)/labyrinth_generator.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(P_OBJ)/labyrinth_repository.o: $(P_SRC)/labyrinth_repository.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(P_OBJ)/inputs.o: $(P_SRC)/inputs.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(P_OBJ)/game.o: $(P_SRC)/game.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(P_OBJ)/user_interface.o: $(P_SRC)/user_interface.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(P_OBJ)/leaderboard.o: $(P_SRC)/leaderboard.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(P_OBJ)/menu.o: $(P_SRC)/menu.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(P_OBJ)/monsters.o: $(P_SRC)/monsters.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

doc: | mkdirs
	doxygen Doxyfile

mkdirs:
	mkdir -p $(P_OBJ)
	mkdir -p $(P_BIN)
	mkdir -p $(P_LABYRINTHS)
	mkdir -p $(P_SCORES)
	mkdir -p $(P_DOCUMENTATION)

manuals:
	pandoc Manuel_Joueur.md -o Manuel_Joueur.pdf --pdf-engine=xelatex
	pandoc Manuel_Developpeur.md -o Manuel_Developpeur.pdf --pdf-engine=xelatex

clean:
	rm -f $(P_OBJ)/*

clean_labyrinths:
	rm -f $(P_LABYRINTHS)/*
	rm -f $(P_SCORES)/*
