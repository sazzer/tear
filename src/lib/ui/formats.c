#include "formats.h"

static const int ID_COLUMN = 0;
static const int LABEL_COLUMN = 1;

/** The actual store for the formats */
static GtkListStore* formatsStore = 0;

/**
 * Register a new format into the store
 * @param id The ID of the format
 * @param label The label of the format
 */
void ui_formats_register(int id, const char* label) {
    GtkListStore* store = GTK_LIST_STORE(ui_formats_get_model());

    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 
        ID_COLUMN, id, 
        LABEL_COLUMN, label,
        -1);
}
/**
 * Get the GTK Tree Model that represents the Formats list
 * @return the Tree Model
 */
GtkTreeModel* ui_formats_get_model() {
    if (formatsStore == 0) {
        formatsStore = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING);
    }
    return GTK_TREE_MODEL(formatsStore);
}
