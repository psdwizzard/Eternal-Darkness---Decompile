typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Runtime80093D20 {
    u8 pad00[0x8C];
    u32* state;
    u8 pad90[0xF];
    u8 kind;
} Runtime80093D20;

extern int lbl_8064D18C;
extern float lbl_8064EC98;

extern void *fn_80201B8C();
extern void *fn_80201BC8();
extern int fn_80201B54();
extern int fn_80201EB8();
extern u32 fn_80036D5C(void*);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_801287C4(void*, void*, int, int);
extern void fn_80128C28();
extern void fn_80128C44(void*, void*, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_80204810(void);
extern int fn_801E8328();
extern int fn_80200C20(void*);
extern int fn_80201B44();
extern void* fn_801A717C(void);
extern void fn_801A74A0(void*, int);
extern void fn_801A74A8(void*, int);
extern void fn_801A7538(void*, int);
extern void fn_801A7518();
extern unsigned long long fn_8020123C();
extern void fn_801A7228(void*);
extern void fn_8003CB6C(void);
extern int fn_800389E0(void*, int, int, int);
extern void fn_80201138(float, int, void*, int, int, int);

void fn_80093D20(register void* object, register void* source)
{
    register Runtime80093D20* runtime = ((Runtime80093D20*)fn_80201B8C(object));
    register short amount;
    register void* resource = fn_80201BC8(object);
    register int id = fn_80201B54(object);
    register int room = fn_80201EB8(object);
    register u32 flags = fn_80036D5C(object);

    if ((flags & 0x80) != 0 || (flags & 0x8000) != 0) {
        resource = fn_801294DC(resource, 0x92, 0x20, 10);
        if (resource != 0) {
            int value = id << 8;
            fn_801287C4(resource, fn_80204810, value | 0xA9, 0x14);
            fn_80128C28(resource, fn_80204810, value | 0x77);
            fn_80128C44(resource, fn_80204810, value | 0x77);
            fn_80201D2C(object, 0x37);
            fn_80201D14(object, 1);
        }
        return;
    }

    if (room != lbl_8064D18C) {
        fn_801E8328(2, object);
        return;
    }

    resource = fn_801294DC(resource, 0x18, 0x20, 10);
    if (resource != 0) {
        if (runtime->kind == 10 || runtime->kind == 0x18) {
            int source_id = fn_80200C20(source);
            int current_id = fn_80201B44();
            amount = -0x23;
            if (runtime->kind == 10) {
                amount = 0x32;
            }
            if (source_id == current_id && runtime->state != 0 &&
                ((*runtime->state & 0x00020000) == 0)) {
                void* effect = fn_801A717C();
                int object_id = fn_80201B54(object);
                fn_801A74A0(effect, object_id);
                fn_801A74A8(effect, current_id);
                fn_801A7538(effect, 2);
                fn_801A7518(effect, amount);
                fn_8020123C(0x27, object_id, current_id, effect);
                fn_801A7228(effect);
            }
        }
        fn_80128C28(resource, fn_8003CB6C, id);
        fn_800389E0(object, 0, 0, 1);
        fn_80201D2C(object, 8);
        fn_80201D14(object, 1);
        fn_80201138(lbl_8064EC98, 0x11, object, 8, -1, 0);
    }
}
