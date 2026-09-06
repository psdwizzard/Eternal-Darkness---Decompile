typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void fn_801082D4(void*);
extern int fn_801083B4(void*, int);
extern int fn_80108470(void);
extern void fn_80108478(void);
extern int fn_800FD1E8(const char*, void*, unsigned long);
extern u32 fn_8021A370(void);
extern void fn_80106A8C(void*, void*);
extern u32 fn_80106AC0(void*);
extern void* memset(void*, int, unsigned long);
extern unsigned long strlen(const char*);
extern const char lbl_8023A268[];
extern float lbl_8064FE60;
extern float lbl_8064FE64;

#define U8(p, o) (*(u8*)((u8*)(p) + (o)))
#define U16(p, o) (*(u16*)((u8*)(p) + (o)))
#define U32(p, o) (*(u32*)((u8*)(p) + (o)))

#pragma opt_common_subs off
int fn_801098C0(void* source, void* state)
{
    u32 format;

    fn_801082D4(source);
    memset(state, 0, 0x1C0);
    U32(state, 0x178) = 1;
    while (fn_80108470() != 0) {}
    if (fn_801083B4(state, 0x44) == -1) {
        return 1;
    }
    if (fn_800FD1E8(lbl_8023A268, state, strlen(lbl_8023A268)) != 0) {
        return 1;
    }

    U8(state, 0x1AF) = 0xFF;
    format = U32(state, 0x40);
    if (format != 0) {
        if (format == 0xBBAA) {
            if (fn_8021A370() != 1) {
                fn_80108478();
                while (fn_80108470() != 0) {}
                return 1;
            }
            U8(state, 0x1AF) = 1;
        } else if (format == 0x7D1C) {
            if (fn_8021A370() != 0) {
                fn_80108478();
                while (fn_80108470() != 0) {}
                return 1;
            }
            U8(state, 0x1AF) = 0;
        } else {
            fn_80108478();
            while (fn_80108470() != 0) {}
            return 1;
        }
    }

    fn_80106A8C((u8*)state + 0xA0, (u8*)state + 0x34);
    if (fn_80106AC0((u8*)state + 0xA0) == 0) {
        return 1;
    }

    U32(state, 0x184) = (int)(lbl_8064FE60 + (float)U32(state, 0x24) / lbl_8064FE64);
    U32(state, 0x180) = 0;
    U16(state, 0x19C) = U16(state, 0xA4);
    U16(state, 0x19E) = U16(state, 0xA6);
    U16(state, 0x198) = (u16)((480 - U16(state, 0x19E)) / 2);
    U16(state, 0x19A) = (u16)((640 - U16(state, 0x19C)) / 2);
    U32(state, 0x138) = (u32)state + 0xF0;
    U32(state, 0x13C) = (u32)state + 0xFC;
    U32(state, 0x140) = (u32)state + 0x108;
    U32(state, 0x144) = (u32)state + 0x114;
    U32(state, 0x148) = (u32)state + 0x120;
    U32(state, 0x14C) = (u32)state + 0x12C;
    return 0;
}
#pragma opt_common_subs reset
