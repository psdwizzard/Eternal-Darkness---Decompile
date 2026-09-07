typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

#pragma use_lmw_stmw on

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Record {
    char pad00[0x2C];
    s16 position[3];
    char pad32[0x16];
    u32 flags;
} Record;

typedef struct RecordSet {
    char pad00[0x34];
    u16 count;
    char pad36[2];
    Record* records;
} RecordSet;

extern RecordSet* fn_8015C390(int);
extern u32 fn_80178F14(int, int, int, int, int, int);

int fn_80158D38(Vec3* position, int key, u32 mask, Vec3* output)
{
    int result;
    u32 best_distance;
    Record* best;
    RecordSet* set;
    int i;
    Record* record;

    result = 0;
    best = 0;
    set = fn_8015C390(key);

    if (set != 0 && set->count != 0) {
        record = set->records;

        for (i = 0; i < set->count; i++, record++) {
            if (record->flags & mask) {
                u32 distance = fn_80178F14(record->position[0], record->position[1],
                                          record->position[2], (int)position->x,
                                          (int)position->y, (int)position->z);
                if (best == 0 || distance < best_distance) {
                    best_distance = distance;
                    best = record;
                }
            }
        }
    }

    if (best != 0) {
        result = 1;
        output->x = (float)best->position[0];
        output->y = (float)best->position[1];
        output->z = (float)best->position[2];
    }
    return result;
}
