typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct WorkSlot {
    u8 state;
    u8 pad01;
    u8 first;
    u8 second;
    u8 pad04[0x28];
} WorkSlot;
typedef struct Work {
    u8 pad00[0x38];
    void* owner;
    u8 pad3C[0x2C];
    WorkSlot slots[2];
    u8 padC0[4];
    u8* runtime;
} Work;
typedef struct PositionTable { Vec3 positions[16]; } PositionTable;
typedef struct EffectDescriptor {
    u8 header[0x28];
} EffectDescriptor;
typedef struct EffectMemory {
    u8 pad[0x1740];
    int identifiers[16];
    int slot;
} EffectMemory;

extern void* fn_801A717C(void);
extern void fn_801A7228(void*);
extern void fn_801A7470(void*, int);
extern void *fn_8006ED3C();
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void *fn_80201B8C();
extern int fn_80201B54();
extern void* fn_80205868(void*, int, Vec3*, int);
extern void* fn_80201A84(void*);
extern unsigned int fn_800FBFB0(void);
extern int fn_8011F6A4(void*, int, int, int, void*, int);
extern void fn_8014D478(void*, Vec3*, Vec3*, int, int, void*, int);
extern unsigned long long fn_8020123C();
extern void* fn_80158598(void*, int);
extern int fn_80157FE0(void*, int, int);
extern void fn_80158038(void*, int);
extern void fn_8014CBE8(void*, int, int, int*);
extern void fn_8011E174(int, int);
extern void* fn_80036D38(void*);
extern void fn_8012B690(void*, Vec3*, Vec3*);
extern void fn_8006DEF8(Work*, int, void*, Work*, u16);
extern int lbl_8064B820;
extern const Vec3 lbl_80239554;
extern const PositionTable lbl_80239560;
extern const u8 lbl_802FC5BC[];

int fn_80089A34(void* arg)
{
    u8* runtime;
    int result;
    void* owner;
    void* scene;
    Work* work;
    EffectMemory* memory;
    void* guard;
    int index;

    guard = fn_801A717C();
    runtime = ((Work*)arg)->runtime;
    work = arg;
    result = 0;
    fn_8006ED3C(arg, 0xB, &index);
    owner = fn_80201814(((Work*)arg)->owner);
    memory = *(EffectMemory**)(((Work*)arg)->runtime + 0x15C);
    if (owner != 0) {
        Vec3 position;
        Vec3 direction = lbl_80239554;
        EffectDescriptor descriptor;
        PositionTable table;
        int slot;
        void* spawned;
        int identifier;
        u8* runtimeFlags;
        int i;
        u32 flags;

        table = lbl_80239560;
        slot = memory->slot;
        runtimeFlags = work->runtime;
        identifier = memory->identifiers[slot];
        scene = fn_80201BC8(owner);
        fn_80201B8C(owner);
        if (lbl_8064B820 != 0) {
            spawned = fn_80205868(scene, identifier, &direction, 0x2000);
            if (spawned != 0)
                *(void**)(runtime + 0x94) = fn_80201A84(fn_80201BC8(spawned));
            else
                *(void**)(runtime + 0x94) = 0;
        } else {
            *(void**)(runtime + 0x94) = 0;
        }

        direction.x = (float)(8 - (int)(fn_800FBFB0() & 15));
        direction.y = (float)(8 - (int)(fn_800FBFB0() & 15));
        direction.z = 8.0f;
        if (fn_8011F6A4(scene, 0x14, identifier, -1, &descriptor, 1) != -1) {
            position = *(Vec3*)(descriptor.header + 8);
            fn_8014D478(scene, &position, &direction, 0x10, 4,
                        (void*)(lbl_802FC5BC + 0x18), 3);
        }

        fn_801A7470(guard, 0xB);
        fn_8020123C(0x35, 0, work->owner, guard);

        switch (identifier) {
        case 2:
        case 3:
            if (spawned != 0) {
                void* animation = fn_80158598(((void*)fn_80201B54(owner)), 0);
                int handle;
                if (identifier == 2) {
                    handle = fn_80157FE0(animation, 1, 0);
                    *(int*)(runtime + 0x9C) = handle;
                } else {
                    handle = fn_80157FE0(animation, 2, 0);
                    *(int*)(runtime + 0xA0) = handle;
                }
                if (handle != -1)
                    fn_80158038(animation, handle);
                if (lbl_8064B820 != 0)
                    fn_8014CBE8(owner, 0x14, identifier, (int*)(lbl_802FC5BC + 0x18));
            }
            flags = *(u32*)(runtimeFlags + 0x20);
            flags |= 0x100000;
            flags |= 0x1200;
            *(u32*)(runtimeFlags + 0x20) = flags;
            fn_8011E174(0x100, 1);
            break;
        case 1: {
            int handle;
            int stateValue;
            void* state;
            void* animation;

            state = fn_80036D38(owner);
            *(u32*)(runtimeFlags + 0x20) |= 3;
            stateValue = *(int*)((u8*)state + 0x44);
            if (spawned != 0) {
                animation = fn_80158598(((void*)fn_80201B54(owner)), 0);
                handle = fn_80157FE0(animation, 4, 0);
                *(int*)(runtime + 0xA4) = handle;
                if (handle != -1)
                    fn_80158038(animation, handle);
            }
            for (i = 0; i < 16; i++) {
                direction.x = (float)(8 - (int)(fn_800FBFB0() & 15));
                direction.y = (float)(8 - (int)(fn_800FBFB0() & 15));
                direction.z = 8.0f;
                fn_8012B690(scene, &table.positions[i], &position);
                fn_8014D478(scene, &position, &direction, 0, 4,
                            (void*)(lbl_802FC5BC + 0x18), 1);
            }
            work->slots[index].first = 0;
            work->slots[index].second = 0;
            work->slots[index].state = 4;
            fn_8006DEF8(work, 0xB, 0, 0, 0);
            fn_8020123C(8, stateValue, work->owner, 0);
            break;
        }
        default:
            if (lbl_8064B820 != 0)
                fn_8014CBE8(owner, 0x14, identifier, (int*)(lbl_802FC5BC + 0x18));
            break;
        }

        memory->slot++;
        result = 1;
        slot = memory->slot;
        memory->slot = slot >= 16 ? 0 : slot;
    }
    fn_801A7228(guard);
    return result;
}
