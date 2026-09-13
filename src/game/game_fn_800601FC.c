typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;

#pragma use_lmw_stmw on

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct OwnerData {
    u8 pad00[0x8C];
    void *state;
} OwnerData;

typedef struct OwnerState {
    s32 flags;
    u8 pad04[0x14A];
    s16 cooldown;
} OwnerState;

typedef struct Entry {
    s32 packed;
    s32 kind;
    s32 unused;
} Entry;

typedef struct EntryList {
    s32 count;
    Entry *entries;
} EntryList;

extern const float lbl_8064E5D8;
extern const float lbl_8064E5F0;
extern void *fn_80201BC8();
extern void *fn_80201B8C();
extern s32 fn_80066D04(void *, s32);
extern int fn_80201B54();
extern s32 fn_80204180(void *, void *);
extern unsigned int fn_8015C910(void);
extern void *fn_8012AB2C(void *);
extern void fn_8011F114();
extern void fn_8013F3C0(void *, Vec3 *, Vec3 *, float);
extern unsigned int fn_8013FBE4(void *, void *, void *, s32, s32);
extern void *fn_801294DC(void *, int, int, int);
#define fn_801294DC(a, b, c, d) fn_801294DC((void *)(a), (b), (c), (d))
extern void *fn_801A717C(void);
extern void fn_801A7460(void *, s32);
extern void fn_801A74A0(void *, s32);
extern void fn_801A74A8(void *, s32);
extern void fn_801A74C8(void *, s32);
extern void fn_801A7560(void *, s32);
extern void fn_801A7550(void *, s32);
extern void fn_801A7558(void *, s32);
extern void *fn_8011F130(void *);
extern void fn_801A764C(void *, void *);
extern void fn_801A7538(void *, s32);
extern void fn_801A7518(void *, s32);
extern void fn_801292E0(void *, s32 *, Entry **);
extern void fn_801287C4(void *, void *, void *, s32);
extern void fn_80128C28();
extern void fn_80128C44(void *, void *, void *);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())

extern s32 fn_8006016C(s32, void *);
extern s32 fn_8006012C(void);
extern s32 fn_8006010C(void);
extern void fn_802042A4(void);

s32 fn_800601FC(void *source, void *target)
{
    void *source_resource;
    void *target_resource;
    OwnerData *owner_data;
    s32 relaxed;
    s32 source_value;
    s32 target_value;
    s32 distance;
    void *collision;
    Vec3 source_pos;
    Vec3 target_pos;
    u8 transform[0x3C];
    u8 hit[0x18];
    void *created;
    void *descriptor;
    EntryList list;
    s32 i;
    s32 offset;
    s32 callback_arg;
    s32 cooldown;

    if (source != 0 && target != 0) {
      source_resource = fn_80201BC8(source);
      if (source_resource != 0) {
       target_resource = fn_80201BC8(target);
       if (target_resource != 0) {

    owner_data = fn_80201B8C(source);
    relaxed = 0;
    if (fn_80066D04(source, 3) == 0 && fn_80066D04(source, 2) == 0) {
        relaxed = 1;
    }
    source_value = fn_80201B54(source);
    target_value = fn_80201B54(target);
    distance = fn_80204180(source, target);

    if (fn_8015C910() != 0) {
        return 0;
    }
    if ((((OwnerState *)owner_data->state)->flags & 0x800000) != 0 ||
        (((OwnerState *)owner_data->state)->cooldown <= 2 &&
         (distance > 1000 || relaxed != 0))) {

    collision = fn_8012AB2C(source_resource);
    fn_8011F114(&source_pos, source_resource);
    fn_8011F114(&target_pos, target_resource);
    source_pos.z += lbl_8064E5D8;
    target_pos.z += lbl_8064E5D8;
    fn_8013F3C0(transform, &source_pos, &target_pos, lbl_8064E5F0);
    if (fn_8013FBE4(collision, transform, hit, 0, 9) == 0) {

    created = fn_801294DC(source_resource, 9, 0, 6);
    if (created != 0) {
    descriptor = fn_801A717C();
    relaxed = 0;
    if (fn_80066D04(source, 3) == 0 && fn_80066D04(source, 2) == 0) {
        relaxed = 1;
    }
    fn_801A7460(descriptor, 9);
    fn_801A74A0(descriptor, source_value);
    fn_801A74A8(descriptor, target_value);
    fn_801A74C8(descriptor, 1);
    fn_801A7560(descriptor, 0x84);
    fn_801A7550(descriptor, 0xC);
    fn_801A7558(descriptor, 7);
    fn_801A764C(descriptor, fn_8011F130(source_resource));
    fn_801A7538(descriptor, 1);
    fn_801A7518(descriptor, 0x14);

    fn_801292E0(source_resource, &list.count, &list.entries);
    offset = 0;
    for (i = 0; i < list.count; i++, offset += sizeof(Entry)) {
        Entry *entry = (Entry *)((u8 *)list.entries + offset);
        switch (entry->kind) {
        case 1:
            callback_arg = entry->packed >> 17;
            fn_801287C4(created, fn_8006016C, descriptor, callback_arg + 0x1E);
            break;
        }
    }
    fn_801287C4(created, fn_8006012C, descriptor, callback_arg);
    fn_80128C28(created, fn_8006010C, descriptor);
    fn_80128C44(created, fn_802042A4, descriptor);
    fn_80201D2C(source, 6);
    fn_80201D14(source, 1);

    if (relaxed != 0) {
        cooldown = (fn_800FBFB0() & 0x7F) + 300;
    } else {
        cooldown = 400;
    }
    ((OwnerState *)owner_data->state)->cooldown = cooldown;
    return 1;
    }
    }
    }
       }
      }
    }

fail:
    return 0;
}
