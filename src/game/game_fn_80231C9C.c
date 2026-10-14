/* Compare pointers to Vorbis floor post positions for sorting. */
#include "src/game/types.h"

int fn_80231C9C(const void *left, const void *right)
{
    return **(s32 *const *)left - **(s32 *const *)right;
}
