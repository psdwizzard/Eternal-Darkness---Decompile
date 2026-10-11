typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Slot {
    int depth;
    void *model;
    char pad8[0x1C];
    void *actor;
    void *owner;
} Slot;

typedef struct SlotTable {
    Slot banks[4][6]; /* previous, current, previous shadow, shadow */
    Slot extra[32];
    void *lists[2][3];
} SlotTable;

typedef struct MenuState {
    char pad0[0x10];
    unsigned int flags;
    void *sound;
} MenuState;

typedef struct FadeState {
    char pad0[0x6C];
    void *handle;
    char pad70[0x10];
    int color;
    int active;
    char pad88[0xA];
    short enable;
    int unk94;
    int unk98;
} FadeState;

extern unsigned char lbl_80330D80[];

/* Menu slot banks and list handles live in one block of menu data. */
#define sCurrent ((Slot *)(lbl_80330D80 + 0x108))
#define sShadow ((Slot *)(lbl_80330D80 + 0x318))
#define sLists ((void **)(lbl_80330D80 + 0x9A0))
extern MenuState lbl_80332140;
extern FadeState lbl_8024B3E4;
extern void *lbl_8064C504;
extern int lbl_8064CCB0;
extern int lbl_8064CCBC;
extern int lbl_8064CCD0;
extern int lbl_8064CCD4;
extern unsigned int lbl_8064CCE0;
extern float lbl_8064FE70;
extern float lbl_8064FE74;
extern float lbl_8064FE80;

extern int fn_8010B4C4(Slot *, int, int, float);
extern int fn_8010B5E4(Slot *, int, int, float);
extern void fn_8010CCD0(Slot *);
extern int fn_8010DA50(int);
extern int fn_8010DA94(int);
extern void fn_8010F2A4(void);
extern void fn_8011F0E8(void *, Vec3 *);
extern void fn_80144C40(void);
extern int fn_8015784C(void *);
extern int fn_80157858(void *);
extern int fn_80157BD0(void *);
extern int fn_80157BF4(void *);
extern int fn_8015821C(void *);
extern int fn_801A98F4(int, int);
extern void fn_801A9964(unsigned int);
extern void fn_801E5FB0(void *);
extern void *fn_801E6CA0(void *, int, int, int, int);
extern int fn_801E8D24(void *);
extern void fn_801F69F0(int *, Vec3 *, int);

