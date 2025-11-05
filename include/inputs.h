#ifndef INPUTS_H
#define INPUTS_H

#include <stdlib.h>

char askForChar();

char askForCharInList(char* values, int n);

int askForInt();

int askForIntInList(int* values, int n);

int askForIntInRange(int min, int max);

void askForString(char* string, size_t length);


char fastAskForChar();

char fastAskForCharInList(char * values, int n);

#endif
