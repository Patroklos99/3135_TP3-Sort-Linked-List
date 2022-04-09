#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "structures.h"
#include "debutliste.h"
#include "lecturefichier.h"
#include "listechainee.h"
#include "statistiques.h"

int main(int argc, char *argv[]) {
   struct Stats *stats = malloc(sizeof(struct Stats));
   FILE *file = lire_fichier(argv, argc);
   int nb_mots = trouver_nb_mots(file, stats);
   size_t size = trouver_size_fichier(file, stats);
   char **words = calloc(nb_mots, size * sizeof(char *));
   lire_lignes(file, words, &nb_mots, stats);
   Liste *liste = init_liste();
   init_noeud(words, nb_mots, stats, liste);
   liberer_allocs(liste->first, words, stats, liste);
   valider_arg_stats(argc, argv, stats);
}
