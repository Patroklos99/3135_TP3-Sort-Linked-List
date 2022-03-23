#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

void afficher_mots(struct noeud *ptr) {
   int a = 0;
   while (ptr != NULL) {
      printf("Noeud#%d ->%s\n", a, ptr->mot);
      ptr = ptr->next;
      a++;
   }
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
   afficher_mots(ptr);
}

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

void ajout_1er_noeud(struct noeud *tete, char **words) {
   tete->mot = words[0];
   tete->next = NULL;
   tete->size = 1;
}

void
parcourirTabMots(int count, char **words, struct noeud *tete, struct noeud *ptr,
                 int nb_mots) {
   for (int i = 1; i <= count; ++i) {
      if (words[i] != 0)
         ajout_noeud_fin(tete, words[i]);
   }
   trier_tab(nb_mots, words, ptr);
}

void liberer_allocs(struct noeud *tete, char **words) {
   struct noeud *tmp;
   while (tete != NULL) {
      tmp = tete;
      tete = tete->next;
      free(tmp);
   }
   free(words);
}

void modifier_tab_size(int *b, int *count, char **words) {
   for (int k = *b; k < *count; k++) {
      words[k] = words[k + 1];
      words[*count + 1] = 0;
   }
   (*count)--;
   (*b)--;
}

void effacer_doublons(int *count, char **words) {
   for (int a = 0; a < *count; ++a) {
      if (words[a] != 0) {
         for (int b = 0; b < *count; ++b) {
            if (strcmp(words[a], words[b]) == 0 && b != a)
               modifier_tab_size(&b, count, words);
         }
      }
   }
}

void compter_lignes(FILE *file, struct Stats *stats) {
   int compteur = 0;
   char ligne[80];
   while (fgets(ligne, 80, file)) {
      compteur++;
   }
   stats->nb_lignes = compteur;
}

int trouver_nb_mots(FILE *file, struct Stats *stats) {
   int x = 0;
   char ligne[80];
   while (fgets(ligne, 81, file)) {
      char *word;
      word = strtok(ligne, " ,.-\n");
      while (word != NULL) {
         word = strtok(NULL, " ,.-\n");
         ++x;
      }
   }
   stats->mots_totaux = x;
   return x;
}

size_t trouver_size_fichier(FILE *file, struct Stats *stats) {
   fseek(file, 0, SEEK_END);
   size_t size = ftell(file);
   fseek(file, 0, SEEK_SET);
   compter_lignes(file, stats);
   fseek(file, 0, SEEK_SET);
   return size;
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
      if (array[(int)str[i]] > max) {
         max = array[(int)str[i]];
         index = i;
         stats->lettre_frequente = (char) str[index];
         stats->nb_let_freq = max;
      }
   }
}

void placermots_tabs(char ligne[80], char **words, int *i) {
   char *word = strtok(ligne, " ,.-\n");
   while (word != NULL) {                  // strtok result controls the loop
      words[(*i)++] = strdup(word);
      word = strtok(NULL, " ,.-\n");
   }
}

void lire_lignes(FILE *file, char **words, int *nb_mots, struct Stats *stats) {
   int i = 0;
   char ligne[80];
   while (fgets(ligne, 81, file)) {
      placermots_tabs(ligne, words,  &i);
   }
   effacer_doublons(nb_mots, words);
   stats->mot_sans_doublons = *nb_mots;
   trouver_lettre_frequente((char const **) words, stats);
   fclose(file);
}

void compter_lettres(struct noeud *ptr, struct Stats *stats) {
   int nb_lettres = 0;
   while (ptr != NULL) {
      for (int i = 0; i < (int) strlen(ptr->mot); ++i) {
         if (ptr->mot[i] != '\0')
            nb_lettres++;
      }
      ptr = ptr->next;
   }
   stats->nb_lettres = nb_lettres;
}

void init_noeud(char **words, int nb_mots, struct Stats *stats) {
   struct noeud *tete = malloc(sizeof(struct noeud));
   struct noeud *ptr = tete;
   ajout_1er_noeud(tete, words);
   parcourirTabMots(nb_mots, words, tete, ptr, nb_mots);
   compter_lettres(ptr, stats);
   liberer_allocs(tete, words);
}

void ecrire_stats(int argc, char *argv[], struct Stats *stats) {
   if (argc == 4 && strcmp(argv[2], "-S") == 0) {
      FILE *file = fopen(argv[3], "w");
      if (file != NULL) {
         fprintf(file, "Le nb de mots (sans doublons) est: %d.\n",
                 stats->mot_sans_doublons);
         fprintf(file, "Le nb de mots avec doublons est: %d.\n", stats->mots_totaux);
         fprintf(file, "Le nb de lignes est: %d.\n", stats->nb_lignes);
         fprintf(file, "Le nb de lettres des mots (sans doublons) est: %d.\n",
                 stats->nb_lettres);
         fprintf(file, "La lettre la plus frequente (sans doublons) est: %c, "
                       "apparait %d fois.\n", stats->lettre_frequente, stats->nb_let_freq);
      }
      fclose(file);
   }
}

int main(int argc, char *argv[]) {
   struct Stats *stats = malloc(sizeof(struct noeud));
   FILE *file = lire_fichier(argv, argc);
   int nb_mots = trouver_nb_mots(file, stats);
   size_t size = trouver_size_fichier(file, stats);
   char **words = calloc(nb_mots, size * sizeof(char *) + 1);
   lire_lignes(file, words, &nb_mots, stats);
   init_noeud(words, nb_mots, stats);
   ecrire_stats(argc, argv, stats);
   return 0;
}
