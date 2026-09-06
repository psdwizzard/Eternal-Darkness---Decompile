typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object {
    u8 bytes[0x1000];
} Object;

extern int lbl_8064D18C;
extern u32 lbl_80651EE0;
extern u16 lbl_80651EE4;
extern float lbl_80651160;
extern void fn_801FE22C(u32);
extern u32 fn_80201B54(void*);
extern unsigned long long fn_8020123C(u32, u32, u32, u32);
extern void fn_801D1318(u32);
extern void fn_801A9E40(int);
extern void fn_801B05B0(u32, u32);
extern void fn_801D0E78(Object*);
extern u32 fn_801D3944(u32);
extern u32 fn_801D3A34(u32, u32);
extern u32 fn_801CEB2C(u32);
extern void fn_8014E9B0(void*, void*, u32, u32, u32*, u32, u32, u32);
extern void* fn_80201814(u32);
extern u32 fn_80201B64(void*);
extern void fn_801FE934(u32, u32);
extern void fn_801D9A68(Object*);
extern void fn_801858E0(void*);
extern u32 fn_801D38E8(u32);
extern void fn_801D38BC(u32, void*, void*);
extern void fn_80185AE8(void);
extern void* memcpy(void*, const void*, u32);
extern void fn_801E8328(u32, void*);

void fn_801D9D14(Object* self)
{
    u32 owner;
    u32 value;
    u8* effect;
    u32 xyz[3];

    if (*(u32*)(self->bytes + 8) != lbl_8064D18C ||
        (*(u8*)(self->bytes + 0xFF0) & 1) != 0) {
        fn_801FE22C(*(u32*)(self->bytes + 0x44));
        if (*(u16*)(self->bytes + 0xFF4) <= 0x62 &&
            *(void**)(self->bytes + 0x30) != 0) {
            u32 actor = fn_80201B54(*(void**)(self->bytes + 0x30));
            fn_8020123C(0x39, actor, actor, 0);
        }
        if ((*(u8*)(self->bytes + 0xFF0) & 0x10) != 0)
            fn_801D1318(0);
        fn_801A9E40(-1);
        if (*(u32*)(self->bytes + 0x10) != -1U)
            fn_801B05B0(*(u32*)(self->bytes + 0x10), 10);
        fn_801D0E78(self);
        return;
    }

    owner = *(u32*)(self->bytes + 4);
    if ((*(u16*)(self->bytes + 0xFF4) & 0xF) == 0) {
        xyz[0] = fn_801D3944(owner);
        value = fn_801D3A34(owner, 0x35);
        fn_8014E9B0(self->bytes + 0x16C, self->bytes + 0x38,
                    fn_801CEB2C(owner), value, xyz, 3, 4, 1);
    }

    switch (*(u16*)(self->bytes + 0xFF4)) {
    case 0x3C: {
        void* node = fn_80201814(*(u32*)(self->bytes + 0xC));
        if (node != 0 && fn_80201B64(node) != 8) {
            u32 init[2];
            init[0] = lbl_80651EE0;
            *(u16*)((u8*)init + 4) = lbl_80651EE4;
            fn_801FE934(*(u32*)(self->bytes + 0x44), 0x3C);
            fn_801D9A68(self);
            effect = self->bytes + 0xBC;
            fn_801858E0(effect);
            fn_801D38BC(fn_801D38E8(owner), effect + 0x78, effect + 4);
            effect[1] = 0x80;
            *(u16*)(effect + 8) = 20;
            *(u16*)(effect + 6) = 45;
            effect[3] = (u8)-10;
            effect[0x14] = 30;
            *(u16*)(effect + 0x1C) = 0x80;
            effect[0x18] |= 2;
            effect[0x19] = 8;
            *(void (**)(void))(effect + 0x90) = fn_80185AE8;
            xyz[0] = *(u32*)(self->bytes + 0x38);
            xyz[1] = *(u32*)(self->bytes + 0x3C);
            xyz[2] = *(u32*)(self->bytes + 0x40);
            *(float*)&xyz[2] += lbl_80651160;
            *(u32*)(effect + 0x98) = xyz[0];
            *(u32*)(effect + 0x9C) = xyz[1];
            *(u32*)(effect + 0xA0) = xyz[2];
            memcpy(effect + 0xA4, init, 6);
            *(u32*)(effect + 0x94) = 0;
            effect[0xAA] = 4;
            fn_801E8328(0x10, effect);
        }
        break;
    }
    case 0x62:
        if (*(void**)(self->bytes + 0x30) != 0) {
            u32 actor = fn_80201B54(*(void**)(self->bytes + 0x30));
            fn_8020123C(0x39, actor, actor, 0);
        }
        break;
    case 0x76:
        if (*(void (**)(Object*, u32))(self->bytes + 0x28) != 0)
            (*(void (**)(Object*, u32))(self->bytes + 0x28))(self, *(u32*)(self->bytes + 0x2C));
        if ((*(u8*)(self->bytes + 0xFF0) & 0x10) != 0)
            fn_801D1318(0);
        fn_801A9E40(-1);
        fn_801D0E78(self);
        break;
    }
}
