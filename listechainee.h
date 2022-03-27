#ifndef LISTECHAINEE_H
#define LISTECHAINEE_H
#include <stdio.h>
#include "structures.h"

void init_noeud(char **words, int nb_mots, struct Stats *stats);
void ajout_1er_noeud(struct noeud *tete, char **words, int nb_mots, struct noeud
*ptr, struct Stats *stats);
void iterer_tab_mots(int nb_mots, char **words, struct noeud *tete,
struct noeud *ptr);
void ajout_noeud_fin(struct noeud *tete, char *mot);
void afficher_mots(struct noeud *ptr);
void compter_lettres(struct noeud *ptr, struct Stats *stats);
void liberer_allocs(struct noeud *tete, char **words, struct Stats *stats);

#endif
