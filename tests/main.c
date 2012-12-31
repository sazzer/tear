#include <check.h>
#include <stdlib.h>

Suite* create_config_tests();

/**
 * Main entry point into the tests
 */
int main(int argc, char** argv) {

    Suite* mainSuite = suite_create("Tear");
    SRunner* runner = srunner_create(mainSuite);
    srunner_add_suite(runner, create_config_tests());

    srunner_run_all(runner, CK_ENV);
    int numberFailed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (numberFailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
