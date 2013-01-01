#ifndef UI_FORMATS_H
#define UI_FORMATS_H

#include <gtk/gtk.h>

/**
 * Register a new format into the store
 * @param id The ID of the format
 * @param label The label of the format
 */
void ui_formats_register(int id, const char* label);

/**
 * Get the GTK Tree Model that represents the Formats list
 * @return the Tree Model
 */
GtkTreeModel* ui_formats_get_model();

/**
 * Get the ID of the format entry at the given index
 * @param index The index
 * @retrn the ID
 */
int ui_formats_get_id_from_index(int index);

#endif // UI_FORMATS_H
