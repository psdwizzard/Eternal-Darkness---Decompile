typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

typedef struct Entry {
    u16 a;
    u16 pad2[3];
    u16 b;
    u16 padA[3];
} Entry;

typedef struct SlotState {
    s32 pad0;
    s32 dir;
} SlotState;

typedef struct Slot {
    s32 pad0;
    SlotState state;
    char padC[0x4C - 0xC];
} Slot;

typedef struct EntryTable {
    s32 pad0;
    Entry **entries;
} EntryTable;

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

typedef struct Runtime {
    char pad0[0xB8];
    EntryTable *table;
    char padBC[0xF4 - 0xBC];
    u32 flags;
} Runtime;

typedef struct Owner {
    char pad0[0x3C];
    u16 *info;
    char pad40[0x154 - 0x40];
    Vec3 *scales;
    char pad158[0x160 - 0x158];
    Slot *slots;
} Owner;

extern Runtime *fn_80128E30(Owner *owner);
extern s32 fn_80128F40(void *object);
extern u16 fn_8012927C(Owner *owner);
extern void fn_80127658(Owner *owner, s32 index, s32 mode, s32 arg);
extern const f32 lbl_806501A8;

s32 fn_80128F74(Owner *owner, u32 flags) {
    Runtime *rt;
    s32 newBit1;
    s32 oldBit2;
    s32 newBit2;
    s32 oldBit1;
    u32 old;
    s32 result;

    result = 0;
    rt = fn_80128E30(owner);
    if (rt != 0) {
        old = rt->flags;
        newBit1 = (flags >> 1) & 1;
        newBit2 = (flags >> 2) & 1;
        oldBit1 = (old >> 1) & 1;
        rt->flags = flags;
        oldBit2 = (old >> 2) & 1;
        if (oldBit1 != newBit1) {
            s32 count;
            s32 i;
            Entry *entries;

            count = owner->info[4];
            entries = *rt->table->entries;
            if (fn_8012927C(owner) != 0xFFFF) {
                count++;
            }
            result = fn_80128F40(owner);
            for (i = 0; i < count; i++) {
                if (entries[i].a != 0 || entries[i].b != 0) {
                    SlotState *state = &owner->slots[i].state;
                    state->dir = newBit1 ? -1 : 1;
                    fn_80127658(owner, i, result, 0);
                }
            }
        }
        if (oldBit2 != newBit2 && (rt->flags & 4)) {
            u16 idx = fn_8012927C(owner);
            if (idx != 0xFFFF) {
                owner->scales[idx].x = lbl_806501A8;
                owner->scales[idx].y = lbl_806501A8;
                owner->scales[idx].z = lbl_806501A8;
            }
        }
        result = 1;
    }
    return result;
}
