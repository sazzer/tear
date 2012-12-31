#ifndef UI_CONFIG_H
#define UI_CONFIG_H

#include <stdbool.h>
#include "../config.h"

/**
 * Actually create the config window of the application
 * @param config The configuration object to show and manipulate
 */
void ui_create_config_window(Config config);
/**
 * Show or hide the config window
 * @param show True to show it, False to hide it
 */
void ui_show_config_window(bool show);

#endif // UI_CONFIG_H

