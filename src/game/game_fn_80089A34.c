/*
 * Honest-C reconstruction of the effect/resource dispatch callback.
 * This remains NonMatching: floating-point temporaries and register allocation
 * still differ.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Work { u8 bytes[0xC4]; void* runtime; } Work;
typedef struct PositionTable { Vec3 positions[16]; } PositionTable;
typedef struct EffectDescriptor {
    u8 header[0x28];
    PositionTable table;
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
extern void fn_8014CBE8(void*, int, void*, int, void*);
extern void fn_8011E174(int, int);
extern void* fn_80036D38(void*);
extern void fn_8012B690(void*, Vec3*, Vec3*);
extern void fn_8006DEF8(Work*, int, void*, Work*, u16);
extern int lbl_8064B820;
extern const Vec3 lbl_80239554;
extern const PositionTable lbl_80239560;
extern const u8 lbl_802FC5BC[];

int fn_80089A34(Work* work)
{
    void* guard = fn_801A717C();
    u8* runtime = *(u8**)(work->bytes + 0xC4);
    Work* workCopy = work;
    u8* runtimeFlags;
    int index;
    int result = 0;
    void* owner;
    EffectMemory* memory;

    fn_8006ED3C(work, 0xB, &index);
    owner = fn_80201814(*(void**)(work->bytes + 0x38));
    memory = *(EffectMemory**)(*(u8**)(work->bytes + 0xC4) + 0x15C);
    if (owner != 0) {
        Vec3 position;
        Vec3 direction = lbl_80239554;
        EffectDescriptor descriptor;
        int slot;
        int identifier;
        void* scene;
        void* spawned = 0;
        u32 flags;
        int i;

        descriptor.table = lbl_80239560;
        slot = memory->slot;
        runtimeFlags = *(u8**)(workCopy->bytes + 0xC4);
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
        fn_8020123C(0x35, 0, *(void**)(work->bytes + 0x38), guard);

        if (identifier == 1)
            goto identifier_one;
        if (identifier < 1 || identifier >= 4)
            goto identifier_other;
        {
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
            }
            if (lbl_8064B820 != 0)
                fn_8014CBE8(owner, 0x14, (void*)lbl_802FC5BC, identifier,
                            (void*)(lbl_802FC5BC + 0x18));
            flags = *(u32*)(runtimeFlags + 0x20);
            flags |= 0x10000000;
            flags |= 0x1200;
            *(u32*)(runtimeFlags + 0x20) = flags;
            fn_8011E174(0x100, 1);
            goto identifier_done;
        }
identifier_one:
        {
            void* state = fn_80036D38(owner);
            int stateValue = *(int*)((u8*)state + 0x44);
            *(u32*)(runtimeFlags + 0x20) |= 3;
            if (spawned != 0) {
                void* animation = fn_80158598(((void*)fn_80201B54(owner)), 0);
                int handle = fn_80157FE0(animation, 4, 0);
                *(int*)(runtime + 0xA4) = handle;
                if (handle != -1)
                    fn_80158038(animation, handle);
            }
            for (i = 0; i < 16; i++) {
                direction.x = (float)(8 - (int)(fn_800FBFB0() & 15));
                direction.y = (float)(8 - (int)(fn_800FBFB0() & 15));
                direction.z = 8.0f;
                fn_8012B690(scene, &descriptor.table.positions[i], &position);
                fn_8014D478(scene, &position, &direction, 0, 4,
                            (void*)(lbl_802FC5BC + 0x18), 1);
            }
            workCopy->bytes[index * 0x2C + 0x6A] = 0;
            workCopy->bytes[index * 0x2C + 0x6B] = 0;
            workCopy->bytes[index * 0x2C + 0x68] = 4;
            fn_8006DEF8(workCopy, 0xB, 0, 0, 0);
            fn_8020123C(8, stateValue, *(void**)(work->bytes + 0x38), 0);
            goto identifier_done;
        }
identifier_other:
        if (lbl_8064B820 != 0) {
            fn_8014CBE8(owner, 0x14, (void*)lbl_802FC5BC, identifier,
                        (void*)(lbl_802FC5BC + 0x18));
        }

identifier_done:
        memory->slot++;
        result = 1;
        slot = memory->slot;
        memory->slot = slot >= 16 ? 0 : slot;
    }
    fn_801A7228(guard);
    return result;
}
