#include <gtk/gtk.h>
#include "ui/mainwindow.h"
#include "ui/drives.h"
#include "ui/formats.h"

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

    ui_drives_register(0, "HL-DT-ST DVD+-RW GT10N        Rev: A104");

    ui_create_main_window();
    ui_show_main_window(true);

    gtk_main();
    return 0;
}
