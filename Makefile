CC = gcc
CFLAGS = -Wall -Wextra -pedantic
CPPFLAGS = -I ./include

P_SRC = src
P_INCLUDE = include
P_OBJ = obj
P_BIN = bin
P_LABYRINTHS = labyrinths

EXEC = $(P_BIN)/labyrinth.bin


all: $(EXEC) | mkdirs

$(EXEC): $(P_OBJ)/main.o $(P_OBJ)/labyrinth.o $(P_OBJ)/labyrinth_generator.o $(P_OBJ)/inputs.o $(P_OBJ)/labyrinth_repository.o $(P_OBJ)/user_interface.o $(P_OBJ)/game.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(P_OBJ)/main.o: $(P_SRC)/main.c
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

mkdirs:
	mkdir -p $(P_OBJ)
	mkdir -p $(P_BIN)
	mkdir -p $(P_LABYRINTHS)

clean:
	rm -f $(P_OBJ)/*
