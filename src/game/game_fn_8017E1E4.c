typedef signed short s16;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

/* The unsigned definition is known, but this caller needs a signed declaration
 * to reproduce retail's signed radius subtraction. Resolve the source-level ABI
 * mismatch only when this TU can retain its retail code generation. */
extern int rand(void);

void fn_8017E1E4(Vec3s* current, Vec3s* base, s16 radius, s16 z_offset)
{
    int mask = radius * 2 - 1;

    current->x += radius - (rand() & mask) + base->x;
    current->y += radius - (rand() & mask) + base->y;

    if (z_offset >= 0) {
        current->z += (rand() & 1) + base->z + z_offset;
    } else {
        current->z += base->z + (rand() & 1) * -1 + z_offset;
    }
}
