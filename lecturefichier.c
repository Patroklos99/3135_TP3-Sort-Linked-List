#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "lecturefichier.h"

/*
 * Valide que le fichier existe, arrete le programme dans le cas contraire.
 *
 * @param *file pointeur vers le fichier à lire.
 * */
void valider_fichier_existe(FILE *file) {
   if (!file) {
      printf("Fichier n'existe pas\n");
      exit(0);
   }
}

/*
 * Valide le nbre d'arguments.
 *
 * @param argc nb d'arguments.
 * */
void valider_nbr_args(int argc) {
   if (argc == 1 || argc == 3) {
      printf("Argument fichier a lire ou a ecrire manquant\n");
      exit(0);
   }
   if (argc > 4) {
      printf("Trop d'arguments\n");
      exit(0);
   }
}

/*
 * Valide argument option -S
 *
 * @param argc nb d'arguments.
 * @param argv pointeur vers les arguments.
 * */
void valider_arg_invalide(int argc, char **argv) {
   if (argc == 4 && strcmp(argv[2], "-S") != 0) {
      printf("L'option est invalide, essayez avec -S\n");
      exit(0);
   }
}

/*
 * Valide le nb d'arguments, arrete le programme s'il ny pas d'argument ou s'il y en a trop.
 *
 * @param argc nb d'arguments.
 * @param argv pointeur vers les arguments.
 * */
void valider_fichier_args(int argc, char **argv) {
   valider_nbr_args(argc);
   valider_arg_invalide(argc, argv);
}

/*
 * Lit le fichier passé en argument.
 *
 * @param argv reference vers le fichier.
 * @param argc nb d'arguments.
 * */
FILE *lire_fichier(char **argv, int argc) {
   FILE *file = fopen(argv[1], "r");
   valider_fichier_args(argc, argv);
   valider_fichier_existe(file);
   return file;
}

/*
 * Trouve le nombre de lignes dans le fichier d'entrée.
 *
 * @param *file pointeur du fichier à lire.
 * @param stats pointeur vers la structure statistiques
 * */
void compter_lignes(FILE *file, struct Stats *stats) {
   int compteur = 0;
   char ligne[80];
   while (fgets(ligne, 80, file))
      compteur++;
   stats->nb_lignes = compteur;
}

/*
 * Trouve la taille du fichier d'entrée.
 *
 * @param *file pointeur du fichier à lire.
 * @param stats pointeur vers la structure statistiques
 *
 * return la taille du fichier.
 * */
size_t trouver_size_fichier(FILE *file, struct Stats *stats) {
   fseek(file, 0, SEEK_END);
   size_t size = ftell(file);
   fseek(file, 0, SEEK_SET);
   compter_lignes(file, stats);
   fseek(file, 0, SEEK_SET);
   return size;
}

/*
 * Trouve le nombre de mots dans le fichier d'entrée
 *
 * @param *file pointeur du fichier à lire.
 * @param stats pointeur vers la structure statistiques
 *
 * return le nombre de mots trouvés.
 * */
int trouver_nb_mots(FILE *file, struct Stats *stats) {
   int x = 0;
   char ligne[80];
   while (fgets(ligne, 80, file)) {
      char *word;
      word = strtok(ligne, " ,.-\n");
      for (; word != NULL; ++x)
         word = strtok(NULL, " ,.-\n");
   }
   return stats->mots_total = x;
}
