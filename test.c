#include <err.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "lecturefichier.c"

void test_lire_fichier(void) { 
    FILE *file = fopen("temp.txt", "w+");
    char* argv[] = {"TEST", "temp.txt", "-s", NULL};
    struct Stats *stats = malloc(sizeof(struct Stats));
    CU_ASSERT_PTR_NOT_NULL_FATAL(lire_fichier(argv, 2));
    free(stats);
    fclose(file);
}

void test_trouver_nb_mots_0(void) {
    FILE *file = fopen("temp.txt", "w+");
    fprintf(file, "Hello Mike John");
    struct Stats *stats = malloc(sizeof(struct Stats));
    CU_ASSERT_NOT_EQUAL(trouver_nb_mots(file, stats), 3);
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
    CU_pSuite facSuite = CU_add_suite("fac", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "%s", CU_get_error_msg());
    CU_add_test(facSuite, "valider_nbr_args0(1)", test_nbr_arg_0);
    CU_add_test(facSuite, "valider_nbr_args0(2)", test_nbr_arg_1);
    CU_add_test(facSuite, "valider_nbr_args0(3)", test_nbr_arg_2);
    CU_add_test(facSuite, "valider_nbr_args1(4)", test_nbr_arg1_0);
    CU_add_test(facSuite, "valider_nbr_args1(5)", test_nbr_arg1_1);
    CU_add_test(facSuite, "valider_arg_invalide(4, argv)", test_arg_invalide_0);
    CU_add_test(facSuite, "valider_arg_invalide(4, argv)", test_arg_invalide_1);
    CU_add_test(facSuite, "valider_fichier_existe(file)", test_fichier_existe_0);
    CU_add_test(facSuite, "valider_fichier_existe(file)", test_fichier_existe_1);
    CU_add_test(facSuite, "compter_lignes(file)", test_compter_lignes_0);
    CU_add_test(facSuite, "compter_lignes(file)", test_compter_lignes_1);
    CU_add_test(facSuite, "trouver_size_fichier(file, stats)", test_trouver_size_0);
    CU_add_test(facSuite, "trouver_size_fichier(file, stats)", test_trouver_size_1);
    CU_add_test(facSuite, "trouver_nb_mots(file, stats)", test_trouver_nb_mots_0);
    CU_add_test(facSuite, "lire_fichier(argv, 2)", test_lire_fichier);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
