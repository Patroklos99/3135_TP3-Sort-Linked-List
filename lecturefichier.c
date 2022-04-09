#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "lecturefichier.h"

void arret_prog(int test) {
   if (test)
      exit(0);
}

int valider_fichier_existe(FILE *file) {
   if (!file) 
      printf("Fichier n'existe pas\n");
   return !file;
}

int valider_nbr_args(int argc) {
   int int_verite = 0;
   if (argc == 1 || argc == 3) {
      printf("Argument fichier a lire ou a ecrire manquant\n");
      int_verite = 1;
   }
   if (argc > 4) {
      printf("Trop d'arguments\n");
      int_verite = 1;
   }
   return int_verite;
}

int valider_arg_invalide(int argc, char **argv) {
   int int_verite = 0;
   if (argc == 4 && strcmp(argv[2], "-S") != 0) {
      printf("L'option est invalide, essayez avec -S\n");
      int_verite = 1;
   }
   return int_verite;
}
	
FILE *lire_fichier(char **argv, int argc) {
   FILE *file = fopen(argv[1], "r");
   arret_prog(valider_fichier_existe(file));
   arret_prog(valider_nbr_args(argc));
   arret_prog(valider_arg_invalide(argc, argv));
   return file;
}

void compter_lignes(FILE *file, struct Stats *stats) {
   int compteur = 0;
   char ligne[80];
   while (fgets(ligne, 80, file))
      compteur++;
   stats->nb_lignes = compteur;
}

size_t trouver_size_fichier(FILE *file, struct Stats *stats) {
   fseek(file, 0, SEEK_END);
   size_t size = ftell(file);
   fseek(file, 0, SEEK_SET);
   compter_lignes(file, stats);
   fseek(file, 0, SEEK_SET);
   return size;
}

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
