#include "game_state_8063C6B8.h"

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

void fn_801F6FD8(Vec3 value)
{
    *(Vec3*)&lbl_8063C6B8[3] = value;
}
