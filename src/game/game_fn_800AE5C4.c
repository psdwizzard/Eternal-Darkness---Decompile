typedef unsigned char u8;
typedef unsigned short u16;
#define NULL ((void*)0)

extern u16 fn_8004A608(int, int, u8*, void*, void*, int);
extern u16 fn_80050730(int, int, u8*, void*, void*, int*);
extern int fn_8006D548();
extern int fn_800A3564(void);
extern u16 fn_800AE864(unsigned int, u16*);
extern int fn_800AE88C(unsigned int);
extern void fn_800AF2D4(void);
extern int fn_801AF824(int);
extern int fn_801B05E8(int, int, int, int, void*, int, int, int);
extern void fn_801B0CA4(int, int);
extern int lbl_8064D18C;
int fn_800AE5C4(int handle, int owner, int type, int stop, u16* soundId, u8* params, int flags) {
    u16 extra;
    u16 a;
    int out;
    int b;
    u8 info[0xC];
    int result;
    int mode;
    int loop;
    int allow;

    mode = 2;
    loop = 0;
    result = handle;
    if (*soundId == 0xFFFF) {
        switch (type) {
        case 0x3C:
            loop = 1;
            mode = 6;
            *soundId = fn_8004A608(owner, type, params, &a, &b, 0);
            fn_800AF2D4();
            break;
        case 0x55:
            out = 0;
            loop = 0;
            mode = 3;
            *soundId = fn_80050730(type, 0, params, &a, &b, &out);
            break;
        default:
            *soundId = fn_8004A608(owner, type, params, &a, &b, 0);
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
                        if (fn_8006D548(2, 4, 2, info, 0, 0, 0) >= 0) {
                            result = fn_801B05E8(*soundId, *params, mode, loop, info, 2, 0, 0);
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
                    result = fn_801B05E8(*soundId, *params, mode, loop, NULL, 5, 0, 0);
                }
                break;
            }
        }
    }
    return result;
}
