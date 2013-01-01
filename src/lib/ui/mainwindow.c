#include <gtk/gtk.h>
#include "intl.h"
#include "mainwindow.h"
#include "formats.h"
#include "drives.h"

static const int DRIVE_ROW = 0;
static const int AUTHOR_ROW = 1;
static const int TITLE_ROW = 2;
static const int DISC_ROW = 3;
static const int FORMAT_ROW = 4;
static const int BUTTONS_ROW = 5;

/** The config callback to use */
static ConfigCallback configCallback;

/** The actual main window of the application */
static GtkWidget* window;

/** The grid for the main window */
static GtkWidget* grid;

/**
 * Actually create and configure the main window
 */
static void createMainWindow() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), _("Tear"));
    gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

/**
 * Actually create and configure the grid that contains the widgets in
 * the main window
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

/** The entry for the author */
static GtkWidget* authorEntry;

/**
 * Create the author row
 */
static void createAuthorRow() {
    createLabelledRow(AUTHOR_ROW, _("Author"));

    authorEntry = gtk_entry_new();
    gtk_widget_set_hexpand(authorEntry, true);
    gtk_grid_attach(GTK_GRID(grid), authorEntry, 1, AUTHOR_ROW, 1, 1);
}

/** The entry for the title */
static GtkWidget* titleEntry;

/**
 * Create the title row
 */
static void createTitleRow() {
    createLabelledRow(TITLE_ROW, _("Title"));

    titleEntry = gtk_entry_new();
    gtk_widget_set_hexpand(titleEntry, true);
    gtk_grid_attach(GTK_GRID(grid), titleEntry, 1, TITLE_ROW, 1, 1);
}

/** The entry for the disc */
static GtkWidget* discEntry;

/**
 * Create the disc row
 */
static void createDiscRow() {
    createLabelledRow(DISC_ROW, _("Disc"));

    discEntry = gtk_spin_button_new_with_range(0, 100, 1);
    gtk_widget_set_hexpand(discEntry, true);
    gtk_grid_attach(GTK_GRID(grid), discEntry, 1, DISC_ROW, 1, 1);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(discEntry), 1);
}

/** The entry for the format */
static GtkWidget* formatEntry;

/**
 * Create the format row
 */
static void createFormatRow() {
    createLabelledRow(FORMAT_ROW, _("Format"));

    formatEntry = gtk_combo_box_new_with_model(ui_formats_get_model());
    gtk_widget_set_hexpand(formatEntry, true);
    gtk_grid_attach(GTK_GRID(grid), formatEntry, 1, FORMAT_ROW, 1, 1);

    GtkCellRenderer* cellRenderer = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(formatEntry), cellRenderer, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(formatEntry), cellRenderer, "text", 1, NULL);

    gtk_combo_box_set_active(GTK_COMBO_BOX(formatEntry), 0);
}

/** The entry for the drive */
static GtkWidget* driveEntry;

/**
 * Create the drive row
 */
static void createDriveRow() {
    createLabelledRow(DRIVE_ROW, _("Drive"));

    driveEntry = gtk_combo_box_new_with_model(ui_drives_get_model());
    gtk_widget_set_hexpand(driveEntry, true);
    gtk_grid_attach(GTK_GRID(grid), driveEntry, 1, DRIVE_ROW, 1, 1);

    GtkCellRenderer* cellRenderer = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(driveEntry), cellRenderer, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(driveEntry), cellRenderer, "text", 1, NULL);

    gtk_combo_box_set_active(GTK_COMBO_BOX(driveEntry), 0);
}

static void onConfig() {
    if (configCallback) {
        configCallback();
    }
}

/** The button to actually start ripping */
static GtkWidget* goButton;
/** The button to open the config dialog */
static GtkWidget* configButton;
/**
 * Create the buttons row
 */
static void createButtonsRow() {
    GtkWidget* buttonsBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

    gtk_grid_insert_row(GTK_GRID(grid), BUTTONS_ROW);
    gtk_grid_attach(GTK_GRID(grid), buttonsBox, 0, BUTTONS_ROW, 2, 1);
    gtk_button_box_set_layout(GTK_BUTTON_BOX(buttonsBox), GTK_BUTTONBOX_END);
    gtk_widget_set_hexpand(buttonsBox, true);

    configButton = gtk_button_new_with_label(_("Config"));
    gtk_container_add(GTK_CONTAINER(buttonsBox), configButton);
    g_signal_connect_swapped(G_OBJECT(configButton), "clicked", G_CALLBACK(onConfig), NULL);

    goButton = gtk_button_new_with_label(_("Go"));
    gtk_container_add(GTK_CONTAINER(buttonsBox), goButton);
}

/**
 * Actually create the main window of the application
 * @param cc callback to trigger when the Config button is pressed
 */
void ui_create_main_window(ConfigCallback cc) {
    configCallback = cc;

    createMainWindow();
    createGrid();
    createDriveRow();
    createAuthorRow();
    createTitleRow();
    createDiscRow();
    createFormatRow();
    createButtonsRow();
}

/**
 * Show or hide the main window
 * @param show True to show it, False to hide it
 */
void ui_show_main_window(bool show) {
    if (show) {
        gtk_widget_show_all(window);
    }
    else {
        gtk_widget_hide(window);
    }
}
