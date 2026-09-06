typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
typedef struct Vec3f { f32 x, y, z; } Vec3f;
typedef struct Descriptor { u8 bytes[0x38]; u32 flags; u8 tail[0x84]; } Descriptor;

extern void* fn_80201814(u32);
extern void* fn_80155DB4(void);
extern void* fn_80149E04(void);
extern void fn_80147E88(Descriptor*);
extern void fn_8014A2AC(Descriptor*, void*);
extern void fn_8014A040(Descriptor*, void*);
extern void fn_80149B0C(void*, void*, void*);
extern void fn_801938FC(void*);
extern void fn_80149C1C(void*, u16*, void*, void*, int);
extern void fn_801D3CAC(int, int, void*);
extern void* fn_80148300(void*, Descriptor*, void*);
extern void fn_80149EB8(void*);

void* fn_801D6B44(u32 object_id, void* first, void* second, int index,
                  Vec3f* position, int type, int spawn_first, int spawn_third,
                  u8 spawn_second, u8 main14, u8 main15, u8 child14,
                  u8 child15, int set_4000, int set_8000, u8 main17,
                  u8 main18, u8 child18, u8 main16, int enable,
                  u16 value06, u32 flags)
{
    Descriptor descriptor;
    Descriptor child_descriptor;
    void* object;
    void* owner;
    void* list;
    void* work;
    void* child;
    u8 failed;
    u8* params;

    owner = 0;
    object = fn_80201814(object_id);
    if (object != 0) {
        list = fn_80155DB4();
        if (list != 0) {
            work = fn_80149E04();
            if (work != 0) {
                fn_80147E88(&descriptor);
                fn_8014A2AC(&descriptor, work);
                fn_80149B0C(work, first, second);
                fn_801938FC(&descriptor);
                *(u16*)(descriptor.bytes + 6) = value06;
                params = descriptor.bytes + 0x14;
                fn_80149C1C(object, (u16*)(params + 8), first, second, index);
                *(u16*)(params + 0xE) = (u16)(int)position->x;
                *(u16*)(params + 0x10) = (u16)(int)position->y;
                *(u16*)(params + 0x12) = (u16)(int)position->z;
                params[1] = main15;
                params[0] = main14;
                params[6] = index;
                descriptor.flags |= flags;
                if (set_4000 != 0) descriptor.flags |= 0x4000;
                if (set_8000 != 0) descriptor.flags |= 0x8000U;
                if (enable == 0) descriptor.flags &= 0xFFFFFF7FU;
                fn_801D3CAC(type, 0, params);
                params[3] = main17;
                descriptor.bytes[0x19] = 0x40;
                params[2] = main16;
                params[4] = main18;
                owner = fn_80148300(list, &descriptor, work);
                if (owner != 0) {
                    failed = 0;
                    if (spawn_first != 0) {
                        child = fn_80149E04();
                        if (child != 0) {
                            fn_80147E88(&child_descriptor);
                            fn_8014A040(&child_descriptor, child);
                            fn_801938FC(&child_descriptor);
                            child_descriptor.bytes[0x14] = child14;
                            child_descriptor.bytes[0x15] = child15;
                            child_descriptor.flags |= 0x651;
                            if (set_4000 != 0) child_descriptor.flags |= 0x4000;
                            if (set_8000 != 0) child_descriptor.flags |= 0x8000U;
                            fn_801D3CAC(type, 0, child_descriptor.bytes + 0x14);
                            child_descriptor.bytes[0x18] = child18;
                            child_descriptor.bytes[0x16] = main16;
                            if (fn_80148300(owner, &child_descriptor, child) == 0) {
                                fn_80149EB8(child);
                                failed = 1;
                            }
                        } else failed = 1;
                    }
                    if (spawn_second != 0 && failed == 0) {
                        child = fn_80149E04();
                        if (child != 0) {
                            fn_80147E88(&child_descriptor);
                            fn_8014A040(&child_descriptor, child);
                            *(u8*)child = spawn_second;
                            fn_801938FC(&child_descriptor);
                            child_descriptor.bytes[0x14] = child14;
                            child_descriptor.bytes[0x15] = child15;
                            child_descriptor.flags |= 0x352;
                            if (set_4000 != 0) child_descriptor.flags |= 0x4000;
                            if (set_8000 != 0) child_descriptor.flags |= 0x8000U;
                            fn_801D3CAC(type, 0, child_descriptor.bytes + 0x14);
                            child_descriptor.bytes[0x18] = child18;
                            child_descriptor.bytes[0x16] = main16;
                            if (fn_80148300(owner, &child_descriptor, child) == 0) {
                                fn_80149EB8(child);
                                failed = 1;
                            }
                        } else failed = 1;
                    }
                    if (spawn_third != 0 && failed == 0) {
                        child = fn_80149E04();
                        if (child != 0) {
                            fn_80147E88(&child_descriptor);
                            fn_8014A040(&child_descriptor, child);
                            fn_801938FC(&child_descriptor);
                            child_descriptor.bytes[0x14] = child14;
                            child_descriptor.bytes[0x15] = child15;
                            child_descriptor.flags |= 0x654;
                            if (set_4000 != 0) child_descriptor.flags |= 0x4000;
                            if (set_8000 != 0) child_descriptor.flags |= 0x8000U;
                            fn_801D3CAC(type, 0, child_descriptor.bytes + 0x14);
                            child_descriptor.bytes[0x18] = child18;
                            child_descriptor.bytes[0x16] = main16;
                            if (fn_80148300(owner, &child_descriptor, child) == 0)
                                fn_80149EB8(child);
                        }
                    }
                } else fn_80149EB8(work);
            }
        }
    }
    return owner;
}
