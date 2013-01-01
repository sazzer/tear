#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <stdbool.h>

typedef void(*ConfigCallback)();
/**
 * Actually create the main window of the application
 * @param configCallback callback to trigger when the Config button is pressed
 */
void ui_create_main_window(ConfigCallback configCallback);
/**
 * Show or hide the main window
 * @param show True to show it, False to hide it
 */
void ui_show_main_window(bool show);

#endif // UI_MAINWINDOW_H
