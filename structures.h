#ifndef STRUCTURES_H
#define STRUCTURES_H

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

#endif
