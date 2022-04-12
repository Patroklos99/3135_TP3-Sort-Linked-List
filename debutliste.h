/**
 *  Auteur: Renzo Arturo Salcedo
 *  Code Permanent: SALR02089408
 *  Cours: INF3135 TP3 UQAM
 *  Session: Hiver 2022
 *
 *  Classe debutliste.h
 *  Represente la classe debutliste.h contenant les fonctions en lien avec la 
 *  structure liste qui contient les noeuds.
 */

#ifndef DEBUTLISTE_H
#define DEBUTLISTE_H
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
 * @param *file pointeur du fichier à lire.
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @return valeur de verité si des mots ont été rajoutés.
 * */
int placer_mots_tab(FILE *file, char **words);

/*
 * Efface les doublons dans **words.
 *
 * @param nb_mots nombre de mots dans le fichier d'entrée.
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @return Le nouveau nombre de mots appres l'effacage des doublons.
 * */
int effacer_doublons(int *nb_mots, char **words);

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
 * @return le max de fois que la lettre la plus répétée apparait.
 * */
int trouver_lettre_frequente(char const **words, struct Stats *stats);

#endif
