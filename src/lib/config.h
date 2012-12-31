#ifndef CONFIG_H
#define CONFIG_H

struct Config_t;
typedef struct Config_t* Config;

/**
 * Load the configuration from the given Config file
 * @param file The filename to load the config from
 * @return the loaded Config, or NULL if the file couldn't be loaded
 */
Config config_load(const char * file);

/**
 * Create a new, blank Config object
 * @return the blank Config object
 */
Config config_new();

/**
 * Free the configuration object provided
 * @param config The config object to free
 */
void config_free(Config* config);

/**
 * Get the requested setting from the Config object, as a String. If the setting isn't
 * present then NULL is returned instead
 * @param config The config object to request
 * @param name The name of the setting to get
 * @return the setting, or NULL if not present
 */
const char * config_get_string(Config config, const char * name);

/**
 * Set a new value into the Config object, overwriting an existing one if it's already present
 * @param config The config object to request
 * @param name The name of the setting to set
 * @param value The new value
 */
void config_set_string(Config config, const char * name, const char * value);

#endif // CONFIG_H
