#include "drives.h"
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <cdio/cdio.h>
#include <cdio/mmc.h>

/** 
 * The CD Name Format to use. Substitution entries are
 * Vendor
 * Model
 * Revision
 * Path
 */
static const char * CD_NAME_FORMAT = "%s %s: %s (%s)";

/** Representation of the details of a CD Drive */
struct CDInfo_t {
    /** The name of the CD Drive */
    char * name;
};

/** Representation of a list of CD Drives */
struct CDList_t {
    /** The actual list */
    GSList* list;
};

/**
 * Generate a list of all the CD Drives that can be used
 * @return the list of CD Drives
 */
CDList cd_list_new() {
    CDList list = malloc(sizeof(struct CDList_t));
    list->list = g_slist_alloc();

    driver_id_t driver = DRIVER_DEVICE;
    char** cdDrives = cdio_get_devices_ret(&driver);
    char** cd;
    if (cdDrives != NULL) {
        for (cd = cdDrives; *cd != NULL; ++cd) {
            CdIo_t* cdio = cdio_open(*cd, driver);
            if (cdio) {
                CDInfo info = malloc(sizeof(struct CDInfo_t));
                cdio_hwinfo_t hwinfo;
                cdio_get_hwinfo(cdio, &hwinfo);
                int bufferSize = snprintf(0, 0, CD_NAME_FORMAT, hwinfo.psz_vendor, hwinfo.psz_model, hwinfo.psz_revision, *cd) + 1;
            
                info->name = malloc(sizeof(char) * bufferSize);
                snprintf(info->name, bufferSize, CD_NAME_FORMAT, hwinfo.psz_vendor, hwinfo.psz_model, hwinfo.psz_revision, *cd);
                list->list = g_slist_append(list->list, info);

                cdio_destroy(cdio);
            }
        }
    }
    return list;
}

/**
 * Free up the list of CD drives
 * @param list The list to free
 */
void cd_list_free(CDList list) {
    if (list) {
        g_slist_free(list->list);
        free(list);
    }
}

/**
 * Get the number of entries in the provided list
 * @param list The list to query
 * @return the size of the list
 */
int cd_list_size(const CDList list) {
    int result = 0;
    if (list) {
        result = g_slist_length(list->list) - 1;
    }
    return result;
}

/**
 * Get the name of the CD at the given index in the list
 * @param list The list to get the name from
 * @param index The index of the entry to get
 * @return the name of this entry. If the entry doesn't exist then null is returned
 */
const char * cd_list_get_name(const CDList list, const int index) {
    const char * name = 0;
    if (list) {
        if (g_slist_length(list->list) > index && index >= 0) {
            CDInfo info = g_slist_nth_data(list->list, index + 1);
            if (info) {
                name = info->name;
            }
        }
    }
    return name;
}
