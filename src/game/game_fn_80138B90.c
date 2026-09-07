typedef unsigned int u32;

typedef struct Status {
    unsigned char pad[0x34];
    u32 size;
} Status;

extern u32 lbl_8064CFFC;
extern u32 lbl_8064D000;
extern unsigned char* lbl_8064D004;
extern unsigned char* lbl_8064CFC0;
extern volatile u32 lbl_8064D00C;
extern volatile u32 lbl_8064D010;

extern void fn_80213394(void*, Status*);
extern void fn_8021345C(Status*);
extern int fn_8015D458(void*, void*, u32);
extern int fn_8015E86C(void*, void*, u32);
extern void fn_8013824C(void);

void* fn_80138B90(void* object, int mode, int alternate)
{
    unsigned char* address;
    u32 available;
    int used;

    if (mode == 1) {
        address = lbl_8064D004 + lbl_8064D000;
        available = lbl_8064CFFC - lbl_8064D000;
    } else if (mode == 3) {
        Status status;
        fn_80213394(object, &status);
        address = lbl_8064CFC0 + 0x3D3100 - ((status.size + 31) & ~31);
        available = 0x3D3100 - lbl_8064D010;
        fn_8021345C(&status);
    } else {
        address = lbl_8064CFC0 + lbl_8064D010;
        available = 0x3D3100 - lbl_8064D010 - lbl_8064D00C;
    }

    if (alternate) {
        used = fn_8015D458(object, address, available);
    } else {
        used = fn_8015E86C(object, address, available);
    }
    if (used != 0) {
        if (mode == 1) {
            lbl_8064D000 += used;
        } else if (mode == 3) {
            lbl_8064D00C = (used + 31) & ~31;
            fn_8013824C();
        } else {
            lbl_8064D010 += (used + 31) & ~31;
        }
    } else {
        address = 0;
    }
    return address;
}
