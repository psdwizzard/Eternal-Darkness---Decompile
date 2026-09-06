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
extern void fn_8014A248(Descriptor*, void*);
extern void fn_8014A040(Descriptor*, void*);
extern void fn_80149B0C(void*, void*, void*);
extern void fn_801938FC(void*);
extern void fn_80149B60(void*, u16*, void*, void*, int);
extern void fn_801D3CAC(int, int, void*);
extern void* fn_80148300(void*, Descriptor*, void*);
extern void fn_80149EB8(void*);

void* fn_801D5BC8(Vec3f* position, u32 object_id, void* first, void* second,
                  int type, int spawn_first, int spawn_third, u8 spawn_second,
                  u8 value14, u8 value15, u8 value17, u8 value18,
                  u8 value16, int enable, u16 value06)
{
    Descriptor descriptor;
    Descriptor child_descriptor;
    void* object;
    void* list;
    void* work;
    void* owner;
    u8 failed;
    void* child;
    u8* params;
    owner = 0;
    object = fn_80201814(object_id);
    if (object != 0) {
        list = fn_80155DB4();
        if (list != 0) {
            work = fn_80149E04();
            if (work != 0) {
                fn_80147E88(&descriptor);
                fn_8014A248(&descriptor, work);
                fn_80149B0C(work, first, second);
                fn_801938FC(&descriptor);
                *(u16*)(descriptor.bytes + 6) = value06;
                params = descriptor.bytes + 0x14;
                *(u16*)(params + 8) = (u16)(int)position->x;
                *(u16*)(params + 10) = (u16)(int)position->y;
                *(u16*)(params + 12) = (u16)(int)position->z;
                fn_80149B60(object, (u16*)(params + 0xE), first, second, 0);
                descriptor.flags = descriptor.flags | 0x44040;
                params[0] = value14;
                params[1] = value15;
                if (enable == 0)
                    descriptor.flags &= 0xFFFFFF7FU;
                fn_801D3CAC(type, 0, params);
                params[3] = value17;
                params[4] = value18;
                params[2] = value16;
                owner = fn_80148300(list, &descriptor, work);
                if (owner != 0) {
                    failed = 0;
                    if (spawn_first != 0) {
                        child = fn_80149E04();
                        if (child != 0) {
                            fn_80147E88(&child_descriptor);
                            fn_8014A040(&child_descriptor, child);
                            fn_801938FC(&child_descriptor);
                            child_descriptor.bytes[0x14] = value14 >> 2;
                            child_descriptor.bytes[0x15] = value15 >> 1;
                            child_descriptor.flags |= 0x4651;
                            fn_801D3CAC(type, 0, child_descriptor.bytes + 0x14);
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
                            child_descriptor.bytes[0x14] = value14 >> 2;
                            child_descriptor.bytes[0x15] = value15 >> 1;
                            child_descriptor.flags |= 0x4352;
                            fn_801D3CAC(type, 0, child_descriptor.bytes + 0x14);
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
                            child_descriptor.bytes[0x14] = value14 >> 2;
                            child_descriptor.bytes[0x15] = value15 >> 1;
                            child_descriptor.flags |= 0x4654;
                            fn_801D3CAC(type, 0, child_descriptor.bytes + 0x14);
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
