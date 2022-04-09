#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "statistiques.h"
#include "lecturefichier.h"

int ecrire_stats(FILE *file, struct Stats *stats) {
   int int_verite = 1;
   if (file != NULL) {
         fprintf(file, "Le nb de mots (sans doublons) est: %d.\n",
                 stats->mot_sans_doublons);
         fprintf(file, "Le nb de mots avec doublons est: %d.\n",
                 stats->mots_total);
         fprintf(file, "Le nb de lignes est: %d.\n", stats->nb_lignes);
         fprintf(file, "Le nb de lettres des mots (sans doublons) est: %d.\n",
                 stats->nb_lettres);
         fprintf(file, "La lettre la plus frequente (sans doublons) est: %c, "
                       "apparait %d fois.\n", stats->lettre_frequente,
                 stats->nb_let_freq);
         int_verite = 0;
      }
   return int_verite;
}

void valider_arg_stats(int argc, char *argv[], struct Stats *stats) {
   if (argc == 4 && strcmp(argv[2], "-S") == 0) {
      FILE *file = fopen(argv[3], "w");
      arret_prog(ecrire_stats(file, stats), err4);
      fclose(file);
   }
   free(stats);
}
