#include <check.h>
#include "lib/config.h"
#include <stdlib.h>
#include "testFiles.h"
#include "stdio.h"

static const char * REAL_FILE = "/tests/resources/simpleconfig";
static const char * BAD_FILE = "/tests/resources/badconfig";

/**
 * Helper to build a full filename
 * @param filename The filename in the source tree to build
 * @return the fill filename
 */
static char * makeFile(const char * filename) {
    int size = strlen(filename) + strlen(SOURCE_DIR) + 1;
    char * result = malloc(sizeof(char) * size);
    result[0] = 0;
    strcat(result, SOURCE_DIR);
    strcat(result, filename);
    return result;
}

START_TEST(config_load_bad_file) {
    char * filename = makeFile(BAD_FILE);

    Config config = config_load(filename);
    fail_unless(config == 0);

    free(filename);
}
END_TEST

START_TEST(config_load_good_file) {
    char * filename = makeFile(REAL_FILE);

    Config config = config_load(filename);
    fail_if(config == 0);
    
    config_free(&config);
    fail_unless(config == 0);

    free(filename);
}
END_TEST

START_TEST(config_get_simple_value) {
    char * filename = makeFile(REAL_FILE);

    Config config = config_load(filename);

    const char * value = config_get_string(config, "a");
    fail_if(value == 0);
    if (value != 0) {
        fail_unless(strncmp("1", value, 1) == 0);
    }

    value = config_get_string(config, "hello");
    fail_if(value == 0);
    if (value != 0) {
        fail_unless(strncmp("world", value, 5) == 0);
    }

    value = config_get_string(config, "foo");
    fail_if(value == 0);
    if (value != 0) {
        fail_unless(strncmp("bar!", value, 4) == 0);
    }

    value = config_get_string(config, "commented");
    fail_if(value == 0);
    if (value != 0) {
        fail_unless(strncmp("value", value, 5) == 0);
    }

    config_free(&config);
    free(filename);
}
END_TEST

START_TEST(config_get_missing_value) {
    char * filename = makeFile(REAL_FILE);

    Config config = config_load(filename);
    fail_unless(config_get_string(config, "b") == 0);
    config_free(&config);
    free(filename);
}
END_TEST

Suite* create_config_tests() {
    Suite* suite = suite_create("Config");
    TCase* tc = tcase_create("Config");
    tcase_add_test(tc, config_load_bad_file);
    tcase_add_test(tc, config_load_good_file);
    tcase_add_test(tc, config_get_simple_value);
    tcase_add_test(tc, config_get_missing_value);
    suite_add_tcase(suite, tc);
    return suite;
}
