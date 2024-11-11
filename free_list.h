#ifndef FREE_LIST_H_
#define FREE_LIST_H_

#include "file_ops.h"

/* Implemented separately in free_list_best_fit.c and free_list_first_fit.c */
int get_free_block(FS *fs, int size);

/* Functions implemented in free_list_common.c*/

void add_free_block(FS *fs, int location, int size);
void rebuild_freelist(FS *fs);
void print_freelist(FS *fs); 


#endif /* FREE_LIST_H_ */
