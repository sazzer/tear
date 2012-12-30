#include <gtk/gtk.h>
#include "ui/mainwindow.h"
#include "ui/drives.h"
#include "drives.h"
#include "ui/formats.h"
#include <stdio.h>

/** The list of CD Drive Information */
static CDList cdList;

/**
 * The main entry point of the Tear application. 
 * @param argc The number of entries in the argv array
 * @param argv The arguments array
 * @param argp The environment array
 */
int tear_main(int argc, char** argv, char** argp) {
    gtk_init(&argc, &argv);

    ui_formats_register(0, "MP3");
    ui_formats_register(1, "Ogg Vorbis");
    ui_formats_register(2, "FLAC");
    ui_formats_register(3, "WAV");

    cdList = cd_list_new();
    int i;
    for (i = 0; i < cd_list_size(cdList); ++i) {
        const char * name = cd_list_get_name(cdList, i);
        ui_drives_register(i, name);
        printf("Found CD Drive %d: %s\n", i, name);
    }

    ui_create_main_window();
    ui_show_main_window(true);

    gtk_main();
    return 0;
}