void fn_8010B704(int unused, int mode)
{
    Slot *slot;
    Slot *current;
    Slot *shadow;
    void *actor;
    Vec3 world;
    int pos[3];
    float scale;
    short x;
    short y;
    int cursor;
    int sel;
    int target;
    int low;
    int range;
    int step;
    int i;
    int ok;
    int okShadow;
    int group;
    int sound;

    cursor = fn_801E8D24(sLists[0]) + fn_801E8D24(sLists[1]) * 2;
    x = fn_8010DA50(cursor);
    y = fn_8010DA94(cursor);
    if (lbl_8064CCD0 != 0) {
        lbl_8064CCD0--;
        fn_80144C40();
    }
    if (mode != 1) {
        return;
    }

    if ((lbl_80332140.flags & 1) && lbl_80332140.sound == 0 && !(lbl_80332140.flags & 2)) {
        lbl_80332140.sound = fn_801E6CA0(lbl_8064C504, 0, *(int *)((char *)&lbl_80332140 + 8), 0, 1);
    }

    slot = &sCurrent[cursor];
    if (sShadow[cursor].actor != 0) {
        slot = &sShadow[cursor];
    }
    if (slot->actor != 0) {
        fn_8015784C(slot->actor);
        fn_80157858(slot->actor);
        scale = (float)(20 - lbl_8064CCB0) / lbl_8064FE80;
        if (++lbl_8064CCB0 > 1000) {
            lbl_8064CCB0 = 0;
        }
    } else {
        scale = lbl_8064FE74;
    }

    current = sCurrent;
    shadow = sShadow;
    for (i = 0; current->actor != 0 && i < 6; current++, shadow++, i++) {
        sel = fn_801E8D24(sLists[0]) + fn_801E8D24(sLists[1]) * 2;
        target = fn_8015784C(current->actor);
        range = (target - fn_80157858(current->actor)) / 10;
        step = 1;
        if (range > 1) {
            step = range;
        }
        low = target - step;
        switch (lbl_8064CCD4) {
        case 3:
        case 4:
        case 5:
            if (i == sel) {
                break;
            }
            if (current->depth != target) {
                range = step / 30;
                current->depth += range >= 1 ? range : 1;
                current->depth = current->depth < target ? current->depth : target;
            }
            pos[0] = (short)fn_8010DA50(i);
            pos[1] = (short)fn_8010DA94(i);
            pos[2] = current->depth;
            fn_801F69F0(pos, &world, 0);
            fn_8011F0E8(current->model, &world);
            if (shadow->actor == 0) {
                break;
            }
            if (shadow->depth != target) {
                range = step / 30;
                shadow->depth += range >= 1 ? range : 1;
                shadow->depth = shadow->depth < target ? shadow->depth : target;
            }
            pos[0] = (short)fn_8010DA50(i);
            pos[1] = (short)fn_8010DA94(i);
            pos[2] = shadow->depth;
            fn_801F69F0(pos, &world, 0);
            fn_8011F0E8(shadow->model, &world);
            break;
        case 2:
            sel = fn_801E8D24(sLists[3]) + fn_801E8D24(sLists[4]) * 2;
        default:
            if (i != sel) {
                if (current->depth != target) {
                    range = step / 10;
                    current->depth += range >= 1 ? range : 1;
                    current->depth = current->depth < target ? current->depth : target;
                }
            } else if (current->depth != low) {
                range = step / 10;
                current->depth -= range >= 1 ? range : 1;
                current->depth = current->depth > low ? current->depth : low;
            }
            pos[0] = (short)fn_8010DA50(i);
            pos[1] = (short)fn_8010DA94(i);
            pos[2] = current->depth;
            fn_801F69F0(pos, &world, 0);
            fn_8011F0E8(current->model, &world);
            if (shadow->actor == 0) {
                break;
            }
            if (i != sel) {
                if (shadow->depth != target) {
                    range = step / 10;
                    shadow->depth += range >= 1 ? range : 1;
                    shadow->depth = shadow->depth < target ? shadow->depth : target;
                }
            } else if (shadow->depth != low) {
                range = step / 10;
                shadow->depth -= range >= 1 ? range : 1;
                shadow->depth = shadow->depth > low ? shadow->depth : low;
            }
            pos[0] = (short)fn_8010DA50(i);
            pos[1] = (short)fn_8010DA94(i);
            pos[2] = shadow->depth;
            fn_801F69F0(pos, &world, 0);
            fn_8011F0E8(shadow->model, &world);
            break;
        }
    }

    switch (lbl_8064CCD4) {
    case 3:
        okShadow = 1;
        if (sShadow[cursor].actor != 0) {
            okShadow = fn_8010B4C4(slot, (int)((float)(x - 320) * scale),
                                   (int)((float)(y - 165) * scale), scale);
        }
        ok = fn_8010B4C4(&sCurrent[cursor], (int)((float)(x - 320) * scale),
                         (int)((float)(y - 165) * scale), scale);
        if (ok != 0 && okShadow != 0) {
            group = fn_80157BF4(sCurrent[cursor].actor);
            sound = fn_80157BD0(sCurrent[cursor].actor);
            lbl_8024B3E4.handle = fn_801E6CA0(lbl_8064C504, group, sound, 0, 1);
            lbl_8064CCD4 = 4;
            lbl_8024B3E4.color = 0x60000000;
            lbl_8024B3E4.active = 1;
            lbl_8024B3E4.enable = 1;
            lbl_8024B3E4.unk94 = 0;
            lbl_8024B3E4.unk98 = 0;
        }
        break;
    case 4:
        lbl_8064CCBC = slot->depth;
        break;
    case 5:
        okShadow = 1;
        if (sShadow[cursor].actor != 0) {
            okShadow = fn_8010B5E4(slot, (int)((float)(x - 320) * (lbl_8064FE70 - scale)),
                                   (int)((float)(y - 165) * (lbl_8064FE70 - scale)), scale);
        }
        ok = fn_8010B5E4(&sCurrent[cursor], (int)((float)(x - 320) * (lbl_8064FE70 - scale)),
                         (int)((float)(y - 165) * (lbl_8064FE70 - scale)), scale);
        fn_801E5FB0(lbl_8024B3E4.handle);
        lbl_8024B3E4.handle = 0;
        if (ok != 0 && okShadow != 0) {
            lbl_8064CCD4 = 0;
        }
        break;
    case 2:
        cursor = fn_801E8D24(sLists[3]) + fn_801E8D24(sLists[4]) * 2;
    case 0:
    case 1:
        slot = &sCurrent[cursor];
        actor = slot->actor;
        fn_8010CCD0(slot);
        switch (fn_8015821C(actor)) {
        case 0xC8: case 0xC9: case 0xCA: case 0xCB: case 0xCC: case 0xCD: case 0xCE:
        case 0xCF: case 0xD0: case 0xD1: case 0xD2: case 0xD3: case 0xD4: case 0xD5:
        case 0xDB:
            if (lbl_8064CCE0 == 0) {
                lbl_8064CCE0 = fn_801A98F4(0x21, 0x3C);
            }
            break;
        default:
            if (lbl_8064CCE0 != 0) {
                fn_801A9964(lbl_8064CCE0);
                lbl_8064CCE0 = 0;
            }
            break;
        }
        break;
    }

    if (lbl_80332140.flags & 2) {
        fn_8010F2A4();
    }
}
