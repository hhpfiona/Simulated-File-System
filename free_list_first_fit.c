#include <string.h>
#include <stdlib.h>

#include "free_list.h"

/* Search the free list for the first block that has at least size bytes.
 * If the block that was found has exactly the right size, remove the block 
 * from the free list and return the offset of the block.
 * If the block that was found is larger than size, adjust the block in the free
 * list to reflect the remaining free space, and return the offset of the block.
 * Return -1 if no block is found that is large enough.
 */

int get_free_block(FS *fs, int size) {
    Freeblock *prev = NULL, *curr = fs->freelist;

    while (curr != NULL) {
        if (curr->length >= size) {
            int offset = curr->offset;

            // If the block is exactly the size needed, remove it from the free list
            if (curr->length == size) {
                if (prev == NULL) {
                    fs->freelist = curr->next;
                } else {
                    prev->next = curr->next;
                }
                free(curr);
            } else {
                // Otherwise, adjust the block's size
                curr->offset += size;
                curr->length -= size;
            }

            return offset;
        }

        prev = curr;
        curr = curr->next;
    }

    return -1; // No block large enough found
}

