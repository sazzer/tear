#include "config.h"
#include <gtk/gtk.h>
#include "intl.h"
#include "settings.h"

static const int BASE_DIR_ROW = 0;
static const int OUTPUT_FORMAT_ROW = 1;
static const int BUTTONS_ROW = 2;

/** The actual config window */
static GtkWidget* window;
/** The grid for the config window */
static GtkWidget* grid;
/** The config object to use */
static Config tearConfig;
/** The callback when the config is saved */
static SaveCallback saveCallback;
/** The callback when the config is cancelled */
static CancelCallback cancelCallback;

/**
 * Actually create and configure the config window
 */
static void createConfigWindow() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), _("Tear - Config"));
    gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_deletable(GTK_WINDOW(window), FALSE);
}

/**
 * Actually create and configure the grid that contains the widgets in
 * the config window
 */
static void createGrid() {
    grid = gtk_grid_new();
    gtk_grid_insert_column(GTK_GRID(grid), 0);
    gtk_grid_insert_column(GTK_GRID(grid), 1);
    gtk_widget_set_hexpand(grid, true);
    gtk_widget_set_vexpand(grid, false);
    gtk_container_add(GTK_CONTAINER(window), grid);
}

/**
 * Helper to create a new row in the grid with a label in the first column
 * @param row The row to create
 * @param label The text of the label
 * @return the widget that was created for the label
 */
static GtkWidget* createLabelledRow(int row, const char* label) {
    GtkWidget* labelWidget;
    gtk_grid_insert_row(GTK_GRID(grid), row);

    labelWidget = gtk_label_new(label);
    gtk_grid_attach(GTK_GRID(grid), labelWidget, 0, row, 1, 1);

    return labelWidget;
}

/** The entry for the baseDir */
static GtkWidget* baseDirEntry;

/**
 * Create the baseDir row
 */
static void createBaseDirRow() {
    createLabelledRow(BASE_DIR_ROW, _("Base"));

    baseDirEntry = gtk_file_chooser_button_new(_("Select Base Directory"), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
    gtk_widget_set_hexpand(baseDirEntry, true);
    gtk_grid_attach(GTK_GRID(grid), baseDirEntry, 1, BASE_DIR_ROW, 1, 1);
}

/** The entry for the outputFormat */
static GtkWidget* outputFormatEntry;

/**
 * Create the outputFormat row
 */
static void createOutputFormatRow() {
    createLabelledRow(OUTPUT_FORMAT_ROW, _("Filename"));

    outputFormatEntry = gtk_entry_new();
    gtk_widget_set_hexpand(outputFormatEntry, true);
    gtk_grid_attach(GTK_GRID(grid), outputFormatEntry, 1, OUTPUT_FORMAT_ROW, 1, 1);
}

/** The button to save the config */
static GtkWidget* saveButton;

/** The button to cancel the config */
static GtkWidget* cancelButton;

/**
 * Create the buttons row
 */
static void createButtonsRow() {
    GtkWidget* buttonsBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_grid_insert_row(GTK_GRID(grid), BUTTONS_ROW);
    gtk_grid_attach(GTK_GRID(grid), buttonsBox, 0, BUTTONS_ROW, 2, 1);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(buttonsBox), GTK_BUTTONBOX_CENTER);
    gtk_widget_set_hexpand(buttonsBox, true);

    saveButton = gtk_button_new_with_label(_("Save"));
    gtk_container_add(GTK_CONTAINER(buttonsBox), saveButton);

    cancelButton = gtk_button_new_with_label(_("Cancel"));
    gtk_container_add(GTK_CONTAINER(buttonsBox), cancelButton);
}

/**
 * Handle when the Save button is triggered
 */
static void onSave() {
    if (saveCallback) {
        saveCallback();
    }
}

/**
 * Handle when the Cancel button is triggered
 */
static void onCancel() {
    if (cancelCallback) {
        cancelCallback();
    }
}

/**
 * Register callbacks on all of the widgets
 */
static void registerCallbacks() {
    g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(onCancel), NULL);
    g_signal_connect_swapped(G_OBJECT(cancelButton), "clicked", G_CALLBACK(onCancel), NULL);
    g_signal_connect_swapped(G_OBJECT(saveButton), "clicked", G_CALLBACK(onSave), NULL);
}

/**
 * Repopulate the config dialog based on the values in the config object
 */
static void repopulateDialog() {
    const char * baseDir = config_get_string(tearConfig, BASE_DIR_SETTING);
    if (baseDir) {
        printf("Setting base dir to: %s\n", baseDir);
        gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(baseDirEntry), baseDir);
    }

    const char * outputFormat = config_get_string(tearConfig, FILENAME_SETTING);
    if (outputFormat) {
        printf("Setting output format to: %s\n", outputFormat);
        gtk_entry_set_text(GTK_ENTRY(outputFormatEntry), outputFormat);
    }
}

/**
 * Actually create the config window of the application
 * @param config The configuration object to show and manipulate
 * @param sc The callback to call when the config is saved
 * @param cc The callback to call when the config is cancelled
 */
void ui_create_config_window(Config config, SaveCallback sc, CancelCallback cc) {
    tearConfig = config;
    saveCallback = sc;
    cancelCallback = cc;

    createConfigWindow();
    createGrid();
    createBaseDirRow();
    createOutputFormatRow();
    createButtonsRow();
    registerCallbacks();
}

/**
 * Show or hide the config window
 * @param show True to show it, False to hide it
 */
void ui_show_config_window(bool show) {
    if (show) {
        repopulateDialog();
        gtk_widget_show_all(window);
    }
    else {
        gtk_widget_hide(window);
    }
}
