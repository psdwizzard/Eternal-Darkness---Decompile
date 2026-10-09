typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

typedef struct Entry {
    u8 pad0[0x2C];
    u32 id;
    u8 pad30[0x68 - 0x30];
    u32 flags;
    u8 pad6C[0x74 - 0x6C];
} Entry;

typedef struct Owner {
    u8 pad0[0xB0];
    u16 count;
    u8 padB2[2];
    Entry* entries;
} Owner;

typedef struct Settings {
    u8 pad0[0x48F];
    u8 timer;
} Settings;

extern void fn_800804C4(int);
extern int fn_80080530(int, int);
extern int fn_80080588(int, int, u8, f32);
extern Owner* fn_8015C28C(int);
extern int fn_8015C9F0(void);
extern int fn_801E79FC(void*, int);
extern int fn_802019EC(int, int);
extern Settings lbl_8031CD84;
extern void* lbl_8064C4E0;
extern s32 lbl_8064D18C;
extern f32 lbl_8064EA08;
extern f32 lbl_8064EA1C;
extern f32 lbl_8064EA64;
extern f32 lbl_8064EA68;

void fn_80080030(void) {
    Owner* owner;
    int which;
    int object;
    int flag58;
    int flag59;
    int flag5A;
    int flag5B;
    int i;

    if (lbl_8064D18C == 0xBE) {
        owner = fn_8015C28C(2);
        flag58 = fn_801E79FC(lbl_8064C4E0, 0x58);
        flag59 = fn_801E79FC(lbl_8064C4E0, 0x59);
        flag5A = fn_801E79FC(lbl_8064C4E0, 0x5A);
        flag5B = fn_801E79FC(lbl_8064C4E0, 0x5B);
        object = fn_802019EC(0x5B, 0xBE);
        if (fn_8015C9F0() == 1) {
            fn_800804C4(0);
            return;
        }
        for (i = 0; i < owner->count; i++) {
            Entry* entry = &owner->entries[i];
            u32 id = entry->id;
            if (id == 0xE98A39BB) {
                if (entry->flags & 1) {
                    which = 3;
                }
            } else if (id == 0xE98B79B9) {
                if (entry->flags & 1) {
                    which = 2;
                }
            } else if (id == 0xE98BD9B8) {
                if (entry->flags & 1) {
                    which = 1;
                }
            }
        }
        if (flag5A != 0 || which == 1 || flag5B != 0) {
            fn_80080588(object, 0, lbl_8031CD84.timer, lbl_8064EA64);
            fn_80080588(object, 1, lbl_8031CD84.timer, lbl_8064EA64);
        } else {
            fn_80080530(0, 1);
            fn_80080530(1, 1);
        }
        if (flag59 != 0 || which == 2 || flag5B != 0) {
            fn_80080588(object, 2, lbl_8031CD84.timer, lbl_8064EA68);
            fn_80080588(object, 3, lbl_8031CD84.timer, lbl_8064EA68);
        } else {
            fn_80080530(2, 1);
            fn_80080530(3, 1);
        }
        if (flag58 != 0 || which == 3 || flag5B != 0) {
            fn_80080588(object, 4, lbl_8031CD84.timer, lbl_8064EA1C);
            fn_80080588(object, 5, lbl_8031CD84.timer, lbl_8064EA1C);
        } else {
            fn_80080530(4, 1);
            fn_80080530(5, 1);
        }
        if ((flag5A != 0 && flag59 != 0 && which == 3) ||
            (flag59 != 0 && flag58 != 0 && which == 1) ||
            (flag5A != 0 && flag58 != 0 && which == 2) || flag5B != 0) {
            fn_80080588(object, 6, lbl_8031CD84.timer, lbl_8064EA08);
        } else {
            fn_80080530(6, 1);
        }
        if (lbl_8031CD84.timer == 0) {
            lbl_8031CD84.timer = 0x2D;
        }
    } else if (lbl_8064D18C != 0xBD) {
        fn_800804C4(0);
    }
}
