#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "listechainee.h"

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
