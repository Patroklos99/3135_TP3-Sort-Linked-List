#define _POSIX_C_SOURCE 200809L
const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "pointeurliste.h"

/*
 * Change de place des mots dans leur position correspndante.
 *
 * @param i position reguliere d'iteration sur **words
 * @param j_min Mot alphabetiquement le suivant en relation du précedent.
 * @param words pointeur de pointeur vers leur mot correspondant.
 * */
void swap_mots(int i, int j_min, char **words) {
   char *tmp;
   tmp = words[i];
   words[i] = words[j_min];
   words[j_min] = tmp;
}

/*
 * Trie le pointeur de pointeur (**words).
 *
 * @param nb_mots_update, nombre de mots dans **words updaté.
 * @param words pointeur de pointeur vers leur mot correspondant.
 * */
void trier_tab(int nb_mots_update, char **words) {
   for (int i = 0; i < nb_mots_update - 1; ++i) {
      int j_min = i;
      for (int j = i + 1; j < nb_mots_update; ++j) {
         if (strcmp(words[j], words[j_min]) < 0)
            j_min = j;
      }
      if (j_min != i)
         swap_mots(i, j_min, words);
   }
}

/*
 * Trouve la lettre la plus fréquente  dans l'array (sans inclure les doublons).
 *
 * @param array Contient le nombre de répétition de toutes les lettres.
 * @param max Contient le nombre de répétition de la lettre la plus frequente.
 * @param stats pointeur vers la structure statistiques
 * */
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

/*
 * Trouve la lettre la plus frequente (sans inclure les doublons).
 *
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @param stats pointeur vers la structure statistiques
 * */
void trouver_lettre_frequente(char const **words, struct Stats *stats) {
   int array[255] = {0};
   int max = array[0];
   for (int d = 0; d < stats->mot_sans_doublons; ++d) {
      for (const char *s = words[d]; *s; ++s)
         ++array[(unsigned char) *s];
   }
   chercher_lettre_freq_array(array, max, stats);
}

/*
 * Modifie la taille du pointeur de pointeurs (**words)
 *
 * @param nb_mots nombre de mots dans le fichier d'entrée.
 * @param words pointeur de pointeur vers leur mot correspondant.
 * */
void modifier_tab_size(int *b, int *nb_mots_update, char **words) {
   free(words[*b]);
   for (int k = *b; k < *nb_mots_update; k++) {
      words[k] = words[k + 1];
      words[*nb_mots_update + 1] = 0;
   }
   (*nb_mots_update)--;
   (*b)--;
}

/*
 * Efface les doublons dans **words.
 *
 * @param nb_mots nombre de mots dans le fichier d'entrée.
 * @param words pointeur de pointeur vers leur mot correspondant.
 * */
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

/*
 * Place chaque mot dans le pointeur de pointeurs (**words).
 *
 * @param ligne Ligne lu.
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @param positon Position correspondante dans **words.
 * */
void placermots_tabs(char ligne[80], char **words, int *position) {
   char *word = strtok(ligne, " ,.-\n");
   while (word != NULL) {
      words[(*position)++] = strdup(word);
      word = strtok(NULL, " ,.-\n");
   }
}

/*
 * Lit chaque ligne du fichier en entrée.
 *
 * @param *file pointeur du fichier à lire.
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @param nb_mots nombre de mots dans le fichier d'entrée.
 * @param stats pointeur vers la structure statistiques
 * */
void lire_lignes(FILE *file, char **words, int *nb_mots, struct Stats *stats) {
   int position = 0;
   char ligne[80];
   while (fgets(ligne, 80, file))
      placermots_tabs(ligne, words, &position);
   effacer_doublons(nb_mots, words);
   stats->mot_sans_doublons = *nb_mots;
   trouver_lettre_frequente((char const **) words, stats);
   trier_tab(*nb_mots, words);
   fclose(file);
}
 
