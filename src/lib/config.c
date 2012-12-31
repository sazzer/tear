#include <string.h>
#include <ctype.h>
#include "config.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <glib.h>
#include <stdio.h>
#include <stdbool.h>

static const char EQUALS = '=';
static const char COMMENT = '#';

/**
 * The actual structure representing the config file
 */
struct Config_t {
    GHashTable* values;
};

/**
 * Create a new, blank Config object
 * @return the blank Config object
 */
Config config_new() {
    Config result = malloc(sizeof(struct Config_t));
    result->values = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    return result;
}

/**
 * Load the configuration from the given Config file
 * @param file The filename to load the config from
 * @return the loaded Config, or NULL if the file couldn't be loaded
 */
Config config_load(const char * file) {
    Config result = 0;
    FILE* fb = fopen(file, "r");
    char lineBuffer[1024];

    if (fb != NULL) {
        result = config_new();

        while (fgets(lineBuffer, 1024, fb) != NULL) {
            lineBuffer[strlen(lineBuffer) - 1] = 0;
            g_log("tear.config.load", G_LOG_LEVEL_DEBUG, "Read line: %s", lineBuffer);
            char * key;
            char * value;
            int keyEnd = -1;
            int valueStart = -1;
            int valueEnd = -1;

            bool finished = false;
            for (valueEnd = 0; !finished && valueEnd < strlen(lineBuffer); ++valueEnd) {
                if (lineBuffer[valueEnd] == COMMENT) {
                    finished = true;
                    if (keyEnd == -1 && valueEnd != 0) {
                        g_log("tear.config.load", G_LOG_LEVEL_WARNING, "Malformed line: %s", lineBuffer);
                    }
                    else {
                        --valueEnd;
                    }
                }
                else if (lineBuffer[valueEnd] == EQUALS) {
                    keyEnd = valueEnd;
                    valueStart = valueEnd + 1;
                }
            }

            if (valueStart != -1) {
                g_log("tear.config.load", G_LOG_LEVEL_DEBUG, "keyStart = 0(%c), keyEnd = %d(%c), valueStart = %d(%c), valueEnd = %d(%c)", 
                    lineBuffer[0], 
                    keyEnd, lineBuffer[keyEnd], 
                    valueStart, lineBuffer[valueStart],
                    valueEnd, lineBuffer[valueEnd]);
                for (; keyEnd > 0 && isspace(lineBuffer[keyEnd - 1]); --keyEnd);
                for (; valueStart < valueEnd && isspace(lineBuffer[valueStart]); ++valueStart);
                for (; valueEnd > valueStart && isspace(lineBuffer[valueEnd - 1]); --valueEnd);
                g_log("tear.config.load", G_LOG_LEVEL_DEBUG, "keyStart = 0(%c), keyEnd = %d(%c), valueStart = %d(%c), valueEnd = %d(%c)", 
                    lineBuffer[0], 
                    keyEnd, lineBuffer[keyEnd], 
                    valueStart, lineBuffer[valueStart],
                    valueEnd, lineBuffer[valueEnd]);

                key = malloc(sizeof(char) * keyEnd);
                strncpy(key, lineBuffer, keyEnd);
                key[keyEnd] = 0;
                g_log("tear.config.load", G_LOG_LEVEL_DEBUG, "Found key: '%s'", key);

                value = malloc(sizeof(char) * (valueEnd - valueStart));
                strncpy(value, lineBuffer + valueStart, valueEnd - valueStart);
                value[valueEnd - valueStart] = 0;
                g_log("tear.config.load", G_LOG_LEVEL_DEBUG, "Found value: '%s'", value);

                g_hash_table_insert(result->values, key, value);
            }

        }

        fclose(fb);
    }
    else {
        g_log("tear.config.load", G_LOG_LEVEL_WARNING, "Unable to open config file %s: %s", file, strerror(errno));
    }
    return result;
}

/**
 * Free the configuration object provided
 * @param config The config object to free
 */
void config_free(Config* config) {
    if (config && *config) {
        g_hash_table_destroy((*config)->values);
        free(*config);
        *config = 0;
    }
}

/**
 * Get the requested setting from the Config object, as a String. If the setting isn't
 * present then NULL is returned instead
 * @param config The config object to request
 * @param name The name of the setting to get
 * @return the setting, or NULL if not present
 */
const char * config_get_string(Config config, const char * name) {
    const char * val = 0;
    if (config) {
        val = g_hash_table_lookup(config->values, name);
    }
    return val;
}

/**
 * Set a new value into the Config object, overwriting an existing one if it's already present
 * @param config The config object to request
 * @param name The name of the setting to set
 * @param value The new value
 */
void config_set_string(Config config, const char * name, const char * value) {
    g_hash_table_insert(config->values, g_strdup(name), g_strdup(value));
}

