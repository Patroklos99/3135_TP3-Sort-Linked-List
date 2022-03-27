#define _POSIX_C_SOURCE 200809L
const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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
    int mots_total; //nombre total des mots dans le fichier lu.
    int nb_lignes;
    int nb_lettres;
    char lettre_frequente;
    int nb_let_freq; //nombre de la lettre la plus fréquente.
};

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

/*
 * Libere (alloc. dyn.) tous les noeuds de la liste chainée, les pointeurs
 * dans **words, incluant ce dernier.
 *
 * @param tete struct du 1er noeud de la liste chainée
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @param stats pointeur vers la structure statistiques
 * */
void liberer_allocs(struct noeud *tete, char **words, struct Stats *stats) {
   struct noeud *tmp;
   while (tete != NULL) {
      tmp = tete;
      tete = tete->next;
      free(tmp);
   }
   for (int i = 0; i < stats->mots_total; ++i)
      free(words[i]);
   free(words);
}

/*
 * Trouve le nombre de lignes dans le fichier d'entrée.
 *
 * @param *file pointeur du fichier à lire.
 * @param stats pointeur vers la structure statistiques
 * */
void compter_lignes(FILE *file, struct Stats *stats) {
   int compteur = 0;
   char ligne[80];
   while (fgets(ligne, 80, file))
      compteur++;
   stats->nb_lignes = compteur;
}

/*
 * Trouve la taille du fichier d'entrée.
 *
 * @param *file pointeur du fichier à lire.
 * @param stats pointeur vers la structure statistiques
 *
 * return la taille du fichier.
 * */
size_t trouver_size_fichier(FILE *file, struct Stats *stats) {
   fseek(file, 0, SEEK_END);
   size_t size = ftell(file);
   fseek(file, 0, SEEK_SET);
   compter_lignes(file, stats);
   fseek(file, 0, SEEK_SET);
   return size;
}

/*
 * Trouve le nombre de mots dans le fichier d'entrée
 *
 * @param *file pointeur du fichier à lire.
 * @param stats pointeur vers la structure statistiques
 *
 * return le nombre de mots trouvés.
 * */
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

/*
 * Compte le nb de lettres dans la liste (sans les doublons)
 *
 * @param ptr pointeur pointe vers la tête de la liste chainée, pour iteration.
 * @param stats pointeur vers la structure statistiques
 * */
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

/*
 * Parcours le liste chainée en affichant le mot correspondant.
 *
 * @param ptr pointeur pointe vers la tête de la liste chainée,pour iteration
 * */
void afficher_mots(struct noeud *ptr) {
   for (int a = 0; ptr != NULL; ++a) {
      printf("%s\n", ptr->mot);
      ptr = ptr->next;
   }
}

/*
 * Crée et lie le nouveau noeud à la fin de la liste chainée
 *
 * @param tete struct du 1er noeud de la liste chainée
 * @param mot mot correspondant à sa position sur **words.
 * */
void ajout_noeud_fin(struct noeud *tete, char *mot) {
   struct noeud *ptr, *temp;
   ptr = tete;
   temp = malloc(sizeof(struct noeud));
   temp->mot = mot;
   temp->next = NULL;
   while (ptr->next != NULL)
      ptr = ptr->next;
   ptr->next = temp;
   tete->size++;
}

/*
 * Itere à travers le pointeur de pointeur **words
 *
 * @param nb_mots nombre de mots dans le fichier d'entrée.
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @param tete struct du 1er noeud de la liste chainée.
 * @param ptr struct pointe vers la tête de la liste chainée, pour iteration.
 * */
void iterer_tab_mots(int nb_mots, char **words, struct noeud *tete,
                     struct noeud *ptr) {
   for (int i = 1; i < nb_mots; ++i) {
      if (words[i] != 0)
         ajout_noeud_fin(tete, words[i]);
   }
   afficher_mots(ptr);
}

/*
 * Ajoute le 1er noeud de la liste chainée
 *
 * @param tete struct du 1er noeud de la liste chainée
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @param nb_mots nombre de mots dans le fichier d'entrée.
 * @param ptr struct pointe vers la tête de la liste chainée, pour iteration.
 * @param stats pointeur vers la structure statistiques
 * */
void ajout_1er_noeud(struct noeud *tete, char **words, int nb_mots, struct noeud
*ptr, struct Stats *stats) {
   tete->mot = words[0];
   tete->next = NULL;
   tete->size = 1;
   iterer_tab_mots(nb_mots, words, tete, ptr);
   compter_lettres(ptr, stats);
}

/*
 * Initialise le noeud tête et un ptr d'itération.
 *
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @param nb_mots nombre de mots dans le fichier d'entrée.
 * @param stats pointeur vers la structure statistiques
 * */
void init_noeud(char **words, int nb_mots, struct Stats *stats) {
   struct noeud *tete = malloc(sizeof(struct noeud));
   struct noeud *ptr = tete;
   ajout_1er_noeud(tete, words, nb_mots, ptr, stats);
   liberer_allocs(tete, words, stats);
}

/*
 * Écrit dans le fichier de sortie.
 *
 * @param *file le pointeur vers le fichier à écrire.
 * @param stats pointeur vers la structure statistiques
 * */
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

/*
 * Valide le nb d'arguments avant l'écriture dans le fichier.
 *
 * @param argv reference vers les arguments donnés.
 * @param argc nb d'arguments.
 * @param stats pointeur vers la structure statistiques
 * */
void valider_arg_stats(int argc, char *argv[], struct Stats *stats) {
   if (argc == 4 && strcmp(argv[2], "-S") == 0) {
      FILE *file = fopen(argv[3], "w");
      if (file != NULL)
         ecrire_stats(file, stats);
      fclose(file);
   }
   free(stats);
}

int main(int argc, char *argv[]) {
   struct Stats *stats = malloc(sizeof(struct noeud));
   FILE *file = lire_fichier(argv, argc);
   int nb_mots = trouver_nb_mots(file, stats);
   size_t size = trouver_size_fichier(file, stats);
   char **words = calloc(nb_mots, size * sizeof(char *));
   lire_lignes(file, words, &nb_mots, stats);
   init_noeud(words, nb_mots, stats);
   valider_arg_stats(argc, argv, stats);
   return 0;
}

