typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Entry {
    int id;
} Entry;

typedef struct Slot {
    u32 callbacks[4];
    u32 arguments[4];
    u16 ids[4];
    u8 index;
    u8 last_index;
    u8 first;
    u8 end;
} Slot;

typedef struct Config {
    u8 pad00[0x20];
    u32 flags;
} Config;

typedef struct Owner {
    u8 pad00[0x38];
    int handle;
    u8 pad3C[4];
    Slot slots[3];
    Config *config;
} Owner;

extern void *fn_8006D488(Owner *);
extern int fn_800A17C4(Owner *);
extern int fn_8006BCE4(Owner *);
extern Entry *fn_8006ED3C(Owner *, int, int *);
extern void fn_80144430(int, int);
extern int fn_80070F74(Owner *);
extern void fn_802020B4(void *, int);
extern int fn_8006EA4C(Owner *);
extern void fn_8006BEE4(int *, int);
extern void fn_8006C9E4(void *, int);
extern void fn_801FA748(int, Vec3 *);
extern int fn_8006E20C(Owner *);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void fn_800A18AC(int);
extern void fn_801A5C30(int);
/* These entry points accept unused legacy arguments at their call sites. */
extern int fn_800A197C();
extern void fn_801FAB0C();
extern int fn_800A0DE4(void *);
extern void fn_8006DEF8(Owner *, u32, u32, u32, u16);
extern int fn_80088298(void *);
extern void fn_800AF2D4(void);
extern int fn_800AE380(u16, u32, void *, u16, u16, u16, u8, u16);
extern void fn_800AE3FC(u16, u32, void *, u16, u16, u16, u8, u16);
extern int fn_80201B54(void *);
extern void fn_8020104C(int, int, int, int, float);
extern int fn_8009DC54(Owner *);
extern int fn_8009DE10(Owner *);
extern int fn_800A16AC(Owner *);
extern int fn_800A1724(Owner *);
extern void fn_800277A4(void);
extern void fn_8011E174(u32, int);
extern int fn_8006E3D4(void *);
extern int lbl_8064C8C4;
extern int lbl_8064D18C;
extern const float lbl_8064E834;
extern const volatile float lbl_802390EC[3];
extern const volatile float lbl_802390F8[6];

void fn_8006F7E8(Owner *owner, u16 value)
{
    Entry *entry;
    u32 kind;
    Config *config;
    void *object;
    int index;

    object = fn_8006D488(owner);
    config = owner->config;
    if (!fn_800A17C4(owner))
        return;
    if (config->flags & 0x20)
        return;
    config->flags |= 0x20;
    kind = fn_8006BCE4(owner);
    entry = fn_8006ED3C(owner, kind, &index);
    if ((int)kind != 7)
        lbl_8064C8C4 = 0;
    fn_80144430(4, 0);

    switch (kind) {
    case -1:
    case 0:
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
    case 8:
    case 14:
    case 21:
    case 24:
    case 30:
    case 31:
    case 37:
    case 38:
        fn_80070F74(owner);
        fn_802020B4(object, 1);
        return;
    case 10: {
        Vec3 direction = *(const Vec3 *)lbl_802390EC;
        fn_8006BEE4((int *)entry, (int)fn_8006EA4C);
        fn_8006C9E4(entry, 0);
        fn_801FA748(2, &direction);
        fn_802020B4(object, 1);
        return;
    }
    case 34:
        fn_8006E20C(owner);
        fn_8020123C(0xE5, 0, owner->handle, 0);
        fn_800A18AC(lbl_8064D18C);
        fn_8006BEE4((int *)entry, (int)fn_8006EA4C);
        fn_8006C9E4(entry, 0);
        fn_801A5C30(1);
        fn_802020B4(object, 1);
        fn_800A197C(0);
        return;
    case 36: {
        int i;
        fn_802020B4(object, 0);
        fn_801A5C30(0);
        fn_8020123C(0xE5, 0, owner->handle, 0);
        fn_800A18AC(lbl_8064D18C);
        fn_800A0DE4(0);
        fn_8006BEE4((int *)entry, (int)fn_8006EA4C);
        fn_8006C9E4(entry, 0);
        for (i = 0; i < 4; i++) {
            owner->slots[index].index = i;
            fn_8006DEF8(owner, entry->id, 0, 0, 0);
        }
        fn_801A5C30(1);
        fn_802020B4(object, 1);
        return;
    }
    case 7:
        fn_80088298(owner);
        fn_8020123C(0xE5, 0, owner->handle, 0);
        fn_8006BEE4((int *)entry, (int)fn_8006EA4C);
        fn_8006C9E4(entry, 0);
        fn_801A5C30(1);
        fn_802020B4(object, 1);
        fn_800AF2D4();
        if (!fn_800AE380(0xFFFF, 3, 0, 2, 360, 2, 0, 0))
            fn_800AE3FC(0xFFFF, 3, 0, 2, 360, 2, 0, 0);
        return;
    case 20:
    case 25:
    case 26:
    case 27:
    case 28: {
        Vec3 direction = *(const Vec3 *)lbl_802390F8;
        int i;
        owner->slots[index].first = 0;
        owner->slots[index].end = 4;
        for (i = 0; i < 4; i++) {
            owner->slots[index].index = i;
            fn_8006DEF8(owner, kind, 0, 0, 0);
        }
        owner->slots[index].index = 0;
        fn_8006BEE4((int *)entry, (int)fn_8006EA4C);
        fn_8006C9E4(entry, 0);
        fn_8020104C(0xE9, 0, fn_80201B54(object), 0, lbl_8064E834);
        fn_802020B4(object, 1);
        fn_801FA748(2, &direction);
        return;
    }
    }

    switch (kind) {
    case 15:
        fn_8020104C(0xE9, 0, fn_80201B54(object), 0, lbl_8064E834);
        break;
    case 16:
    case 18:
        fn_8009DC54(owner);
        break;
    case 19:
        fn_8009DE10(owner);
        break;
    case 13:
        fn_801FAB0C(0, 0);
        config->flags |= 0x80000U;
        break;
    case 32:
    case 33:
        fn_800A16AC(owner);
        break;
    case 35:
        fn_800A1724(owner);
        break;
    }

    fn_800277A4();
    fn_8020123C(0xE5, 0, owner->handle, 0);
    fn_800A18AC(lbl_8064D18C);
    fn_802020B4(object, 0);
    fn_801A5C30(0);
    fn_8011E174(0x100, 1);
    owner->slots[index].first = 0;
    owner->slots[index].end = 4;
    owner->slots[index].index = 4;
    fn_8006DEF8(owner, kind, (u32)fn_8006E20C, (u32)owner, value);
    owner->slots[index].index = 0;
    fn_8006DEF8(owner, kind, (u32)fn_8006E3D4, (u32)owner, 10);
    owner->slots[index].index = 1;
    fn_8006DEF8(owner, kind, 0, 0, 0);
    owner->slots[index].index = 2;
    fn_8006DEF8(owner, kind, 0, 0, 0);
    owner->slots[index].index = 0;
    fn_8006BEE4((int *)entry, (int)fn_8006EA4C);
    fn_8006C9E4(entry, 0);
}
