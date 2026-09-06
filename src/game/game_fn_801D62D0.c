typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Descriptor { u8 bytes[0x38]; u32 flags; u8 tail[0x84]; } Descriptor;

extern void* fn_80201814(u32);
extern void* fn_80155DB4(void*);
extern void* fn_80149E04(void);
extern void fn_80147E88(Descriptor*);
extern void fn_8014A0A8(Descriptor*, void*);
extern void fn_8014A040(Descriptor*, void*);
extern void fn_80149B0C(void*, void*, void*);
extern void fn_801938FC(void*);
extern void fn_80149B60(void*, u16*, void*, void*, int);
extern void fn_801D3CAC(int, int, void*);
extern void* fn_80148300(void*, Descriptor*, void*);
extern void fn_80149EB8(void*);

void* fn_801D62D0(u32 first_id, void* first_a, void* first_b, u32 second_id,
                  void* second_a, void* second_b, int type, int spawn_first,
                  int spawn_third, u8 spawn_second, u8 main14, u8 main15,
                  u8 child14, u8 child15, int set_4000, int set_8000,
                  u8 child17, u8 main18, u8 child18, u8 main19, u8 main16,
                  int enable, u16 value06, u32 flags, u32 child_flags, u8 kind)
{
    Descriptor descriptor;
    Descriptor child_descriptor;
    void* first_object;
    void* owner;
    void* second_object;
    void* list;
    void* work;
    void* child;
    u8 failed;
    u8* params;

    owner = 0;
    first_object = fn_80201814(first_id);
    second_object = fn_80201814(second_id);
    if (first_object != 0 && second_object != 0) {
        list = fn_80155DB4(first_object);
        if (list != 0) {
            work = fn_80149E04();
            if (work != 0) {
                fn_80147E88(&descriptor);
                fn_8014A0A8(&descriptor, work);
                descriptor.bytes[0xBC] = kind;
                fn_80149B0C(work, first_a, first_b);
                fn_801938FC(&descriptor);
                *(u16*)(descriptor.bytes + 6) = value06;
                params = descriptor.bytes + 0x14;
                fn_80149B60(first_object, (u16*)(params + 8), first_a, first_b, 0);
                fn_80149B60(second_object, (u16*)(params + 0xE), second_a, second_b, 0);
                params[0] = main14;
                descriptor.flags |= flags;
                params[1] = main15;
                if (set_4000 != 0) descriptor.flags |= 0x4000;
                if (set_8000 != 0) descriptor.flags |= 0x8000U;
                if (enable == 0) descriptor.flags &= 0xFFFFFF7FU;
                fn_801D3CAC(type, kind & 0x80, params);
                params[3] = child17;
                params[4] = main18;
                params[2] = main16;
                params[5] = main19;
                *(u32*)(descriptor.bytes + 0x34) = second_id;
                *(void**)(descriptor.bytes + 0x3C) = second_a;
                *(void**)(descriptor.bytes + 0x40) = second_b;
                owner = fn_80148300(list, &descriptor, work);
                if (owner != 0) {
                    failed = 0;
                    if (spawn_first != 0) {
                        child = fn_80149E04();
                        if (child != 0) {
                            fn_80147E88(&child_descriptor);
                            fn_8014A040(&child_descriptor, child);
                            child_descriptor.bytes[0xBC] = kind;
                            fn_801938FC(&child_descriptor);
                            child_descriptor.bytes[0x14] = child14;
                            child_descriptor.bytes[0x15] = child15;
                            child_descriptor.flags |= child_flags | 0x241;
                            if (set_4000 != 0) child_descriptor.flags |= 0x4000;
                            if (set_8000 != 0) child_descriptor.flags |= 0x8000U;
                            child_descriptor.bytes[0x18] = child18;
                            child_descriptor.bytes[0x19] = child18 << 2;
                            fn_801D3CAC(type, kind & 0x80, child_descriptor.bytes + 0x14);
                            child_descriptor.bytes[0x17] = child17;
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
                            child_descriptor.bytes[0xBC] = kind;
                            *(u8*)child = spawn_second;
                            fn_801938FC(&child_descriptor);
                            child_descriptor.bytes[0x14] = child14;
                            child_descriptor.bytes[0x15] = child15;
                            child_descriptor.flags |= 0x352;
                            if (set_4000 != 0) child_descriptor.flags |= 0x4000;
                            if (set_8000 != 0) child_descriptor.flags |= 0x8000U;
                            child_descriptor.bytes[0x18] = child18;
                            fn_801D3CAC(type, kind & 0x80, child_descriptor.bytes + 0x14);
                            child_descriptor.bytes[0x17] = child17;
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
                            child_descriptor.bytes[0xBC] = kind;
                            fn_801938FC(&child_descriptor);
                            child_descriptor.bytes[0x14] = child14;
                            child_descriptor.bytes[0x15] = child15;
                            child_descriptor.flags |= child_flags | 0x244;
                            if (set_4000 != 0) child_descriptor.flags |= 0x4000;
                            if (set_8000 != 0) child_descriptor.flags |= 0x8000U;
                            child_descriptor.bytes[0x18] = child18;
                            child_descriptor.bytes[0x19] = child18 << 2;
                            fn_801D3CAC(type, kind & 0x80, child_descriptor.bytes + 0x14);
                            child_descriptor.bytes[0x17] = child17;
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
