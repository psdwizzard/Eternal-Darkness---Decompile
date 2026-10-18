/* Compare pointers to Vorbis floor post positions for sorting. */
#include "src/game/types.h"

int icomp(const void *left, const void *right)
{
    return **(s32 *const *)left - **(s32 *const *)right;
}
