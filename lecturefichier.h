#ifndef LECTUREFICHIER_H
#define LECTUREFICHIER_H
#include <stdio.h>
#include "structures.h"

/*
 * Arrete le programme dependant de la valeur de verité du param.
 *
 * @param test valeur de verité à tester.
 * */
void arret_prog(int test);

/*
 * Trouve le nombre de mots dans le fichier d'entrée
 *
 * @param *file pointeur du fichier à lire.
 * @param stats pointeur vers la structure statistiques
 *
 * return le nombre de mots trouvés.
 * */
int trouver_nb_mots(FILE *file, struct Stats *stats);

/*
 * Trouve la taille du fichier d'entrée.
 *
 * @param *file pointeur du fichier à lire.
 * @param stats pointeur vers la structure statistiques
 *
 * return la taille du fichier.
 * */
size_t trouver_size_fichier(FILE *file, struct Stats *stats);

/*
 * Trouve le nombre de lignes dans le fichier d'entrée.
 *
 * @param *file pointeur du fichier à lire.
 * @param stats pointeur vers la structure statistiques
 * */
void compter_lignes(FILE *file, struct Stats *stats);

/*
 * Lit le fichier passé en argument.
 *
 * @param argc nb d'arguments.
 * @param argv reference vers le fichier.
 * */
FILE *lire_fichier(char **argv, int argc);

/*
 * Valide que le fichier existe, arrete le programme dans le cas contraire.
 *
 * @param *file pointeur vers le fichier à lire.
 * @return valeur de verité
 * */
int valider_fichier_existe(FILE *file);

/*
 * Valide argument option -S
 *
 * @param argc nb d'arguments.
 * @param argv pointeur vers les arguments.
 * @return valeur de verité
 * */
int valider_arg_invalide(int argc, char **argv);

/*
 * Valide le nbre d'arguments.
 *
 * @param argc nb d'arguments.
 * @param argv pointeur vers les arguments..
 * @return valeur de verité
 * */
int valider_nbr_args(int argc);

#endif
