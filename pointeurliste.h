#ifndef POINTEURLISTE_H
#define POINTEURLISTE_H
#include <stdio.h>
#include "structures.h"

/*
 * Lit chaque ligne du fichier en entrée.
 *
 * @param *file pointeur du fichier à lire.
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @param nb_mots nombre de mots dans le fichier d'entrée.
 * @param stats pointeur vers la structure statistiques
 * */
void lire_lignes(FILE *file, char **words, int *nb_mots, struct Stats *stats);

/*
 * Place chaque mot dans le pointeur de pointeurs (**words).
 *
 * @param ligne Ligne lu.
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @param positon Position correspondante dans **words.
 * */
void placer_mots_tabs(char ligne[80], char **words, int *position);

/*
 * Efface les doublons dans **words.
 *
 * @param nb_mots nombre de mots dans le fichier d'entrée.
 * @param words pointeur de pointeur vers leur mot correspondant.
 * */
void effacer_doublons(int *nb_mots, char **words);

/*
 * Modifie la taille du pointeur de pointeurs (**words)
 *
 * @param nb_mots nombre de mots dans le fichier d'entrée.
 * @param words pointeur de pointeur vers leur mot correspondant.
 * */
void modifier_tab_size(int *b, int *nb_mots_update, char **words);

/*
 * Trouve la lettre la plus frequente (sans inclure les doublons).
 *
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @param stats pointeur vers la structure statistiques
 * */
void trouver_lettre_frequente(char const **words, struct Stats *stats);

/*
 * Trouve la lettre la plus fréquente  dans l'array (sans inclure les doublons).
 *
 * @param array Contient le nombre de répétition de toutes les lettres.
 * @param max Contient le nombre de répétition de la lettre la plus frequente.
 * @param stats pointeur vers la structure statistiques
 * */
void
chercher_lettre_freq_array(const int array[255], int max, struct Stats *stats);

#endif
