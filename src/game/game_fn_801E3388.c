typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object {
    u8 pad0[4];
    int flags;
    int runtime;
    int source;
    int sound;
    u8 pad14[0x14];
    void (*callback)(void*, void*);
    void* callback_arg;
    u8 pad30[8];
    u8 position[0xC];
    u32 lifetime;
    u8 pad48[0x74];
    int owner;
    u8 padC0[0xF30];
    u8 status;
    u8 padFF1[3];
    u16 state;
} Object;

typedef struct InfoOwner {
    u8 pad0[0x28];
    u8* value;
} InfoOwner;

extern int lbl_8064D18C;
extern float lbl_80651248;
extern void fn_801FE22C(u32);
extern void fn_801B05B0(int, int);
extern void fn_801E3314(Object*);
extern void* fn_80201B9C(void);
extern void* fn_80204844(void*, int);
extern InfoOwner* fn_80201B8C(void);
extern void* fn_80201814(int);
extern void* fn_80201B54(void*);
extern int fn_80201EB8(void*);
extern void fn_8020123C(int, void*, void*, void*);
extern void fn_801DA890(int);
extern u32 fn_801E2E1C(u32, int, int);
extern void* fn_801E3020(u32, u32, void*, int, int, void**, void***, void***, void**, u32);
extern void* fn_800CD568(int, int, u32, void*, void*, u32, float);
extern int fn_801CEB2C(u32);
extern void* fn_801DA3B0(u32, u32, void*, u8, int, int, void**, void**, void**, void***);
extern void* fn_801DA058(u32);
extern void* fn_800CD458(int, u32, void*, void*, void*, void*, void*);
extern void fn_801FE934(u32, int);

void fn_801E3388(Object* object)
{
    void* owner;
    u8* info_owner;
    void* info;

    if (object->runtime != lbl_8064D18C || (object->status & 1)) {
        fn_801FE22C(object->lifetime);
        if (object->sound != -1) {
            fn_801B05B0(object->sound, 10);
        }
        fn_801E3314(object);
        return;
    }

    switch (object->state) {
    case 0:
        owner = fn_80204844(fn_80201B9C(), 87);
        if (owner != 0) {
            info_owner = fn_80201B8C()->value;
            info = fn_80201814(*(int*)(info_owner + 8));
            if (info != 0) {
                void* value = fn_80201B54(owner);
                if (fn_80201EB8(info) == lbl_8064D18C) {
                    fn_8020123C(196, value, value, object->position);
                } else {
                    fn_8020123C(57, value, value, 0);
                }
                fn_801DA890(*(int*)(info_owner + 8));
            }
        }

        owner = (void*)object->owner;
        if (fn_80201814((int)owner) != 0) {
            void* output_a;
            void** output_b;
            void** output_c;
            void* output_d;
            u32 alternate_flags;
            u32 resource;
            resource = fn_801E2E1C(object->flags, (int)owner, object->source);
            fn_801E3020(object->runtime, object->flags, object->position,
                         object->source, (int)owner, &output_a, &output_b,
                         &output_c, &output_d, resource);
            *output_b = fn_80201B54(fn_800CD568(object->source,
                                                (int)owner, object->flags,
                                                output_a, output_d,
                                                resource, lbl_80651248));
            *output_c = *output_b;
            if ((object->flags & 0xF) == 8 && resource != 0) {
                void* second_b;
                void** second_d;
                u8 kind;
                alternate_flags = (object->flags & ~0x810) | 0x1010;
                kind = fn_801CEB2C(alternate_flags);
                *second_d = fn_80201B54(fn_800CD458((int)owner,
                                                    alternate_flags,
                                                    fn_801DA058(alternate_flags),
                                                    output_a, second_b, output_d,
                                                    (void*)(resource =
                                                    (u32)fn_801DA3B0(
                                                        object->runtime,
                                                        alternate_flags,
                                                        object->position, kind,
                                                        (int)owner, 0,
                                                        &output_a, &second_b,
                                                        &output_d, &second_d))));
            }
        } else {
            fn_801FE22C(object->lifetime);
            if (object->sound != -1) {
                fn_801B05B0(object->sound, 10);
            }
            fn_801E3314(object);
        }
        break;
    case 20:
        fn_801FE934(object->lifetime, 10);
        break;
    case 140:
        if (object->callback != 0) {
            object->callback(object, object->callback_arg);
        }
        fn_801E3314(object);
        break;
    }
}
