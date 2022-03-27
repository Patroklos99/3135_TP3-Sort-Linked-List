#ifndef STATISTIQUES_H
#define STATISTIQUES_H
#include <stdio.h>
#include "structures.h"

void valider_arg_stats(int argc, char *argv[], struct Stats *stats);
void ecrire_stats(FILE *file, struct Stats *stats);

#endif
