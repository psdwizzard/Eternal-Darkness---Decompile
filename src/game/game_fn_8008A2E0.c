typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Context {
    u8 pad[8];
    s16 counter;
} Context;

typedef struct Runtime {
    u8 pad[0x15C];
    u8* memory;
} Runtime;

typedef struct Work {
    u8 bytes[0xC4];
    Runtime* runtime;
} Work;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct SVec3 { s16 x, y, z; } SVec3;

extern void *fn_8006ED3C();
extern void fn_8006BEE4(Context*, void (*)(void));
extern void fn_8006EA4C(void);
extern u32 fn_801809A0(void*);
extern void* fn_80155DB4(void*);
extern int fn_80157034(void*);
extern int fn_80157050(void*);
extern void* fn_80149E04(void);
extern int fn_8017FDF4(void*);
extern SVec3* fn_8017FDE4(void*);
extern void fn_801489B4(void*, void*);
extern void fn_8014E33C(void);
extern void fn_80184950(void);
extern void fn_80184740(void*);
extern int fn_801E79FC(void*, int);
extern void fn_80149B38(void*);
extern int fn_801E8328();
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8014D98C(void*, Vec3*, Vec3*, int, int, u32*);
extern void fn_8014E4C0(void*, void*);
extern void fn_8019BCEC(void*);
extern u32 lbl_8064EBB0;
extern u32 lbl_8064EBB4;
extern u32 lbl_8064EBB8;
extern void* lbl_8064C4E0;
extern u8 lbl_802FC5BC[];
extern const Vec3 lbl_80239620;

int fn_8008A2E0(Work* work)
{
    int index;
    Context* context = fn_8006ED3C(work, 5, &index);
    u8* effect;
    u8* secondary;
    u8* memory;
    int result = 0;
    u32 identifier;

    memory = work->runtime->memory;
    effect = memory + 0xB00;
    secondary = memory + 0xBC4;

    context->counter++;
    if (context->counter >= 8)
        fn_8006BEE4(context, fn_8006EA4C);

    if (*(void**)(memory + 0x94) != 0) {
        identifier = fn_801809A0(*(void**)(memory + 0x94));
        if (identifier == *(u32*)(memory + 0x1740)) {
            void* object = fn_80155DB4(*(void**)(memory + 0x94));
            if (object != 0 && fn_80157034(object) == 0 &&
                fn_80157050(*(void**)(memory + 0x94)) == 0) {
                *(void**)(effect + 0xC0) = fn_80149E04();
                if (*(void**)(effect + 0xC0) != 0) {
                    u32 color = lbl_8064EBB0;
                    u32 soundColor;
                    int value = fn_8017FDF4(*(void**)(memory + 0x94));
                    Vec3 position;
                    Vec3 direction;
                    int mode;
                    void* scene;
                    SVec3* source;

                    fn_801489B4(effect, *(void**)(effect + 0xC0));
                    *(u32*)(effect + 0x94) = 0;
                    *(void (**)(void))(effect + 0x98) = fn_8014E33C;
                    *(void (**)(void))(effect + 0x90) = fn_80184950;
                    effect[0xBC] = 4;
                    fn_80184740(effect);
                    *(s8*)(effect + 3) = -4;
                    *(s16*)(effect + 4) = -1;
                    effect[0x14] = 12;
                    *(int*)(effect + 0x28) = value;
                    if (fn_801E79FC(lbl_8064C4E0, 0x2ED) != 0) {
                        ((u8*)&color)[0] = 0;
                        ((u8*)&color)[1] = 0xFF;
                        ((u8*)&color)[2] = 0;
                    }
                    *(u32*)(effect + 0x2C) = color;
                    (*(u8**)(effect + 0xC0))[0] = memory[0];
                    fn_80149B38(*(void**)(effect + 0xC0));
                    *(u32*)(effect + 0xA8) = identifier;
                    fn_801E8328(0x1A, effect);

                    soundColor = lbl_8064EBB4;
                    mode = 2;
                    direction = lbl_80239620;
                    scene = fn_80201BC8(fn_80201814(*(void**)(work->bytes + 0x38)));
                    source = fn_8017FDE4(*(void**)(memory + 0x94));
                    position.x = source->x;
                    position.y = source->y;
                    position.z = source->z;
                    if ((context->counter & 1) == 0)
                        mode = 0;
                    fn_8014D98C(scene, &position, &direction,
                                mode, 1, &soundColor);
                }

                *(void**)(secondary + 0xC0) = fn_80149E04();
                if (*(void**)(secondary + 0xC0) != 0) {
                    volatile u32 color = lbl_8064EBB8;
                    fn_8014E4C0(secondary, *(void**)(secondary + 0xC0));
                    fn_8019BCEC(secondary);
                    *(u32*)(secondary + 0x18) = color;
                    if (fn_801E79FC(lbl_8064C4E0, 0x2ED) != 0)
                        *(u32*)(secondary + 0x18) = *(u32*)(lbl_802FC5BC + 0x24);
                    *(u32*)(secondary + 0xA8) = identifier;
                    secondary[0xBC] = 4;
                    fn_801E8328(0x12, secondary);
                }
                result = 1;
            }
        }
    }
    return result;
}
