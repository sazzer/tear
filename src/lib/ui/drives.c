#include "drives.h"

static const int ID_COLUMN = 0;
static const int LABEL_COLUMN = 1;

/** The actual store for the drives */
static GtkListStore* drivesStore = 0;

/**
 * Register a new drive into the store
 * @param id The ID of the drive
 * @param label The label of the drive
 */
void ui_drives_register(int id, const char* label) {
    GtkListStore* store = GTK_LIST_STORE(ui_drives_get_model());

    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, 
        ID_COLUMN, id, 
        LABEL_COLUMN, label,
        -1);
}
/**
 * Get the GTK Tree Model that represents the Drives list
 * @return the Tree Model
 */
GtkTreeModel* ui_drives_get_model() {
    if (drivesStore == 0) {
        drivesStore = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING);
    }
    return GTK_TREE_MODEL(drivesStore);
}

/**
 * Get the ID of the entry at the given index
 * @param index The index
 * @retrn the ID
 */
int ui_drives_get_id_from_index(int index) {
    int id;
    GtkTreeIter iter;
    GtkTreeModel* drives = ui_drives_get_model();
    gtk_tree_model_iter_nth_child(drives, &iter, NULL, index);
    gtk_tree_model_get(drives, &iter, ID_COLUMN, &id, -1);
    return id;
}
