#include <stdint.h>
#include <err.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "lecturefichier.c"
#include "statistiques.c"
#include "debutliste.c"
#include "listechainee.c"

void test_compter_lettres_1(void) {
   int nb_mots = 3;
   FILE *file = fopen("temp.txt", "w+");
   fprintf(file, "MATT NEIL OKA");
   struct Stats *stats = calloc(1, sizeof(struct Stats));  
   stats->mots_total = 3;
   rewind(file);
   char **words = calloc(3, 17 * sizeof(char *));
   lire_lignes(file, words, &nb_mots, stats);
   Liste *liste = init_liste();
   liste->first = iterer_tab_mots(nb_mots, words, liste->first);
   struct noeud *ptr = liste->first;
   CU_ASSERT_NOT_EQUAL(compter_lettres(ptr), 12);
   liberer_allocs(liste->first, words, stats, liste);
   free(stats);
}

void test_compter_lettres_0(void) {
   int nb_mots = 3;
   FILE *file = fopen("temp.txt", "w+");
   fprintf(file, "MATT NEIL OKA");
   struct Stats *stats = calloc(1, sizeof(struct Stats));  
   stats->mots_total = 3;
   rewind(file);
   char **words = calloc(3, 17 * sizeof(char *));
   lire_lignes(file, words, &nb_mots, stats);
   Liste *liste = init_liste();
   liste->first = iterer_tab_mots(nb_mots, words, liste->first);
   struct noeud *ptr = liste->first;
   CU_ASSERT_EQUAL(compter_lettres(ptr), 11);
   liberer_allocs(liste->first, words, stats, liste);
   free(stats);
}

void test_init_noeud_1(void) {
   int nb_mots = 3;
   FILE *file = fopen("temp.txt", "w+");
   fprintf(file, "MATT MATT OKA");
   struct Stats *stats = calloc(1, sizeof(struct Stats));  
   stats->mots_total = 3;
   rewind(file);
   char **words = calloc(3, 17 * sizeof(char *));
   lire_lignes(file, words, &nb_mots, stats);
   Liste *liste = init_liste();
   init_noeud(words, nb_mots, stats, liste);
   CU_ASSERT_NOT_EQUAL(stats->nb_lettres, 8);
   liberer_allocs(liste->first, words, stats, liste);
   free(stats);
}

void test_init_noeud_0(void) {
   int nb_mots = 3;
   FILE *file = fopen("temp.txt", "w+");
   fprintf(file, "MATT MATT OKA");
   struct Stats *stats = calloc(1, sizeof(struct Stats));  
   stats->mots_total = 3;
   rewind(file);
   char **words = calloc(3, 17 * sizeof(char *));
   lire_lignes(file, words, &nb_mots, stats);
   Liste *liste = init_liste();
   init_noeud(words, nb_mots, stats, liste);
   CU_ASSERT_EQUAL(stats->nb_lettres, 7);
   liberer_allocs(liste->first, words, stats, liste);
   free(stats);
}

void test_iter_tab_mots(void){
   int nb_mots = 3;
   FILE *file = fopen("temp.txt", "w+");
   fprintf(file, "MATT NEIL OKA");
   struct Stats *stats = malloc(sizeof(struct Stats));  
   stats->mots_total = 3;
   rewind(file);
   char **words = calloc(3, sizeof(char *));
   lire_lignes(file, words, &nb_mots, stats);
   Liste *liste = init_liste();
   CU_ASSERT_PTR_NOT_NULL_FATAL(liste->first = iterer_tab_mots(nb_mots, words, liste->first));
   liberer_allocs(liste->first, words, stats, liste);
   free(stats);
}

void test_init_liste(void){
   Liste *ptr = init_liste(); 
   CU_ASSERT_PTR_NOT_NULL_FATAL(ptr);
   free(ptr);
}

void test_lire_lignes(void){
   int nb_mots = 3;
   FILE *file = fopen("temp.txt", "w+");
   fprintf(file, "MATT MATT MIMMIE");
   struct Stats *stats = calloc(1, sizeof(struct Stats));  
   rewind(file);
   char **words = calloc(3, 17 * sizeof(char *));
   lire_lignes(file, words, &nb_mots, stats);
   if (NULL != file) {
      CU_ASSERT_NOT_EQUAL(stats->mot_sans_doublons, 0); 
      CU_ASSERT_NOT_EQUAL(stats->nb_let_freq, 0); 
   }
   for (int i = 0; i < 3; ++i)
      free(words[i]);
   free(words);
   free(stats);
}


void test_effacer_doublons_0(void) { 
   FILE *file = fopen("temp.txt", "w+");
   fprintf(file, "MATT MATT MIMMIE");
   rewind(file);
   int val = 3;
   int *val1 = &val;
   char **words = calloc(3, 17 * sizeof(char *));
    placer_mots_tab(file, words);
    CU_ASSERT_EQUAL(effacer_doublons(val1,words), 2);
    for (int i = 0; i < 2; ++i)
      free(words[i]);
    free(words);
    fclose(file);
}

