#ifndef STATISTIQUES_H
#define STATISTIQUES_H
#include <stdio.h>
#include "structures.h"

/*
 * Valide le nb d'arguments avant l'écriture dans le fichier.
 *
 * @param argv reference vers les arguments donnés.
 * @param argc nb d'arguments.
 * @param stats pointeur vers la structure statistiques
 * */
void valider_arg_stats(int argc, char *argv[], struct Stats *stats);

/*
 * Écrit dans le fichier de sortie.
 *
 * @param *file le pointeur vers le fichier à écrire.
 * @param stats pointeur vers la structure statistiques
 * */
void ecrire_stats(FILE *file, struct Stats *stats);

#endif
