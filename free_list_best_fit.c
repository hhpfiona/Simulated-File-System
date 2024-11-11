#include <string.h>
#include <stdlib.h>

#include "free_list.h"

/* Search the free list for the smallest block that has at least size bytes.
 * If a block is found of exactly the right size, remove the block from the
 * free list and return the offset of the block.
 * If a block is found that is larger than size, adjust the block in the free
 * list to reflect the remaining free space, and return the offset of the block.
 * Return -1 if no block is found that is large enough.
 */

int get_free_block(FS *fs, int size) {
    Freeblock *prev = NULL, *best_prev = NULL;
    Freeblock *curr = fs->freelist, *best_block = NULL;

    while (curr != NULL) {
        if (curr->length >= size && (best_block == NULL || curr->length < best_block->length)) {
            best_block = curr;
            best_prev = prev;
        }

        prev = curr;
        curr = curr->next;
    }

    if (best_block == NULL) {
        return -1; // No block large enough found
    }

    int offset = best_block->offset;

    // If the block is exactly the size needed, remove it from the free list
    if (best_block->length == size) {
        if (best_prev == NULL) {
            fs->freelist = best_block->next;
        } else {
            best_prev->next = best_block->next;
        }
        free(best_block);
    } else {
        // Otherwise, adjust the block's size
        best_block->offset += size;
        best_block->length -= size;
    }

    return offset;
}


