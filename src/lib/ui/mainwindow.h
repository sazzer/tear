#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <stdbool.h>

typedef void(*ConfigCallback)();
typedef void(*GoCallback)(const int drive, const char* author, const char* title, const int disc, const int format);
/**
 * Actually create the main window of the application
 * @param configCallback callback to trigger when the Config button is pressed
 * @param goCallback callback to trigger when the Go button is pressed
 */
void ui_create_main_window(ConfigCallback configCallback, GoCallback goCallback);
/**
 * Show or hide the main window
 * @param show True to show it, False to hide it
 */
void ui_show_main_window(bool show);

#endif // UI_MAINWINDOW_H
