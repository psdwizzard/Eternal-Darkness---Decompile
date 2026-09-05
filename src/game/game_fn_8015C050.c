#pragma use_lmw_stmw on
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec { float x, y, z; } Vec;
typedef struct Item { u8 pad[0x58]; u8 index; u8 tail[3]; } Item;
typedef struct Point3 {
    s16 x;
    s16 y;
    s16 z;
} Point3;

typedef struct Config { u8 pad[0x24]; Item* items; u8* lookup; u8 pad2[4]; s16* positions; } Config;
extern u16 fn_8015C470(int);
extern Config* fn_8015C390(int);
extern Vec* fn_8011F130(void*);
extern u32 fn_80178F14(s16, s16, s16, int, int, int);

Item* fn_8015C050(void* object)
{
    u16 count;
    Item* best;
    u32 best_distance;
    count = fn_8015C470(2);
    best = 0;
    if (count != 0) {
        Config* config;
        Item* item;
        u8* lookup;
        s16* positions;
        Vec* position;
        int i;
        best_distance = 0x7FFFFFFF;
        config = fn_8015C390(2);
        item = config->items;
        lookup = config->lookup;
        positions = config->positions;
        position = fn_8011F130(object);
        for (i = 0; i < count; i++, item++) {
            int slot = item->index;
            u16 point = **(u16**)(lookup + slot * 0x38 + 0x2c);
            Point3 candidate = ((Point3*)positions)[point];
            u32 distance;
            fn_80178F14(candidate.x, candidate.y, candidate.z,
                        (int)position->x, (int)position->y, (int)position->z);
            distance = fn_80178F14(candidate.x, candidate.y, candidate.z,
                                   (int)position->x, (int)position->y, (int)position->z);
            if (distance < best_distance) {
                best_distance = distance;
                best = item;
            }
        }
    }
    return best;
}
#pragma use_lmw_stmw off
