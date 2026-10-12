typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;

typedef struct ObjectData {
    u8 pad00[0x90];
    s32 entryIndex;
} ObjectData;

typedef struct Entry {
    u8 pad00[0x2A];
    u8 normalType;
    u8 normalValue;
    u8 specialChance;
    u8 pad2D[5];
    u8 specialType;
    u8 specialValue;
    u8 pad34[0xAC];
} Entry;

extern unsigned int fn_800FBFB0(void);
extern void *fn_80201B8C(u8 *object);
extern Entry *fn_80072354(s32 index);
extern s32 fn_800360B0(void *object, u16 *flags);
extern s32 fn_80066D04(s32 context, s32 index);

void fn_80073AE8(s32 context, s32 *action, s16 *value, u8 *type)
{
    u16 flags;
    s32 chance;
    s32 specialBlocked;
    s32 random;
    Entry *entry;

    random = (s32)fn_800FBFB0() % 100;
    *action = -1;
    *type = 0;
    entry = fn_80072354(((ObjectData *)fn_80201B8C((u8 *)context))->entryIndex);
    fn_800360B0((void *)context, &flags);
    chance = (s8)entry->specialChance;
    if (fn_80066D04(context, 3) == 0) {
        flags |= 1;
    }
    if (fn_80066D04(context, 2) == 0) {
        flags |= 2;
    }
    specialBlocked = flags & 2;
    if (specialBlocked != 0) {
        if (!(flags & 1)) {
            *action = 4;
            *type = entry->specialType;
            *value = entry->specialValue;
        }
    } else if (flags & 1) {
        if (specialBlocked == 0) {
            *action = 5;
            *type = entry->specialType;
            *value = entry->specialValue;
        }
    } else {
        if (random <= chance) {
            *action = 4;
            if (fn_800FBFB0() & 1) {
                *action = 5;
            }
            *type = entry->specialType;
            *value = entry->specialValue;
        } else {
            *action = 6;
            *type = entry->normalType;
            *value = entry->normalValue;
        }
    }
}
