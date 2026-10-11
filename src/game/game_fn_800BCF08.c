typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Shape {
    Vec3 first;
    Vec3 second;
    float radius;
    Vec3 axis;
    float length;
    Vec3 center;
    float bound_radius;
} Shape;

typedef struct Result {
    Vec3 normal;
    Vec3 point;
} Result;

typedef struct PathEntry {
    const short *position;
} PathEntry;

typedef struct Owner Owner;
extern void fn_800BCCC4(const short *source, Vec3 *result);
extern void fn_8013F3C0(Shape *out, const Vec3 *first, const Vec3 *second, float radius);
extern void *fn_8015C2FC(int selector);
extern void *fn_8013FBE4(Owner *owner, const void *value, Result *out,
                        void *context, unsigned int flags);
extern void *memset(void *dest, int value, unsigned long size);
extern void *memcpy(void *dest, const void *source, unsigned long size);
extern PathEntry *lbl_80320C60[100];
extern int lbl_8064D18C;
extern const float lbl_8064F0F0;
extern const float lbl_8064F0F4;

void fn_800BCF08(Vec3 *position, PathEntry **path, float radius)
{
    PathEntry *remaining[100];
    Shape shape;
    Result hit;
    Vec3 first;
    Vec3 next;
    float offset;
    float limit;
    PathEntry **entry;
    int searching;
    int index;

    position->z += (offset = lbl_8064F0F0 + radius);
    if (path[0] != 0 && path[0]->position != 0) {
        fn_800BCCC4(path[0]->position, &first);
        memset(remaining, 0, sizeof(remaining));
        entry = path + 1;
        index = 1;
        searching = 1;
        while (searching && *entry != 0 && (*entry)->position != 0) {
            limit = ((lbl_8064F0F4 + position->z) - radius) - lbl_8064F0F0;
            fn_800BCCC4((*entry)->position, &next);
            if (next.z > limit || lbl_8064D18C == 0x78) {
                searching = 0;
                /* The original copy length subtracts the entry count in bytes. */
                memcpy(remaining, path + (index - 1), 0x190 - (index - 1));
            } else {
                next.z += offset;
                fn_8013F3C0(&shape, position, &next, radius);
                if (fn_8013FBE4(fn_8015C2FC(2), &shape, &hit, 0, 9) != 0) {
                    searching = 0;
                    memcpy(remaining, path + (index - 1), 0x190 - (index - 1));
                }
            }
            entry++;
            index++;
        }
        if (searching) {
            remaining[0] = path[index - 1];
        }
        memcpy(lbl_80320C60, remaining, sizeof(remaining));
    }
    position->z -= offset;
}
