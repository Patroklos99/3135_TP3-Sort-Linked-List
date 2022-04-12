/**
 *  Auteur: Renzo Arturo Salcedo
 *  Code Permanent: SALR02089408
 *  Cours: INF3135 TP3 UQAM
 *  Session: Hiver 2022
 *
 *  Classe structures.h
 *  Represente la classe structures.h contenant la structures stats utilisee toutes les autres classes.
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Stats {
    int mot_sans_doublons;
    int mots_total; //nombre total des mots dans le fichier lu.
    int nb_lignes;
    int nb_lettres;
    char lettre_frequente;
    int nb_let_freq; //nombre de la lettre la plus fréquente.
};

#endif
