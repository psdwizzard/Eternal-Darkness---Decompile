#include "src/game/types.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef struct ObjectState {
    u8 pad0[0x24];
    int unk24;
    int unk28;
    int unk2C;
    u8 pad30[0x38 - 0x30];
    int unk38;
    int unk3C;
    u8 pad40[0x146 - 0x40];
    s16 unk146;
    s16 unk148;
    u8 pad14A[0x14E - 0x14A];
    s16 unk14E;
    u8 pad150[0x152 - 0x150];
    s16 unk152;
    s16 unk154;
} ObjectState;

typedef struct ObjectInfo {
    u8 pad0[0x68];
    void *unk68;
    u8 pad6C[0x8C - 0x6C];
    ObjectState *state;
    u8 pad90[0x98 - 0x90];
    s16 unk98;
} ObjectInfo;

typedef struct ObjectLink {
    u8 pad0[0x2C];
    u32 flags;
} ObjectLink;

typedef struct ObjectPacket {
    u8 unk0;
    u8 unk1;
    s16 rot[3];
    s16 pos[4];
    s16 unk10;
    u16 type;
    s32 flags;
    s16 unk18;
    s16 subtype;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
} ObjectPacket;

typedef struct PacketPair {
    s16 a;
    s16 b;
} PacketPair;

extern int fn_800A4F98(int);
extern int fn_80201B44(void);
extern void *fn_80201814(int);
extern int fn_80201B54(void *);
extern int fn_80201B5C(void *);
extern int fn_80201B64(void *);
extern ObjectInfo *fn_80201B8C(void *);
extern void *fn_80201B94(void *);
extern void *fn_80201BC8(void *);
extern void *fn_80201C2C(void *);
extern void *fn_80201C50(void *);
extern u32 fn_80201CDC(void *);
extern int fn_80205110(void *);
extern void *fn_8011F130(void *);
extern void *fn_8011FE34(void *);
extern void fn_80128108(const float *, s16 *);
extern int fn_8011EB04(void *);
extern void *fn_8011FB4C(void *);
extern void fn_80179E60(s16 *, float *);
extern int fn_80038308(void *, int, s16 *);
extern u32 fn_80036D5C(void *);
extern u16 fn_800B9FE8(void *);
extern int fn_8012FB2C(void *);
extern int fn_8012F700(void *);
extern int fn_8012FA54(void *, int);
extern int fn_8012FAB4(void *, int);
extern u16 fn_800B9C88(void *, void *);
extern int fn_8012F7D4(u8 *, void *);
extern u16 fn_800BB450(void *, void *);
extern u16 fn_800BB5C4(void *, void *);
extern u16 fn_800BB7A8(void *, void *);
extern u16 fn_800BB9A4(void *, void *);
extern u16 fn_800BBAF0(void *, void *);
extern int fn_8012DC80(u8 *);
extern u16 fn_8012DBE8(u8 *, u32, u8 *);
extern int fn_80066D04(void *, int);
extern u16 fn_800BA068(void *, void *, void *, int);
extern void *memcpy(void *, const void *, u32);
extern void *memset(void *, int, u32);

