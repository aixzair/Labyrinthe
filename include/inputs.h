#ifndef INPUTS_H
#define INPUTS_H

#include <stdlib.h>

// Prototypes -------------------------------------------------------------------------------------

/**
 * @brief Demande à l'utilisateur de saisir un caractère.
 *
 * @return Le caractère saisi.
 */
char askForChar();

/**
 * @brief Demande à l'utilisateur de saisir un caractère parmi une liste donnée.
 *
 * @param values Tableau des caractères valides.
 * @param n Nombre de caractères valides dans le tableau.
 * @return Le caractère saisi s'il est valide.
 */
char askForCharInList(char* values, int n);

/**
 * @brief Demande à l'utilisateur de saisir un entier.
 *
 * @return L'entier saisi.
 */
int askForInt();

/**
 * @brief Demande à l'utilisateur de saisir un entier parmi une liste donnée.
 *
 * @param values Tableau des entiers valides.
 * @param n Nombre d'entiers valides dans le tableau.
 * @return L'entier saisi s'il est valide.
 */
int askForIntInList(int* values, int n);

/**
 * @brief Demande à l'utilisateur de saisir un entier dans une plage donnée.
 *
 * @param min Valeur minimale autorisée.
 * @param max Valeur maximale autorisée.
 * @return L'entier saisi s'il est dans la plage.
 */
int askForIntInRange(int min, int max);

/**
 * @brief Demande à l'utilisateur de saisir une chaîne de caractères.
 *
 * @param string Pointeur vers le buffer où stocker la chaîne saisie.
 * @param length Taille maximale de la chaîne.
 */
void askForString(char* string, size_t length);

/**
 * @brief Lit un caractère dés qu'il est saisi par l'utilisateur.
 *
 * @return Le caractère saisi.
 */
char fastAskForChar();

/**
 * @brief Lit un caractère parmi une liste donnée dés qu'il est saisi par l'utilisateur.
 *
 * @param values Tableau des caractères valides.
 * @param n Nombre de caractères valides dans le tableau.
 * @return Le caractère saisi s'il est valide.
 */
char fastAskForCharInList(char* values, int n);

#endif
