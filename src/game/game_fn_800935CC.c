typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Candidate {
    u32 id;
    Vec3 position;
    unsigned char data[0x1C];
} Candidate;

extern void* fn_80158950(int key, u16* count);
extern void fn_80201E78(void* destination, void* object);
extern u32 fn_800FBFB0(void);
extern u32 fn_80178E94(const float* first, const float* second);
extern Vec3 lbl_80239694;

/* Select a resource entry by ID, proximity, or a random index.
 * Flag 0x100 excludes entries with the supplied ID from first/nearest searches.
 */
Candidate* fn_800935CC(register void* object, register Vec3* position,
                       register u32 id, register u16 flags)
{
    Vec3 origin;
    Vec3 object_position;
    Vec3 default_position;
    u16 count;
    Vec3* source;
    register Candidate* candidate;
    register Candidate* best = 0;
    register u32 best_distance = (u32)-1;
    register u16* count_address = &count;
    register u32 zero = 0;
    u32 i;

    /* ASM: sth keeps the count store after argument preservation;
     * C schedules the store ahead of the saved arguments. */
    asm {
        sth zero, 0(count_address)
    }
    candidate = fn_80158950(2, count_address);
    if (object != 0) {
        fn_80201E78(&object_position, object);
        source = &object_position;
    } else if (position != 0) {
        source = position;
    } else {
        default_position = lbl_80239694;
        source = &default_position;
    }
    origin = *source;

    if (flags & 8) {
        best = candidate + ((int)fn_800FBFB0() % count);
    } else {
        for (i = 0; i < count; ++i, ++candidate) {
            if (flags & 2) {
                if (((flags & 0x100) && candidate->id != id) || !(flags & 0x100)) {
                    return candidate;
                }
            } else {
                if ((flags & 4) && id == candidate->id) {
                    return candidate;
                }
                if ((flags & 1) &&
                    (((flags & 0x100) && candidate->id != id) || !(flags & 0x100))) {
                    u32 distance = fn_80178E94(&origin.x, &candidate->position.x);
                    if (distance < best_distance) {
                        best = candidate;
                        best_distance = distance;
                    }
                }
            }
        }
    }
    return best;
}
