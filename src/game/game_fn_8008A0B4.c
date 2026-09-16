typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec3Words {
    u32 x, y, z;
} Vec3Words;

typedef struct SpawnConfig {
    u32 value;
    u32 word;
    u16 half;
} SpawnConfig;

typedef struct Memory {
    u8 pad00[0x90];
    u32 callback;
    void* object;
    u32 position[3];
    u8 config[6];
    u8 mode;
    u8 padAB[0x1695];
    u32 identifier;
    u8 pad1744[0x3C];
    int handle;
} Memory;

typedef struct Runtime {
    u8 pad[0x15C];
    Memory* memory;
} Runtime;

typedef struct Work {
    u8 bytes[0xC4];
    Runtime* runtime;
} Work;

extern void *fn_8006ED3C();
extern int fn_8006D548();
extern void fn_8008799C(u8);
extern int fn_800879E0(u8);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern int fn_8011F6A4(void*, int, int, int, Vec3*, int);
extern void fn_8019BBF0(Memory*);
extern void fn_8019BC48(void);
extern int fn_801E79FC(void*, int);
extern void fn_80147EC4(Memory*);
extern u32 fn_801809A0(void*);
extern int fn_8012FF34(void*, Vec3*, int, int);
extern void fn_801302BC(void*, u16);
extern void* memcpy(void*, const void*, unsigned int);
extern u32 lbl_806519B8;
extern u16 lbl_806519BC;
extern void* lbl_8064C4E0;
extern u8 lbl_802FC5BC[];

/* NonMatching: size-exact; only the initial handle comparison uses r0 instead
 * of the retail r9. */
int fn_8008A0B4(Work* work)
{
    int index;
    u32 output[8];
    u32 position[3];
    SpawnConfig config;
    Memory* memory;
    Runtime* runtime;
    int result;

    config.value = 0;
    config.word = lbl_806519B8;
    config.half = lbl_806519BC;
    fn_8006ED3C(work, 5, &index);
    runtime = work->runtime;
    result = 0;
    memory = runtime->memory;
    memory->object = 0;
    memory->identifier = 0;

    if (memory->handle == -1) {
        void* owner = fn_80201814(*(void**)(work->bytes + 0x38));
        if (owner != 0) {
            void* scene = fn_80201BC8(owner);
            if (fn_8011F6A4(scene, 0, 1, -1, (Vec3*)output, 1) != -1) {
                position[0] = output[2];
                position[1] = output[3];
                position[2] = output[4];
            }
        }
        memory->handle = fn_8006D548(2, 0x1000, 4, position, &config, 0, 0);
    } else {
        memory->handle = fn_8006D548(2, 0x1000, 1, position, &config, 0);
    }

    if (memory->handle != -1) {
        fn_8019BBF0(memory);
        memory->callback = (u32)fn_8019BC48;
        *(Vec3Words*)memory->position = *(Vec3Words*)position;
        memory->object = 0;
        ((u8*)memory)[0xAA] = 4;
        if (fn_801E79FC(lbl_8064C4E0, 0x2ED) != 0)
            *(u32*)((u8*)memory + 0x18) = *(u32*)(lbl_802FC5BC + 0x24);
        memcpy((u8*)memory + 0xA4, (u8*)&config + 4, 6);
        if (config.value > 0x60)
            *(u16*)((u8*)memory + 0x16) = 0x80;
        else if (config.value > 0x30)
            *(u16*)((u8*)memory + 0x16) = 0x40;
        fn_80147EC4(memory);
        if (memory->object != 0) {
            void* scene;
            fn_8008799C(work->bytes[0x15]);
            memory->identifier = fn_801809A0(memory->object);
            scene = fn_80201BC8(fn_80201814(*(void**)(work->bytes + 0x38)));
            if (fn_8012FF34(scene, (Vec3*)position, 4, 2) != 0)
                fn_801302BC(scene, fn_800879E0(work->bytes[0x15]));
            memory->handle = -1;
            result = 1;
        }
    }
    return result;
}
