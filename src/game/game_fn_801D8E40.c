typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object {
    u8 bytes[0x1000];
} Object;

extern int lbl_8064D18C;
extern void* fn_80201814(u32);
extern int fn_800A0C0C(int);
extern void fn_801D88D4(u32, u32);
extern void fn_801FE22C(u32);
extern void fn_801B05B0(int, int);
extern void fn_801D884C(Object*);

void fn_801D8E40(Object* object)
{
    u32 flags = *(u32*)(object->bytes + 4);
    void* subject = fn_80201814(*(u32*)(object->bytes + 0xC));

    if (*(int*)(object->bytes + 8) != lbl_8064D18C ||
        (object->bytes[0xFF0] & 1) != 0) {
        if (*(u16*)(object->bytes + 0xFF4) == 0 &&
            fn_800A0C0C(0) == 0) {
            fn_801D88D4(flags, *(u32*)(object->bytes + 0xC));
        }
        fn_801FE22C(*(u32*)(object->bytes + 0x44));
        if (*(int*)(object->bytes + 0x10) != -1) {
            fn_801B05B0(*(int*)(object->bytes + 0x10), 10);
        }
        fn_801D884C(object);
        return;
    }

    if (subject == 0) {
        return;
    }
}
