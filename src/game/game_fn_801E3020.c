typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct KindInfo {
    u8 pad0[0x9E];
    u8 family;
    u8 kind;
} KindInfo;

extern u32 lbl_802FC5BC[];
extern void fn_801E3644(void);
extern void fn_801499C4(void);
extern void* fn_80201814(u32);
extern KindInfo* fn_80201B8C(void*);
extern void* fn_801D0D78();
extern void fn_801D0CA4(void*);
extern void* fn_80149E04(void);
extern void fn_80147E88(void*);
extern void fn_80149524(void*, void*);
extern void fn_80148A98(void*, void*);
extern void fn_80149B0C(void*, u32, u32);
extern void fn_80149B38(void*);
extern void fn_80149EB8(void*);
extern void fn_801A39DC(void*);
extern void fn_80184740(void*);
extern s16 fn_801D3A34(u32, u32);
extern u32 fn_801CEB2C(u32);
extern u32 fn_801D38E8(u32);
extern u32 fn_80201AE4(void);
extern void fn_801E8328(u32, void*, u32);

void* fn_801E3020(u32 runtime, u32 flags, void* position, u32 source,
                  u32 owner, void** output_a, void** output_b,
                  void** output_c, void** output_d, u32 resource)
{
    KindInfo* info;
    void* object;
    u8* work;
    u8* data;
    u8* secondary;
    u32 special = 0;

    info = fn_80201B8C(fn_80201814(owner));
    if (info->family == 2 && info->kind == 8) {
        special = 1;
    }

    object = fn_801D0D78(0, flags, owner, position, fn_801E3644,
                          0, 0, 0, 0, 0);
    ((u8*)object)[0xFF1] = 3;
    *(u32*)((u8*)object + 8) = runtime;
    fn_801D0CA4(object);
    ((u8*)object)[0xC4] = 1;
    *(u32*)((u8*)object + 0xC8) = 0;
    *(u32*)((u8*)object + 0xC0) = runtime;
    *output_a = (u8*)object + 0xC4;
    *output_b = (u8*)object + 0xBC;
    if (output_d != 0) {
        *output_d = (u8*)object + 0xC8;
    }

    work = (u8*)object + 0xCC;
    *(void**)(work + 0xC0) = fn_80149E04();
    if (*(void**)(work + 0xC0) != 0) {
        fn_80147E88(work);
        fn_80149524(work, *(void**)(work + 0xC0));
        *(void**)(work + 0xA0) = fn_801499C4;
        if (owner == fn_80201AE4()) {
            work[0xBC] = 17;
        } else if (special != 0) {
            work[0xBC] = 1;
        } else {
            work[0xBC] = 4;
        }
        fn_80149B0C(*(void**)(work + 0xC0), 0, 0);
        fn_801A39DC(work);
        *(s16*)(work + 4) = fn_801D3A34(flags, 49);
        work[0] = fn_801CEB2C(flags);
        data = work + 0x14;
        *(u32*)(work + 0x24) = *(u32*)((u8*)object + 0x38);
        *(u32*)(work + 0x28) = *(u32*)((u8*)object + 0x3C);
        *(u32*)(work + 0x2C) = *(u32*)((u8*)object + 0x40);
        *(s16*)(work + 0x34) = 250;
        *(u32*)(work + 0x20) = runtime;
        work[0x3D] = (5 - (work[0] >> 1)) * 5;
        *(u32*)(work + 0x18) = owner;
        *(u32*)(work + 0x1C) = source;
        *output_c = data;
        data[0x2C] = fn_801D38E8(flags);
        if (resource != 0) {
            data[0x2D] = 128;
        }
        *(u32*)(work + 0xA8) = owner;
        *(void**)(work + 0x184) = fn_80149E04();
        if (*(void**)(work + 0x184) != 0) {
            secondary = work + 0xC4;
            fn_80147E88(secondary);
            fn_80148A98(secondary, *(void**)(work + 0x184));
            *(u32*)(secondary + 0x94) = 0;
            if (owner == fn_80201AE4()) {
                secondary[0xBC] = 17;
            } else if (special != 0) {
                secondary[0xBC] = 1;
            } else {
                secondary[0xBC] = 4;
            }
            **(u8**)(work + 0x184) = work[0];
            fn_80149B38(*(void**)(work + 0x184));
            fn_80184740(secondary);
            secondary[0] = 10;
            *(s16*)(secondary + 4) = fn_801D3A34(flags, 78);
            secondary[0x14] = 15;
            *(u32*)(secondary + 0x28) = runtime;
            *(u32*)(secondary + 0x2C) = lbl_802FC5BC[3];
            secondary[0x2F] = 224;
            fn_801E8328(27, work, lbl_802FC5BC[3]);
        } else {
            fn_80149EB8(*(void**)(work + 0xC0));
        }
    }
    return object;
}
