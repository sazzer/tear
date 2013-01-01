#include <gtk/gtk.h>
#include "ui/mainwindow.h"
#include "ui/config.h"
#include "ui/drives.h"
#include "drives.h"
#include "ui/formats.h"
#include <stdio.h>
#include <glib.h>
#include "config.h"
#include <stdbool.h>
#include "settings.h"

/** The name of the filename to load config from */
static const char * CONFIG_FILENAME = ".tear";

/** The default option to use for the filename */
static const char * DEFAULT_FILENAME_OPTION = "%a/%t/%d.%e";

/** The list of CD Drive Information */
static CDList cdList;

/** the config object */
static Config config;

/** Determination of whether we're configured or not */
static bool wasConfigured;
/**
 * Load the User Config object
 * @return the loaded config object, or NULL if one couldn't be loaded
 */
void loadUserConfig() {
    const char * userConfigDir = g_get_user_config_dir();
    char * configFile = g_build_filename(userConfigDir, CONFIG_FILENAME, NULL);

    config = config_load(configFile);

    g_free(configFile);
}

/**
 * Helper to show the initial window
 */
void showInitialWindow() {
    if (wasConfigured) {
        ui_show_main_window(true);
        ui_show_config_window(false);
    }
    else {
        ui_show_config_window(true);
        ui_show_main_window(false);
    }
}

/**
 * Handler when the Save button is pressed on the config dialog
 */
void onConfigSave() {
    const char * userConfigDir = g_get_user_config_dir();
    char * configFile = g_build_filename(userConfigDir, CONFIG_FILENAME, NULL);

    config_save(config, configFile);

    g_free(configFile);

    wasConfigured = true;
    showInitialWindow();
}

/**
 * Handler when the Cancel button is pressed on the config dialog
 */
void onConfigCancel() {
    showInitialWindow();
}

/**
 * Handler when the Config button is pressed on the main window
 */
void onConfigClicked() {
    ui_show_config_window(true);
    ui_show_main_window(false);
}

/**
 * The main entry point of the Tear application. 
 * @param argc The number of entries in the argv array
 * @param argv The arguments array
 * @param argp The environment array
 */
int tear_main(int argc, char** argv, char** argp) {
    gtk_init(&argc, &argv);
    
    wasConfigured = true;
    loadUserConfig();
    if (config == NULL) {
        wasConfigured = false;
        config = config_new();
        config_set_string(config, BASE_DIR_SETTING, g_get_user_special_dir(G_USER_DIRECTORY_MUSIC));
        config_set_string(config, FILENAME_SETTING, DEFAULT_FILENAME_OPTION);
    }

    ui_formats_register(0, "MP3");
    ui_formats_register(1, "Ogg Vorbis");
    ui_formats_register(2, "FLAC");
    ui_formats_register(3, "WAV");

    cdList = drive_list_new();
    int i;
    for (i = 0; i < drive_list_size(cdList); ++i) {
        const char * name = drive_list_get_name(cdList, i);
        ui_drives_register(i, name);
        printf("Found CD Drive %d: %s\n", i, name);
    }

    ui_create_main_window(onConfigClicked);
    ui_create_config_window(config, onConfigSave, onConfigCancel);

    showInitialWindow();

    gtk_main();

    drive_list_free(&cdList);
    config_free(&config);
    return 0;
}
