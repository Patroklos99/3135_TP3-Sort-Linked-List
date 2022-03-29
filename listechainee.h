#ifndef LISTECHAINEE_H
#define LISTECHAINEE_H
#include <stdio.h>
#include "structures.h"

void init_noeud(char **words, int nb_mots, struct Stats *stats);
struct noeud* iterer_tab_mots(int nb_mots, char **words, struct noeud *tete);
struct noeud* ajout_noeud(struct noeud *tete, char *mot);
void afficher_mots(struct noeud *tete);
void compter_lettres(struct noeud *ptr, struct Stats *stats);
void liberer_allocs(struct noeud *tete, char **words, struct Stats *stats);
void chercher_position(struct noeud *tete, struct noeud *temp);

#endif
