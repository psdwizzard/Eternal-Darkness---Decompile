typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef float f32;

#define NULL ((void *)0)

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

/* One 0xB0-byte effect slot */
typedef struct EffectSlot {
    u8 type;            /* 0x00 */
    u8 unk1;
    u8 unk2;
    s8 unk3;            /* 0x03 */
    u8 pad4[4];
    s16 unk8;           /* 0x08 */
    u8 padA[0xA];
    u8 unk14;           /* 0x14 */
    u8 unk15;           /* 0x15 */
    u8 unk16;           /* 0x16 */
    u8 unk17;           /* 0x17 */
    s32 unk18;
    s32 unk1C;          /* 0x1C */
    u8 pad20[0x70];
    void *callback;     /* 0x90 */
    u8 pad94[4];
    Vec3 pos;           /* 0x98 */
    s16 rot[3];         /* 0xA4 */
    u8 unkAA;           /* 0xAA */
    u8 padAB[5];
} EffectSlot;

typedef struct EffectSet {
    EffectSlot slots[5];    /* 0x000 */
    u8 pad370[0x14];
    u32 flags;              /* 0x384 */
    u8 pad388[4];
    s32 entryId;            /* 0x38C */
    u8 mainType;            /* 0x390 */
    u8 subType;             /* 0x391 */
    u8 pad392[10];
    s32 unk39C;             /* 0x39C */
} EffectSet;

typedef struct Owner {
    u8 pad0[0x9F];
    u8 unk9F;
} Owner;

typedef struct Actor {
    u8 pad0[8];
    EffectSet effects;      /* 0x008 */
    u8 pad3A8[0x132C - 0x3A8];
    u16 state;              /* 0x132C */
} Actor;

typedef struct Entry80201814 Entry80201814;
typedef struct ListNode ListNode;

typedef struct ShortCoord3 {
    short x;
    short y;
    short z;
} ShortCoord3;

extern Entry80201814 *fn_80201814(s32);
extern void *fn_80201B8C(unsigned char *);
extern int fn_800676C8(u8);
extern int fn_80052310(int, const s16 *);
extern void fn_80149E28(ListNode *);
extern void fn_80179904(ShortCoord3 *, short);
extern void fn_8017EA58(u8 *);
extern void *fn_8017EAA8(void *, void *, void *);
extern void fn_80183DD4(u8 *);
extern u8 *fn_80183EE0(void *, void *, void *);
extern int fn_801E8328(u32, u32);
extern void *memcpy(void *, const void *, unsigned int);

void fn_8014D650(Actor *actor) {
    EffectSlot *slot;
    EffectSet *set;
    Owner *owner;
    s32 count;
    s16 *rot;
    u32 flags;
    Entry80201814 *entry;
    s16 pos[3];
    s32 sound;

    owner = NULL;
    count = 0;
    set = &actor->effects;
    if (set->entryId != -1) {
        entry = fn_80201814(set->entryId);
        if (entry != NULL) {
            owner = (Owner *)fn_80201B8C((u8 *)entry);
        }
    }

    switch (actor->state) {
    case 0:
        flags = set->flags;
        slot = (EffectSlot *)set;
        rot = set->slots[0].rot;
        if ((flags & 2) && set->mainType != 0) {
            fn_8017EA58((u8 *)set);
            set->slots[0].type = set->mainType;
            *(s32 *)((u8 *)set + 0x1D) = set->unk39C;
            *(s16 *)&set->slots[0].unk14 = 8;
            set->slots[0].callback = fn_8017EAA8;
            set->slots[0].unkAA = 4;
            fn_801E8328(0x10, (u32)set);
        }
        if ((flags & 1) && set->subType != 0) {
            count++;
            slot[1].pos = set->slots[0].pos;
            slot++;
            memcpy(slot->rot, rot, 6);
            slot->rot[2] = -2;
            fn_80183DD4((u8 *)slot);
            slot->unk8 = 1;
            slot->type = set->subType;
            slot->unk3 = -4;
            slot->unk16 = 2;
            slot->unk1C = set->unk39C;
            slot->callback = fn_80183EE0;
            slot->unkAA = 4;
            fn_801E8328(0x10, (u32)slot);
        }
        if ((flags & 0x10) && set->subType != 0 && count < 4) {
            count++;
            slot[1].pos = set->slots[0].pos;
            slot++;
            memcpy(slot->rot, rot, 6);
            fn_80183DD4((u8 *)slot);
            slot->type = set->subType;
            slot->unk16 = 0xFF;
            slot->unk17 = 0;
            slot->unk15 = 0x40;
            slot->unk14 = 4;
            slot->callback = fn_80183EE0;
            slot->unkAA = 4;
            fn_801E8328(0x10, (u32)slot);
        }
        if ((flags & 8) && set->subType != 0 && count < 4) {
            slot[1].pos = set->slots[0].pos;
            memcpy(slot[1].rot, rot, 6);
            fn_80179904((ShortCoord3 *)slot[1].rot, 3);
            fn_80183DD4((u8 *)&slot[1]);
            slot[1].type = set->subType;
            slot[1].unk8 = 0xF;
            slot[1].unk2 = 0xFF;
            slot[1].unk3 = -5;
            slot[1].unk16 = 2;
            slot[1].unk15 = 9;
            slot[1].unk1C = set->unk39C;
            *(u8 *)&slot[1].unk18 = 1;
            slot[1].callback = fn_80183EE0;
            slot[1].unkAA = 4;
            fn_801E8328(0x10, (u32)&slot[1]);
        }
        sound = 0x32;
        pos[0] = set->slots[0].pos.x;
        pos[1] = set->slots[0].pos.y;
        pos[2] = set->slots[0].pos.z;
        if (owner != NULL && fn_800676C8(owner->unk9F) != 0) {
            sound = 0x54;
        }
        fn_80052310(sound, pos);
        break;
    case 2:
        fn_80149E28((ListNode *)actor);
        break;
    }
}
