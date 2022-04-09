#include <err.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

int fac(int n) {
    int f = 1;
    while (n > 1)
        f *= --n;
    return f;
}

void test_fac_0(void) {
    CU_ASSERT_EQUAL(fac(0), 1);
}

int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "can't initialize test registry");
    CU_pSuite facSuite = CU_add_suite("fac", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "%s", CU_get_error_msg());
    CU_add_test(facSuite, "fac(0)", test_fac_0);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
