typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void* fn_80201814(u32);
extern void* fn_80201B8C(void);
extern int fn_80201B64(void*);
extern int fn_80201B5C(void*);
extern int fn_80201AE4(void);
extern void fn_801DB140(void);
extern void* fn_801D0D78(u32, u32, u32, void*, void (*)(void), u32, u32,
                         u32, u32, u32);
extern void fn_801D0CA4(void*);
extern void* fn_80149E04(void);
extern void fn_80149EB8(void*);
extern void fn_80147E88(void*);
extern void fn_80149590(void*, void*);
extern void fn_80148A98(void*, void*);
extern void fn_80149B60(void);
extern void fn_80149B0C(void*, u32, u32);
extern void fn_80149B38(void*);
extern void fn_80191360(void*);
extern void fn_80184740(void*);
extern u32 fn_801D3A34(u32, u32);
extern void fn_801E8328(u32, void*);
extern u8 lbl_802FC5BC[];

void* fn_801DA3B0(void* runtime, u32 flags, void* position, void* value,
                  int owner, u8 option, void** output_a, void** output_b,
                  void** output_d, void** output_c)
{
    void* owner_object;
    u8* object;
    int special;

    object = 0;
    owner_object = fn_80201814(owner);
    if (owner_object != 0) {
        u8* state;
        u8* effect;
        void* allocated;
        u32 kind;
        int alternate;
        u8* info = fn_80201B8C();

        special = 0;
        if (info[0x9E] == 2 && info[0x9F] == 8)
            special = 1;

        object = fn_801D0D78(0, flags, owner, position, fn_801DB140,
                              0, 0, 0, 0, 0);
        object[0xFF1] = 2;
        *(void**)(object + 8) = runtime;
        fn_801D0CA4(object);
        object[0xC4] = 1;

        state = object + 0xBC;
        if (option != 0)
            state[8] |= 8;
        state[9] = 40;
        state[10] = 0;
        *(u32*)(state + 12) = 0;
        *(void**)(state + 4) = runtime;
        *(u32*)state = 0;
        *output_a = state + 8;
        *output_b = state + 10;
        if (output_d != 0)
            *output_d = state + 12;
        *output_c = state;

        effect = object + 0xCC;
        allocated = fn_80149E04();
        *(void**)(effect + 0xC0) = allocated;
        if (*(void**)(effect + 0xC0) != 0) {
        alternate = 0;
        if (fn_80201B64(owner_object) == 0x30 &&
            fn_80201B5C(owner_object) == 0x2A)
            alternate = 1;

        fn_80147E88(effect);
        fn_80149590(effect, *(void**)(effect + 0xC0));
        *(void (**)(void))(effect + 0xA0) = fn_80149B60;
        if (owner == fn_80201AE4())
            effect[0xBC] = 0x11;
        else if (special)
            effect[0xBC] = 1;
        else
            effect[0xBC] = 4;
        fn_80149B0C(*(void**)(effect + 0xC0), 0, 0);
        fn_80191360(effect);
        *(u16*)(effect + 4) = fn_801D3A34(flags, 0x31);
        kind = flags & 0x70000;
        effect[0] = (u8)(u32)value;
        switch (kind) {
        case 0x10000:
            effect[1] = 6;
            break;
        case 0x20000:
            effect[1] = 8;
            break;
        case 0x40000:
            effect[1] = 10;
            break;
        }
        *(u32*)(effect + 0x24) = 1;
        *(u32*)(effect + 0x20) = 1;
        *(u32*)(effect + 0x34) = *(u32*)(object + 0x38);
        *(u32*)(effect + 0x38) = *(u32*)(object + 0x3C);
        *(u32*)(effect + 0x3C) = *(u32*)(object + 0x40);
        *(u16*)(effect + 0x28) = 250;
        *(u32*)(effect + 0x2C) = owner;
        *(void**)(effect + 0x30) = runtime;
        effect[0x1A] = (5 - (effect[0] >> 1)) * 5;
        if (alternate)
            *(u32*)(effect + 0x1C) = 1;
        *(u32*)(effect + 0xA8) = owner;

        allocated = fn_80149E04();
        *(void**)(effect + 0x184) = allocated;
        if (*(void**)(effect + 0x184) != 0) {
            u8* secondary = effect + 0xC4;
            fn_80147E88(secondary);
            fn_80148A98(secondary, *(void**)(effect + 0x184));
            *(u32*)(secondary + 0x94) = 0;
            if (owner == fn_80201AE4())
                secondary[0xBC] = 0x11;
            else if (special)
                secondary[0xBC] = 1;
            else
                secondary[0xBC] = 2;
            (*(u8**)(effect + 0x184))[0] = effect[0];
            fn_80149B38(*(void**)(effect + 0x184));
            fn_80184740(secondary);
            secondary[0] = 0x11;
            *(u16*)(secondary + 4) = fn_801D3A34(flags, 0x4E);
            secondary[1] -= 2;
            switch (kind) {
            case 0x10000:
                secondary[0x14] = 0x16;
                break;
            case 0x20000:
                secondary[0x14] = 0x11;
                break;
            case 0x40000:
                secondary[0x14] = 0x0D;
                break;
            }
            *(void**)(secondary + 0x28) = runtime;
            *(u32*)(secondary + 0x2C) = *(u32*)(lbl_802FC5BC + 0x0C);
            if (alternate)
                secondary[0x2F] = 0;
            else
                secondary[0x2F] = 0xE0;
            fn_801E8328(0x1B, effect);
        } else {
            fn_80149EB8(*(void**)(effect + 0xC0));
            *(u32*)(effect + 0xC0) = 0;
        }
        }
    }
    return object;
}
