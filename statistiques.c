#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "statistiques.h"

void ecrire_stats(FILE *file, struct Stats *stats) {
   fprintf(file, "Le nb de mots (sans doublons) est: %d.\n",
           stats->mot_sans_doublons);
   fprintf(file, "Le nb de mots avec doublons est: %d.\n", stats->mots_total);
   fprintf(file, "Le nb de lignes est: %d.\n", stats->nb_lignes);
   fprintf(file, "Le nb de lettres des mots (sans doublons) est: %d.\n",
           stats->nb_lettres);
   fprintf(file, "La lettre la plus frequente (sans doublons) est: %c, "
                 "apparait %d fois.\n", stats->lettre_frequente,
           stats->nb_let_freq);
}

void valider_arg_stats(int argc, char *argv[], struct Stats *stats) {
   if (argc == 4 && strcmp(argv[2], "-S") == 0) {
      FILE *file = fopen(argv[3], "w");
      if (file != NULL)
         ecrire_stats(file, stats);
      fclose(file);
   } 
   free(stats);
}
