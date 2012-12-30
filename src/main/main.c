#include "lib/app.h"

/**
 * The main entry point of the application. 
 * @param argc The number of entries in the argv array
 * @param argv The arguments array
 * @param argp The environment array
 */
int main(int argc, char** argv, char** argp) {
    return tear_main(argc, argv, argp);
}
