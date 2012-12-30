#ifndef DRIVES_H
#define DRIVES_H

/** Representation of the details of a CD Drive */
struct CDInfo_t;
typedef struct CDInfo_t* CDInfo;

/** Representation of a list of CD Drives */
struct CDList_t;
typedef struct CDList_t* CDList;

/**
 * Generate a list of all the CD Drives that can be used
 * @return the list of CD Drives
 */
CDList cd_list_new();

/**
 * Get the number of entries in the provided list
 * @param list The list to query
 * @return the size of the list
 */
int cd_list_size(const CDList list);

/**
 * Get the name of the CD at the given index in the list
 * @param list The list to get the name from
 * @param index The index of the entry to get
 * @return the name of this entry. If the entry doesn't exist then null is returned
 */
const char * cd_list_get_name(const CDList list, const int index);

#endif // DRIVES_H
