typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object {
    u8 bytes[0x1000];
} Object;

extern u32 lbl_8064D18C;
extern u32 lbl_8064D550;
extern void* fn_80201B54(void*);
extern void fn_8020123C(u32, void*, void*, u32);
extern void fn_801FDF3C(void*, u32);
extern void fn_801FDF00(void*, u32);
extern void fn_801FDFEC(void*, u32);
extern void fn_801FE024(void*, u32);
extern void fn_802006D4(void*, void*, int, u32, u32);
extern void fn_8019B134(void*, u32);

/*
 * Object update callback.  The retail routine continues through the object's
 * complete event/state dispatch after this recovered opening phase.
 */
void fn_801CEF74(Object* object)
{
    Object* owner = *(Object**)(object->bytes + 0x284);
    u32 local_gate = 0;
    u32* gate = &local_gate;
    u8 flags = object->bytes[0xFF0];

    if (flags & 0x10) {
        gate = &lbl_8064D550;
    }

    if (*gate == 0 && *(u32*)(object->bytes + 8) == lbl_8064D18C &&
        !(owner->bytes[0xFF0] & 1) && !(flags & 1)) {
        return;
    }

    if (*(u16*)(object->bytes + 0xFF4) > 10) {
        void* effect = *(void**)(owner->bytes + 0x30);
        if (effect != 0) {
            void* data = fn_80201B54(effect);
            fn_8020123C(0x39, data, data, 0);
        }
        if (*(u16*)(object->bytes + 0xFF4) > 20) {
            void* handle = *(void**)(owner->bytes + 0x44);
            fn_801FDF3C(handle, 0);
            fn_801FDF00(handle, 0);
            fn_801FDFEC(handle, 0);
            fn_801FE024(handle, 60);
        }
    }
}
