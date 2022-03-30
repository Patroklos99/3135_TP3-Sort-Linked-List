#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "listechainee.h"

Liste *init_liste() {
   Liste *liste = malloc(sizeof(Liste));
   liste->first = NULL;
   liste->size = 0;
   return liste;
}

void liberer_allocs(struct noeud *tete, char **words, struct Stats *stats,
        Liste *liste) {
   struct noeud *tmp;
   while (tete != NULL) {
      tmp = tete;
      tete = tete->next;
      free(tmp);
   }
   for (int i = 0; i < stats->mots_total; ++i)
      free(words[i]);
   free(words);
   free(liste);
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

void afficher_mots(struct noeud *tete) {
   struct noeud *ptr = tete;
   for (int a = 0; ptr != NULL; ++a) {
      printf("%s\n", ptr->mot);
      ptr = ptr->next;
   }
}

void chercher_position(struct noeud *tete, struct noeud *temp) {
   struct noeud *cur = tete;
   while (cur->next != NULL && strcmp(temp->mot, cur->next->mot) >= 0)
      cur = cur->next;
   temp->next = cur->next;
   cur->next = temp;
}

struct noeud* ajout_noeud(struct noeud *tete, char *mot) {
   struct noeud *temp;
   temp = malloc(sizeof(struct noeud));
   temp->mot = mot;
   temp->next = NULL;
   if (tete == NULL || strcmp(temp->mot, tete->mot) < 0) {
      temp->next = tete;
      return temp;
   } else
      chercher_position(tete, temp);
   return tete;
}

struct noeud* iterer_tab_mots(int nb_mots, char **words, struct noeud *tete) {
   for (int i = 0; i < nb_mots; ++i) {
      if (words[i] != 0)
         tete = ajout_noeud(tete, words[i]);
   }
   afficher_mots(tete);
   return tete;
}

void init_noeud(char **words, int nb_mots, struct Stats *stats, Liste *liste) {
   liste->first = iterer_tab_mots(nb_mots, words, liste->first);
   struct noeud *ptr = liste->first;
   compter_lettres(ptr, stats);
}
