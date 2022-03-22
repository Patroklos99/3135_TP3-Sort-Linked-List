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

int main(int argc, char *argv[]) {
	struct Stats *stats = malloc(sizeof(struct noeud));
   FILE *file = lire_fichier(argv, argc);
}