int fn_800B9578(u8 *buf, void *object, int *count, int extra) {
    PacketPair pair;
    u8 status[4];
    u8 bits[4];
    PacketPair misc;
    ObjectPacket pkt;
    int ownerId;
    void *model;
    void *parent;
    register int localId;
    register int size;
    ObjectInfo *info;
    int slot;
    void *target;
    ObjectLink *link;
    void *player;

    fn_800A4F98(2);
    /* ASM: mr captures the owner ID in the retail allocation; a C assignment
     * makes MWCC allocate a different register throughout the function. */
    asm { mr localId, r3 }
    player = fn_80201814(fn_80201B44());
    ownerId = fn_80201B54(object);
    info = fn_80201B8C(object);
    link = (info != NULL) ? info->unk68 : NULL;
    parent = fn_80201B94(object);
    model = fn_80201BC8(object);
    target = fn_80201C2C(object);
    slot = fn_80205110(object);
    fn_80179E60(pkt.rot, fn_8011F130(model));
    fn_80128108(fn_8011FE34(model), pkt.pos);
    pkt.type = fn_8011EB04(model);
    pkt.unk10 = (s16)(u32)fn_80201C50(parent);
    pkt.unk18 = (s16)(u32)fn_8011FB4C(model);
    pkt.subtype = info->unk98;
    pkt.unk0 = fn_80201B5C(object);
    pkt.unk1 = fn_80201B64(object);
    fn_80038308(object, 0, &pkt.unk1C);
    pkt.unk20 = info->state->unk148;
    pkt.unk1E = info->state->unk146;
    pkt.flags = 0;
    if (slot != -1) {
        int linkedCount = fn_800B9FE8(target);
        pkt.flags |= linkedCount << 24;
    } else {
        pkt.flags |= 0x40000;
    }
    if (object == player) {
        pkt.flags |= 4;
        if (info->state->unk2C != 0) {
            pkt.flags |= 0x10;
        }
        if (info->state->unk3C != 0) {
            pkt.flags |= 0x20;
        }
    }
    if (fn_80201CDC(object) & 0x01000000) {
        pkt.flags |= 0x10000;
    }
    if (fn_80201CDC(object) & 4) {
        pkt.flags |= 1;
        if (fn_8012FB2C(model) != 0 && fn_8012F700(model) > 0) {
            if (fn_8012FA54(model, 15) == 0) {
                pkt.flags |= 0x400;
            }
            if (fn_8012FAB4(model, 15) != 0) {
                pkt.flags |= 0x800;
            }
        }
        if (fn_80201CDC(object) & 0x100000) {
            pkt.flags |= 0x400;
        }
        if (fn_80201CDC(object) & 0x200000) {
            pkt.flags |= 0x800;
        }
    }
    if (info->state->unk24 != 0) {
        pkt.flags |= 8;
    }
    if (info->state->unk28 != 0) {
        pkt.flags |= 0x20000;
    }
    if (info->state->unk38 != 0) {
        pkt.flags |= 0x40;
    }
    if (fn_80036D5C(object) & 8) {
        pkt.flags |= 0x80;
    }
    if (fn_80036D5C(object) & 0x20000) {
        pkt.flags |= 0x80000;
    }
    if (fn_80036D5C(object) & 0x80) {
        pkt.flags |= 0x100;
    }
    if (fn_80036D5C(object) & 0x8000) {
        pkt.flags |= 0x200;
    }
    if (fn_80036D5C(object) & 0x800000) {
        pkt.flags |= 0x400000;
    }
    if (ownerId == localId && ownerId != 0) {
        pkt.flags |= 0x800000;
    }
    if (extra != 0 && fn_8012F700(model) > 0) {
        pkt.flags |= 2;
    }
    if (link != NULL) {
        if (link->flags & 0x20) {
            pkt.flags |= 0x1000;
        }
        if (link->flags & 0x40) {
            pkt.flags |= 0x2000;
        }
        if (link->flags & 0x80) {
            pkt.flags |= 0x4000;
        }
        if (link->flags & 0x100) {
            pkt.flags |= 0x8000;
        }
        if (link->flags & 0x400) {
            pkt.flags |= 0x100000;
        }
        if (link->flags & 0x80) {
            pkt.flags |= 0x200000;
        }
    }

    memcpy(buf, &pkt, sizeof(ObjectPacket));
    size = sizeof(ObjectPacket);
    *count += 1;
    if (pkt.flags & 4) {
        register int combinedSize;
        register u16 sectionSize = fn_800B9C88(buf + sizeof(ObjectPacket), player);
        /* ASM: addi/clrlwi combine the u16 return with the header length; C adds
         * a redundant return-value truncation before this final 16-bit mask. */
        asm {
            addi combinedSize, sectionSize, 0x24
            clrlwi size, combinedSize, 16
        }
    }
    if (pkt.flags & 2) {
        size = ((u16)size + fn_8012F7D4(buf + (u16)size, model)) & 0xFFFF;
    }
    if (pkt.flags & 8) {
        {
            register u16 sectionSize = fn_800BB450(buf + (u16)size, fn_80201814(info->state->unk24));
            /* ASM: add uses the callee's zero-extended u16 length directly;
             * MWCC otherwise inserts a redundant clrlwi before the addition. */
            asm { add size, size, sectionSize }
        }
    }
    if (pkt.flags & 0x20000) {
        {
            register u16 sectionSize = fn_800BB5C4(buf + (u16)size, fn_80201814(info->state->unk28));
            /* ASM: add uses the callee's zero-extended u16 length directly;
             * MWCC otherwise inserts a redundant clrlwi before the addition. */
            asm { add size, size, sectionSize }
        }
    }
    if (pkt.flags & 0x10) {
        {
            register u16 sectionSize = fn_800BB7A8(buf + (u16)size, fn_80201814(info->state->unk2C));
            /* ASM: add uses the callee's zero-extended u16 length directly;
             * MWCC otherwise inserts a redundant clrlwi before the addition. */
            asm { add size, size, sectionSize }
        }
    }
    if (pkt.flags & 0x20) {
        {
            register u16 sectionSize = fn_800BBAF0(buf + (u16)size, fn_80201814(info->state->unk3C));
            /* ASM: add uses the callee's zero-extended u16 length directly;
             * MWCC otherwise inserts a redundant clrlwi before the addition. */
            asm { add size, size, sectionSize }
        }
    }
    if (pkt.flags & 0x40) {
        {
            register u16 sectionSize = fn_800BB9A4(buf + (u16)size, fn_80201814(info->state->unk38));
            /* ASM: add uses the callee's zero-extended u16 length directly;
             * MWCC otherwise inserts a redundant clrlwi before the addition. */
            asm { add size, size, sectionSize }
        }
    }
    if ((pkt.flags & 0x100) || (pkt.flags & 0x200)) {
        pair.a = info->state->unk152;
        pair.b = info->state->unk154;
        memcpy(buf + (u16)size, &pair, sizeof(PacketPair));
        size += sizeof(PacketPair);
    }
    if (pkt.type == 5 && pkt.subtype == 12) {
        memset(status, 0, sizeof(status));
        if ((u8)fn_8012DC80(model)) {
            if (fn_80066D04(object, 3) == 0) {
                status[0] |= 1;
            }
            if (fn_80066D04(object, 2) == 0) {
                status[0] |= 2;
            }
            if (fn_80066D04(object, 0) == 0) {
                status[0] |= 4;
            }
            fn_8012DBE8(model, 15, bits);
            if (bits[3] <= 20) {
                status[0] |= 8;
            }
        }
        memcpy(buf + (u16)size, status, sizeof(status));
        size += sizeof(status);
    }
    if (pkt.type == 0x89 && pkt.subtype == 0x84) {
        memset(&misc, 0, sizeof(misc));
        misc.a = info->state->unk14E;
        memcpy(buf + (u16)size, &misc, sizeof(misc));
        size += sizeof(misc);
    }
    {
        register u16 sectionSize = fn_800BA068(buf + (u16)size, (void *)ownerId, target, (int)count);
        /* ASM: add consumes the already-zero-extended u16 result in r3; MWCC C
         * otherwise inserts a second truncation at this call boundary. */
        asm { add size, size, sectionSize }
    }
    return size;
}
