#include <string.h>
#include <stdlib.h>
#include "free_list.h"

/* These functions operate on a linked list of free blocks.  Each node of the
 * list contains the starting location and the length of a free block.
 */

/* Give free space back to the free list.  Since the list is ordered by 
 * location, this function is the same for both algorithms.
 * If the new block is adjacent to an existing block, merge the blocks.
 */
void add_free_block(FS *fs, int location, int size) {
    Freeblock *new_block = malloc(sizeof(Freeblock));
    new_block->offset = location;
    new_block->length = size;
    new_block->next = NULL;

    if (fs->freelist == NULL) {
        fs->freelist = new_block;
        return;
    }

    Freeblock *prev = NULL, *curr = fs->freelist;

    // Insert the new block at the right position in the list based on offset
    while (curr != NULL && curr->offset < location) {
        prev = curr;
        curr = curr->next;
    }

    // Check if the new block is adjacent to the previous block and can be merged
    if (prev != NULL && (prev->offset + prev->length == location)) {
        prev->length += size;
        free(new_block);
        new_block = prev;
    } else {
        new_block->next = curr;
        if (prev != NULL) {
            prev->next = new_block;
        } else {
            fs->freelist = new_block;
        }
    }

    // Check if the new block is adjacent to the next block and can be merged
    if (curr != NULL && (location + size == curr->offset)) {
        new_block->length += curr->length;
        new_block->next = curr->next;
        free(curr);
    }
}

/* Print the contents of the free list to standard output, with this format: "(offset: %d, length: %d)\n"
*/
void print_freelist(FS *fs) {



    Freeblock *curr = fs->freelist;
    while (curr != NULL) {
        printf("(offset: %d, length: %d)\n", curr->offset, curr->length);
        curr = curr->next;
    }
}

/* Build the freelist using the metadata read from a file.
 */
void rebuild_freelist(FS *fs) {
    fs->freelist = NULL;
    int curr_offset = METADATA_ENDS;

    for (int i = 0; i < MAXFILES; i++) {
        if (fs->metadata[i].offset > curr_offset) {
            add_free_block(fs, curr_offset, fs->metadata[i].offset - curr_offset);
        }
        curr_offset = fs->metadata[i].offset + fs->metadata[i].length;
    }

    if (curr_offset < MAX_FS_SIZE) {
        add_free_block(fs, curr_offset, MAX_FS_SIZE - curr_offset);
    }
}
