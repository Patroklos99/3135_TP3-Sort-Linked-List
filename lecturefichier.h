#ifndef LECTUREFICHIER_H
#define LECTUREFICHIER_H
#define err0 "Argument fichier a lire ou a ecrire manquant. Fin du programme."
#define err1 "Fichier n'existe pas. Fin du programme."
#define err2 "Trop d'arguments. Fin du programme."
#define err3 "L'option est invalide, essayez avec -S. Fin du programme."
#include <stdio.h>
#include "structures.h"

/*
 * Arrete le programme dependant de la valeur de verité du param.
 *
 * @param test valeur de verité à tester.
 * @param text pointeur vers le texte à afficher.
 * */
void arret_prog(int test, char *texte);

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
 * @return nombre de lignes
 * */
int compter_lignes(FILE *file);

/*
 * Lit le fichier passé en argument.
 *
 * @param argc nb d'arguments.
 * @param argv reference vers le fichier.
 * @return pointeur vers le fichier cree.
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
 * @param argv pointeur vers les arguments.
 * @return valeur de verité
 * */
int valider_nbr_args1(int argc);

/*
 * Valide le nbre d'arguments.
 *
 * @param argc nb d'arguments.
 * @param argv pointeur vers les arguments.
 * @return valeur de verité
 * */
int valider_nbr_args0(int argc);

#endif
