typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

#define NULL ((void*)0)

extern u16 fn_8004A608(u32, int, u8*, u8*, u16*, u32*);
extern u16 fn_80050730(int, int, u8*, u8*, u16*, u32*);
extern int fn_8006D548(int, u32, u32, Vec3*, u32*, u32*, int);
extern int fn_800A3564(void);
extern u16 fn_800AE864(unsigned int, u16*);
extern int fn_800AE88C(unsigned int);
extern void fn_800AF2D4(void);
extern int fn_801AF824(int);
extern int fn_801B05E8(int, u8, u8, u8, Vec3*, u8, int, int);
extern void fn_801B0CA4(int, int);
extern int lbl_8064D18C;

int fn_800AE5C4(int handle, int owner, int type, int stop, u16* soundId, u8* params, int flags) {
    u16 duration;
    u8 kind;
    u32 out;
    u16 extra;
    Vec3 info;
    int result;
    u8 mode;
    u8 loop;
    int allow;

    mode = 2;
    loop = 0;
    result = handle;
    if (*soundId == 0xFFFF) {
        switch (type) {
        case 0x3C:
            loop = 1;
            mode = 6;
            *soundId = fn_8004A608(owner, type, params, &kind, &duration, 0);
            fn_800AF2D4();
            break;
        case 0x55:
            out = 0;
            loop = 0;
            mode = 3;
            *soundId = fn_80050730(type, 0, params, &kind, &duration, &out);
            break;
        default:
            *soundId = fn_8004A608(owner, type, params, &kind, &duration, 0);
            break;
        }
    }
    if (flags & 1) {
        loop = 1;
    }
    if (*soundId < 0x2DB) {
        if (stop != 0) {
            fn_801B0CA4(-1, *soundId);
        } else {
            switch (type) {
            case 0x55: {
                int allow2 = 1;
                if (lbl_8064D18C == 0x27 && fn_800A3564() == 3) {
                    allow2 = 0;
                }
                if (fn_801AF824(result) == 0 && allow2 != 0) {
                    switch (*soundId) {
                    case 0x2D8:
                        if (fn_8006D548(2, 4, 2, &info, 0, 0, 0) >= 0) {
                            u32 volume = *params;
                            int id = *soundId;
                            result = fn_801B05E8(id, volume, mode, loop, &info, 2, 0, 0);
                        }
                        break;
                    default:
                        result = fn_801B05E8(*soundId, *params, mode, loop, NULL, 5, 0, 0);
                        break;
                    }
                }
                break;
            }
            default:
                allow = 1;
                if (type == 0x3B || type == 0x3E) {
                    fn_800AE864(3, &extra);
                    if (extra != 0) {
                        allow = 0;
                    }
                    if (type == 0x3E) {
                        if (fn_801AF824(fn_800AE88C(0)) != 0) {
                            allow = 0;
                        }
                    }
                }
                if (lbl_8064D18C == 0x27 && fn_800A3564() == 3 && type != 0x3C) {
                    allow = 0;
                }
                if (fn_801AF824(result) == 0 && allow != 0) {
                    u32 volume = *params;
                    int id = *soundId;
                    result = fn_801B05E8(id, volume, mode, loop, NULL, 5, 0, 0);
                }
                break;
            }
        }
    }
    return result;
}
