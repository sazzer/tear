#ifndef UI_DRIVES_H
#define UI_DRIVES_H

#include <gtk/gtk.h>

/**
 * Register a new drive into the store
 * @param id The ID of the drive
 * @param label The label of the drive
 */
void ui_drives_register(int id, const char* label);

/**
 * Get the GTK Tree Model that represents the Formats list
 * @return the Tree Model
 */
GtkTreeModel* ui_drives_get_model();

/**
 * Get the ID of the drive entry at the given index
 * @param index The index
 * @retrn the ID
 */
int ui_drives_get_id_from_index(int index);

#endif // UI_DRIVES_H
