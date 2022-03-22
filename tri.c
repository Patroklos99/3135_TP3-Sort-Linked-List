#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct noeud {
    char *mot;
    struct noeud *next;
    int size;

};

struct Stats {
    int mot_sans_doublons;
    int mots_totaux;
    int nb_lignes;
    int nb_lettres;
    char lettre_frequente;
    int nb_let_freq;
};

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
 * Valide le nb d'arguments, arrete le programme s'il ny pas d'argument ou s'il y en a trop.
 *
 * @param argc nb d'arguments.
 * */
void valider_fichier_args(int argc) {
   if (argc == 1) {
      printf("Argument manquant\n");
      exit(0);
   }
   if (argc > 4) {
      printf("Trop d'arguments\n");
      exit(0);
   }

}

int trouver_nb_mots(FILE *file, struct Stats *stats) {
   int x = 0;
   char ligne[80];
   while (fgets(ligne, 81, file)) {
      char *word;
      word = strdup(strtok(ligne, " ,.-\n"));
      while (word != NULL) {
         word = strdup(strtok(NULL, " ,.-\n"));
         ++x;
      }
   }
   stats->mots_totaux = x;
   return x;
}

/*
 * Lit le fichier passé en argument.
 *
 * @param argv reference vers le fichier.
 * */
FILE *lire_fichier(char **argv, int argc) {
   FILE *file = fopen(argv[1], "r");
   valider_fichier_args(argc);
   valider_fichier_existe(file);
   return file;
}

int main(int argc, char *argv[]) {
	struct Stats *stats = malloc(sizeof(struct noeud));
   FILE *file = lire_fichier(argv, argc);
   int nb_mots = trouver_nb_mots(file, stats);

}

