#ifndef LECTUREFICHIER_H
#define LECTUREFICHIER_H
#include <stdio.h>
#include "structures.h"

int trouver_nb_mots(FILE *file, struct Stats *stats);
size_t trouver_size_fichier(FILE *file, struct Stats *stats);
void compter_lignes(FILE *file, struct Stats *stats);
FILE *lire_fichier(char **argv, int argc);
void valider_fichier_args(int argc, char **argv);
void valider_fichier_existe(FILE *file);
void valider_arg_invalide(int argc, char **argv);
void valider_nbr_args(int argc, char **argv);

#endif