void test_placer_mots_tab_0(void) { 
    FILE *file = fopen("temp.txt", "w+");
    fprintf(file, "MATT GEORGE MIMMIE");
    rewind(file);
    char **words = calloc(3, sizeof(char *));
    CU_ASSERT_EQUAL(placer_mots_tab(file, words), 1);
    for (int i = 0; i < 3; ++i)
      free(words[i]);
    free(words);
    fclose(file);
}

void test_trouver_lettre_freq_0(void) { 
    FILE *file = fopen("temp.txt", "w+");
    fprintf(file, "MATT GEORGE MIMMIE");
    struct Stats *stats = malloc(sizeof(struct Stats));
    stats->mot_sans_doublons = 3;
    rewind(file);
    char **words = calloc(3, sizeof(char *));
    placer_mots_tab(file, words);
    CU_ASSERT_EQUAL(trouver_lettre_frequente((char const**)words, stats), 4);
    for (int i = 0; i < 3; ++i)
      free(words[i]);
    free(words);
    free(stats); 
    fclose(file);
}

int stub_arg (int val){
if (val == 0) {
   struct Stats *stats = calloc(1, sizeof(struct Stats));  
   char* argv[] = {"TEST", "dummy", "-S", "temp.txt"};
   valider_arg_stats(4, argv, stats);  
} else {
   val = 1;
}
 return val;
}

void test_arg_stats_1(void) {
   CU_ASSERT_NOT_EQUAL(stub_arg(1), 0);  
}

void test_arg_stats_0(void) {
   CU_ASSERT_EQUAL(stub_arg(0), 0);  
}

void test_ecrire_stats_1(void) { 
    FILE *file = NULL;
    struct Stats *stats = calloc(1, sizeof(struct Stats));
    CU_ASSERT_EQUAL(ecrire_stats(file, stats), 1);
    free(stats);
}

void test_ecrire_stats_0(void) { 
    FILE *file = fopen("temp.txt", "w+");
    struct Stats *stats = calloc(1, sizeof(struct Stats));
    CU_ASSERT_EQUAL(ecrire_stats(file, stats), 0);
    free(stats);
    fclose(file);
}

void test_lire_fichier(void) { 
    FILE *file = fopen("temp.txt", "w+");
    char* argv[] = {"TEST", "temp.txt", "-s", "james"};
    FILE *ptr = lire_fichier(argv,2);
    CU_ASSERT_PTR_NOT_NULL_FATAL(ptr);
    fclose(ptr);
    fclose(file);
}

void test_trouver_nb_mots_1(void) {
    FILE *file = fopen("temp.txt", "w+");
    fprintf(file, "Hello Mike John\n");
    fprintf(file, "Hello Mike John");
    struct Stats *stats = malloc(sizeof(struct Stats));
    rewind(file);
    CU_ASSERT_NOT_EQUAL(trouver_nb_mots(file, stats), 5);
    fclose(file);
    free(stats);
}

void test_trouver_nb_mots_0(void) {
    FILE *file = fopen("temp.txt", "w+");
    fprintf(file, "Hello Mike John\n");
    fprintf(file, "Hello Mike John");
    struct Stats *stats = malloc(sizeof(struct Stats));
    rewind(file);
    CU_ASSERT_EQUAL(trouver_nb_mots(file, stats), 6);
    fclose(file);
    free(stats);
}

void test_trouver_size_1(void) {
    FILE *file = fopen("temp.txt", "w+");
    fprintf(file, "Hello");
    struct Stats *stats = malloc(sizeof(struct Stats));
    CU_ASSERT_NOT_EQUAL(trouver_size_fichier(file, stats), 4);
    fclose(file);
    free(stats);
}

void test_trouver_size_0(void) {
    FILE *file = fopen("temp.txt", "w+");
    fprintf(file, "Hello");
    struct Stats *stats = malloc(sizeof(struct Stats));
    CU_ASSERT_EQUAL(trouver_size_fichier(file, stats), 5);
    fclose(file);
    free(stats);
}

void test_compter_lignes_1(void) {
    FILE *file = fopen("temp.txt", "w");
    fprintf(file, "Hello\n");
    fprintf(file, "Hello");
    CU_ASSERT_NOT_EQUAL(compter_lignes(file), 1);
    fclose(file);
}

void test_compter_lignes_0(void) {
    FILE *file = fopen("temp.txt", "w+");
    fprintf(file, "HELLO\n");
    fprintf(file, "Jamie");
    fseek(file, 0, SEEK_SET);
    CU_ASSERT_EQUAL(compter_lignes(file), 2);
    fclose(file);
}

void test_fichier_existe_1(void) {
    FILE *file = NULL; 
    CU_ASSERT_EQUAL(valider_fichier_existe(file), 1);
}

