#ifndef DRIVES_H
#define DRIVES_H

/** Representation of a list of CD Drives */
struct CDList_t;
typedef struct CDList_t* CDList;

/**
 * Generate a list of all the CD Drives that can be used
 * @return the list of CD Drives
 */
CDList drive_list_new();

/**
 * Free up the list of CD Drives
 * @param list The list of drives to free
 */
void drive_list_free(CDList* list);

/**
 * Get the number of entries in the provided list
 * @param list The list to query
 * @return the size of the list
 */
int drive_list_size(const CDList list);

/**
 * Get the name of the CD at the given index in the list
 * @param list The list to get the name from
 * @param index The index of the entry to get
 * @return the name of this entry. If the entry doesn't exist then null is returned
 */
const char * drive_list_get_name(const CDList list, const int index);

#endif // DRIVES_H
