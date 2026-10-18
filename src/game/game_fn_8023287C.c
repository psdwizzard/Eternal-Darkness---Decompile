#include "src/game/types.h"

typedef struct AudioComment {
    char **comments;
    s32 *lengths;
    s32 count;
    char *vendor;
} AudioComment;

extern void *memset(void *dest, int value, unsigned long size);

/* Initialize the vendor string and user comment list. */
void vorbis_comment_init(AudioComment *comment)
{
    memset(comment, 0, sizeof(*comment));
}
