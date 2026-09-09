typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GameObject {
    u8 pad0[0x40];
    u32 flags;
    u8 pad44[0xEC];
    u32 field130;
    u8 pad134[0x8004];
    u32 field8138;
    u8 pad813C[6];
    signed char field8142;
    signed char field8143;
} GameObject;

extern long lbl_8064CBB8;
extern u32 lbl_8064C378;
extern u8 lbl_8064D5F8;
extern long lbl_8064B804;
extern long lbl_8064B7FC;
extern long lbl_8064CB98;
extern long lbl_8064CB9C;
extern long lbl_8064B800;
extern long lbl_8064B808;
extern long lbl_8064B80C;
extern long lbl_8064B7F8;

extern GameObject* fn_8015C28C(int);
extern void fn_800486C8(int);

int fn_801F3B80(void)
{
    GameObject* object;

    if (lbl_8064CBB8 != 0) {
        lbl_8064C378 = 703;
        lbl_8064D5F8 = 0;
        object = fn_8015C28C(0);
        if (lbl_8064B804 == 0) {
            lbl_8064C378 &= ~1;
        }
        if (lbl_8064B7FC == 0) {
            lbl_8064C378 &= ~2;
        }
        fn_800486C8(0);
        if (lbl_8064CB98 != 0 && (object->flags & 0x40) != 0) {
            fn_800486C8(1);
        }
        if (lbl_8064CB9C != 0 && (object->flags & 0x100) != 0) {
            fn_800486C8(2);
        }
        if (lbl_8064B800 == 0) {
            lbl_8064C378 &= ~4;
        }
        if (lbl_8064B808 == 0) {
            lbl_8064C378 &= ~0x80;
        }
        if (lbl_8064B80C == 0) {
            lbl_8064C378 &= ~0x20;
        }
        if (lbl_8064B7F8 == 0) {
            lbl_8064C378 &= ~0x10;
        }
        if (object != 0 && object->field8142 != 0 && object->field8143 != 0) {
            object->field8138 = 0;
            object->field130 = 0;
        }
        object = fn_8015C28C(1);
        if (object != 0 && object->field8142 != 0 && object->field8143 != 0) {
            object->field8138 = 0;
            object->field130 = 0;
        }
        lbl_8064CBB8 = 0;
        return 0;
    }
    return 0;
}
