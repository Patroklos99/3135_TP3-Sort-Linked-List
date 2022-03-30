#ifndef LISTECHAINEE_H
#define LISTECHAINEE_H
#include <stdio.h>
#include "structures.h"

typedef struct {
   struct noeud *first;
   unsigned int size; 
} Liste;

struct noeud {
   char *mot;
   struct noeud *next;
};

/*
 * Initialise la liste.
 *
 * @return tete Pointeur vers la liste
 * */
Liste *init_liste();

/*
 * Initialise le noeud tête et un ptr d'itération.
 *
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @param nb_mots nombre de mots dans le fichier d'entrée.
 * @param stats pointeur vers la structure statistiques
 * @param Liste pointeur vers la structure Liste
 * */
void init_noeud(char **words, int nb_mots, struct Stats *stats, Liste *liste);

/*
 * Itere à travers le pointeur de pointeur **words
 *
 * @param nb_mots nombre de mots dans le fichier d'entrée.
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @param tete struct du 1er noeud de la liste chainée.
 * */
struct noeud* iterer_tab_mots(int nb_mots, char **words, struct noeud *tete);

/*
 * Crée et lie le nouveau noeud à la fin de la liste chainée
 *
 * @param tete struct du 1er noeud de la liste chainée
 * @param mot mot correspondant à sa position sur **words.
 * */
struct noeud* ajout_noeud(struct noeud *tete, char *mot);

/*
 * Parcours le liste chainée en affichant le mot correspondant.
 *
 * @param ptr pointeur pointe vers la tête de la liste chainée,pour iteration
 * */
void afficher_mots(struct noeud *tete);

/*
 * Compte le nb de lettres dans la liste (sans les doublons)
 *
 * @param ptr pointeur pointe vers la tête de la liste chainée, pour iteration.
 * @param stats pointeur vers la structure statistiques
 * */
void compter_lettres(struct noeud *ptr, struct Stats *stats);

/*
 * Libere (alloc. dyn.) tous les noeuds de la liste chainée, les pointeurs
 * dans **words, incluant ce dernier.
 *
 * @param tete struct du 1er noeud de la liste chainée
 * @param words pointeur de pointeur vers leur mot correspondant.
 * @param stats pointeur vers la structure statistiques
 * @param liste pointeur vers la structure Liste.
 * */
void liberer_allocs(struct noeud *tete, char **words, struct Stats *stats,
                    Liste *liste);

/*
 * Cherche position correcte à inserer le nouveau noeud
 *
 * @param tete struct du 1er noeud de la liste chainée
 * @param pointeur vers le noeud temporaire avant insertion.
 * */
void chercher_position(struct noeud *tete, struct noeud *temp);

#endif
