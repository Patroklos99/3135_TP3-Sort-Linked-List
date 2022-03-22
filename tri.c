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

void compter_lignes(FILE *file, struct Stats *stats) {
   int compteur = 0;
   char ligne[80];
   while (fgets(ligne, 80, file)) {
      compteur++;
   }
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

void placermots_tabs(char **words, char *word, int *x) {
   while (word != NULL) {
      //printf("->#%d %s\n", *x, word);
      words[*x] = word;
      word = strdup(strtok(NULL, " ,.-\n"));
      ++(*x);
   }
}

void modifier_tab_size(int *b, int *count, char **words) {
   for (int k = *b; k < *count; k++) {
      words[k] = words[k + 1];
      words[*count + 1] = 0;
   }
   (*count)--;
   (*b)--;
}

void effacer_doublon(int *count, char **words) {
   for (int a = 0; a < *count; ++a) {
      if (words[a] != 0) {
         for (int b = 0; b < *count; ++b) {
            if (strcmp(words[a], words[b]) == 0 && b != a) {
               modifier_tab_size(&b, count, words);
            }
         }
      }
   }
}

void trouver_lettre_frequente(char const **words, struct Stats *stats) {
   int array[255] = {0};
   char str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   int i, max;
   for (int d = 0; d < stats->mot_sans_doublons; ++d) {
      for (const char *s = words[d]; *s; ++s)
         ++array[(unsigned char) *s];
   }
   max = array[0];
   int index;
   for (i = 0; str[i] != 0; i++) {
      if (array[str[i]] > max) {
         max = array[str[i]];
         index = i;
         stats->lettre_frequente = (char) str[index];
         stats->nb_let_freq = max;
      }
   }
}

void lire_lignes(FILE *file, char **words, int *nb_mots, struct Stats *stats) {
   int x = 0;
   char ligne[80];
   while (fgets(ligne, 81, file)) {
      char *word;
      word = strdup(strtok(ligne, " ,.-\n"));
      placermots_tabs(words, word, &x);
   }
   effacer_doublon(nb_mots, words);
   stats->mot_sans_doublons = *nb_mots;
   trouver_lettre_frequente((char const **) words, stats);
   fclose(file);
}

void changer_mots(int i, int j_min, char **words) {
   char temp[100];
   strcpy(temp, words[i]);
   strcpy(words[i], words[j_min]);
   strcpy(words[j_min], temp);
}

void trier_tab(int count, char **words, struct noeud *ptr) {
   for (int i = 0; i < count - 1; ++i) {
      int j_min = i;
      for (int j = i + 1; j < count; ++j) {
         if (strcmp(words[j], words[j_min]) < 0)
            j_min = j;
      }
      if (j_min != i)
         changer_mots(i, j_min, words);
   }
}

void ajout_noeud_fin(struct noeud *tete, char *nbr) {
   struct noeud *ptr, *temp;
   ptr = tete;
   temp = malloc(sizeof(struct noeud));
   temp->mot = nbr;
   temp->next = NULL;
   while (ptr->next != NULL)
      ptr = ptr->next;
   ptr->next = temp;
   tete->size++;
}

void parcourirTabMots(int count, char **words, struct noeud *tete, struct noeud *ptr,
                 int nb_mots) {
   for (int i = 1; i <= count; ++i) {
      if (words[i] != 0)
         ajout_noeud_fin(tete, words[i]);
   }
   trier_tab(nb_mots, words, ptr);
}

void ajout_1er_noeud(struct noeud *tete, char **words) {
   tete->mot = words[0];
   tete->next = NULL;
   tete->size = 1;
}

void init_noeud(char **words, int nb_mots, struct Stats *stats) {
   struct noeud *tete = malloc(sizeof(struct noeud));
   struct noeud *ptr = tete;
   ajout_1er_noeud(tete, words);
   parcourirTabMots(nb_mots, words, tete, ptr, nb_mots);
}

int main(int argc, char *argv[]) {
   struct Stats *stats = malloc(sizeof(struct noeud));
   FILE *file = lire_fichier(argv, argc);
   int nb_mots = trouver_nb_mots(file, stats);
   size_t size = trouver_size_fichier(file, stats);
   char **words = calloc(nb_mots, size * sizeof(char *) + 1);
   lire_lignes(file, words, &nb_mots, stats);
   init_noeud(words, nb_mots, stats);
   return 0;
}
