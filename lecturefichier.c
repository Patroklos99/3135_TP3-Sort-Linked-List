#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "lecturefichier.h"

void arret_prog(int test, char *texte) {
   if (test) {
      printf("%s\n", texte);
      exit(0);
   }
}

int valider_fichier_existe(FILE *file) {
   return !file;
}

int valider_nbr_args1(int argc) {
   int int_verite = 0;
   if (argc > 4)
      int_verite = 1;
   return int_verite;
}

int valider_nbr_args0(int argc) {
   int int_verite = 0;
   if (argc == 1 || argc == 3)
      int_verite = 1;
   return int_verite;
}

int valider_arg_invalide(int argc, char **argv) {
   int int_verite = 0;
   if (argc == 4 && strcmp(argv[2], "-S") != 0)
      int_verite = 1;
   return int_verite;
}
	
FILE *lire_fichier(char **argv, int argc) {
   FILE *file = fopen(argv[1], "r");
   arret_prog(valider_nbr_args0(argc), err0);
   arret_prog(valider_fichier_existe(file), err1);
   arret_prog(valider_nbr_args1(argc), err2);
   arret_prog(valider_arg_invalide(argc, argv), err3);
   return file;
}

int compter_lignes(FILE *file) {
   int nb_lignes = 0;
   char ligne[80];
   while (fgets(ligne, 80, file))
      nb_lignes++;
   return nb_lignes;
}

size_t trouver_size_fichier(FILE *file, struct Stats *stats) {
   fseek(file, 0, SEEK_END);
   size_t size = ftell(file);
   fseek(file, 0, SEEK_SET);
   stats->nb_lignes = compter_lignes(file);
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