void test_fichier_existe_0(void) {
    FILE *file = fopen("temp.txt", "w+");
    CU_ASSERT_EQUAL(valider_fichier_existe(file), 0);
    fclose(file);
}

void test_arg_invalide_1(void) {
    char* argv[] = {"TEST", "dummy", "-s", NULL};
    CU_ASSERT_EQUAL(valider_arg_invalide(4, argv), 1);
}

void test_arg_invalide_0(void) {
    char* argv[] = {"TEST", "dummy", "-S", NULL};
    CU_ASSERT_EQUAL(valider_arg_invalide(4, argv), 0);
}

void test_nbr_arg1_0(void) {
    CU_ASSERT_EQUAL(valider_nbr_args1(4), 0);
}

void test_nbr_arg1_1(void) {
    CU_ASSERT_EQUAL(valider_nbr_args1(5), 1);
}

void test_nbr_arg_0(void) {
    CU_ASSERT_EQUAL(valider_nbr_args0(1), 1);
}

void test_nbr_arg_1(void) {
    CU_ASSERT_EQUAL(valider_nbr_args0(3), 1);
}

void test_nbr_arg_2(void) {
    CU_ASSERT_EQUAL(valider_nbr_args0(2), 0);
}

int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "can't initialize test registry");
    CU_pSuite lectureSuite = CU_add_suite("lecture", NULL, NULL);
    CU_pSuite statsSuite = CU_add_suite("stats", NULL, NULL);
    CU_pSuite listeSuite = CU_add_suite("liste", NULL, NULL);
    CU_pSuite listechaineeSuite = CU_add_suite("listechainee", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "%s", CU_get_error_msg());
    CU_add_test(lectureSuite, "valider_nbr_args0(1)", test_nbr_arg_0);
    CU_add_test(lectureSuite, "valider_nbr_args0(2)", test_nbr_arg_1);
    CU_add_test(lectureSuite, "valider_nbr_args0(3)", test_nbr_arg_2);
    CU_add_test(lectureSuite, "valider_nbr_args1(4)", test_nbr_arg1_0);
    CU_add_test(lectureSuite, "valider_nbr_args1(5)", test_nbr_arg1_1);
    CU_add_test(lectureSuite, "valider_arg_invalide(4, argv)", test_arg_invalide_0);
    CU_add_test(lectureSuite, "valider_arg_invalide(4, argv)", test_arg_invalide_1);
    CU_add_test(lectureSuite, "valider_fichier_existe(file)", test_fichier_existe_0);
    CU_add_test(lectureSuite, "valider_fichier_existe(file)", test_fichier_existe_1);
    CU_add_test(lectureSuite, "compter_lignes(file)", test_compter_lignes_0);
    CU_add_test(lectureSuite, "compter_lignes(file)", test_compter_lignes_1);
    CU_add_test(lectureSuite, "trouver_size_fichier(file, stats)", test_trouver_size_0);
    CU_add_test(lectureSuite, "trouver_size_fichier(file, stats)", test_trouver_size_1);
    CU_add_test(lectureSuite, "trouver_nb_mots(file, stats)", test_trouver_nb_mots_0);
    CU_add_test(lectureSuite, "trouver_nb_mots(file, stats)", test_trouver_nb_mots_1);
    CU_add_test(lectureSuite, "lire_fichier(argv, 2)", test_lire_fichier);
    CU_add_test(statsSuite, "ecrire_stats(file, stats)", test_ecrire_stats_0);
    CU_add_test(statsSuite, "ecrire_stats(file, stats)", test_ecrire_stats_1);
    CU_add_test(statsSuite, "stub_arg", test_arg_stats_0);
    CU_add_test(statsSuite, "stub_arg", test_arg_stats_1);
    CU_add_test(listeSuite, "trouver_lettre_frequente((char const**)words, stats)", test_trouver_lettre_freq_0);
    CU_add_test(listeSuite, "placer_mots_tab(file, words)", test_placer_mots_tab_0);
    CU_add_test(listeSuite, "effacer_doublons(&val, words)", test_effacer_doublons_0);
    CU_add_test(listeSuite, "lire_lignes(file, words, &nb_mots, stats)", test_lire_lignes);
    CU_add_test(listechaineeSuite, "init_liste()", test_init_liste);
    CU_add_test(listechaineeSuite, "iterer_tab_mots(nb_mots, words, liste->first)", test_iter_tab_mots);
    CU_add_test(listechaineeSuite, "init_noeud(words, nb_mots, stats, liste)", test_init_noeud_0);
    CU_add_test(listechaineeSuite, "init_noeud(words, nb_mots, stats, liste)", test_init_noeud_1);
    CU_add_test(listechaineeSuite, "int compter_lettres(struct noeud *ptr)", test_compter_lettres_0);
    CU_add_test(listechaineeSuite, "int compter_lettres(struct noeud *ptr)", test_compter_lettres_1);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
