#include <gtk/gtk.h>
#include "ui/mainwindow.h"

/**
 * The main entry point of the Tear application. 
 * @param argc The number of entries in the argv array
 * @param argv The arguments array
 * @param argp The environment array
 */
int tear_main(int argc, char** argv, char** argp) {
    gtk_init(&argc, &argv);

    ui_create_main_window();

    gtk_main();
    return 0;
}
