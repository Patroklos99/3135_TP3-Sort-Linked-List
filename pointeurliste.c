#define _POSIX_C_SOURCE 200809L
const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "pointeurliste.h"

void
chercher_lettre_freq_array(const int array[255], int max, struct Stats *stats) {
   int index;
   for (int i = 0; (int) alphabet[i] != 0; i++) {
      if (array[(int) alphabet[i]] > max) {
         max = array[(int) alphabet[i]];
         index = i;
         stats->lettre_frequente = (char) alphabet[index];
         stats->nb_let_freq = max;
      }
   }
}

void trouver_lettre_frequente(char const **words, struct Stats *stats) {
   int array[255] = {0};
   int max = array[0];
   for (int d = 0; d < stats->mot_sans_doublons; ++d) {
      for (const char *s = words[d]; *s; ++s)
         ++array[(unsigned char) *s];
   }
   chercher_lettre_freq_array(array, max, stats);
}

void modifier_tab_size(int *b, int *nb_mots_update, char **words) {
   free(words[*b]);
   for (int k = *b; k < *nb_mots_update; k++) {
      words[k] = words[k + 1];
      words[*nb_mots_update + 1] = 0;
   }
   (*nb_mots_update)--;
   (*b)--;
}

void effacer_doublons(int *nb_mots, char **words) {
   for (int i = 0; i < *nb_mots; ++i) {
      if (words[i] != 0) {
         for (int b = 0; b < *nb_mots; ++b) {
            if (strcmp(words[i], words[b]) == 0 && b != i)
               modifier_tab_size(&b, nb_mots, words);
         }
      }
   }
}

void placer_mots_tabs(char ligne[80], char **words, int *position) {
   char *word = strtok(ligne, " ,.-\n");
   while (word != NULL) {
      words[(*position)++] = strdup(word);
      word = strtok(NULL, " ,.-\n");
   }
}

void lire_lignes(FILE *file, char **words, int *nb_mots, struct Stats *stats) {
   int position = 0;
   char ligne[80];
   while (fgets(ligne, 80, file))
      placer_mots_tabs(ligne, words, &position);
   effacer_doublons(nb_mots, words);
   stats->mot_sans_doublons = *nb_mots;
   trouver_lettre_frequente((char const **) words, stats);
   fclose(file);
}
 
