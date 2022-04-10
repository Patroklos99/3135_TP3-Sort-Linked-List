#define _POSIX_C_SOURCE 200809L
const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "debutliste.h"

int trouver_lettre_frequente(char const **words, struct Stats *stats) {
   int array[255] = {0};
   int max = array[0];
   for (int d = 0; d < stats->mot_sans_doublons; ++d) {
      for (const char *s = words[d]; *s; ++s)
         ++array[(unsigned char) *s];
   }
   for (int i = 0; (int) alphabet[i] != 0; i++) {
      if (array[(int) alphabet[i]] > max) {
         max = array[(int) alphabet[i]];
         int index = i;
         stats->lettre_frequente = (char) alphabet[index];
      }
   }
   return max;
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

int effacer_doublons(int *nb_mots, char **words) {
   for (int i = 0; i < *nb_mots; ++i) {
      if (words[i] != 0) {
         for (int b = 0; b < *nb_mots; ++b) {
            if (strcmp(words[i], words[b]) == 0 && b != i)
               modifier_tab_size(&b, nb_mots, words);
         }
      }
   }
   return *nb_mots;
}

int placer_mots_tab(FILE *file, char **words) {
   int position = 0;
   char ligne[80];
   while (fgets(ligne, 80, file)) {
      char *word = strtok(ligne, " ,.-\n");
      while (word != NULL) {
         words[position++] = strdup(word);
         word = strtok(NULL, " ,.-\n");
      }
   }
   return position != 0;
}

void lire_lignes(FILE *file, char **words, int *nb_mots, struct Stats *stats) {
   if (placer_mots_tab(file, words)) {
      stats->mot_sans_doublons = effacer_doublons(nb_mots, words);
      stats->nb_let_freq = trouver_lettre_frequente((char const **) words,
                                                    stats);
   }
   fclose(file);
}
