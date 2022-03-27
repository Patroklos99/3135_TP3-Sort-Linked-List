#ifndef POINTEURLISTE_H
#define POINTEURLISTE_H
#include <stdio.h>
#include "structures.h"

void lire_lignes(FILE *file, char **words, int *nb_mots, struct Stats *stats);
void placermots_tabs(char ligne[80], char **words, int *position);
void effacer_doublons(int *nb_mots, char **words);
void modifier_tab_size(int *b, int *nb_mots_update, char **words);
void trouver_lettre_frequente(char const **words, struct Stats *stats);
void
chercher_lettre_freq_array(const int array[255], int max, struct Stats *stats);
void trier_tab(int nb_mots_update, char **words);
void swap_mots(int i, int j_min, char **words);

#endif
