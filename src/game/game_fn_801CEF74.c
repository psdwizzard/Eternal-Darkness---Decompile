typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Object {
    u8 bytes[0x1000];
} Object;

extern int lbl_8064D18C;
extern int lbl_8064D548;
extern int lbl_8064D550;
extern void* fn_80201B54(void*);
extern void fn_8020123C(u32, void*, void*, u32);
extern void fn_801FDF3C(void*, u32);
extern void fn_801FDF00(void*, u32);
extern void fn_801FDFEC(void*, u32);
extern void fn_801FE024(void*, u32);
extern void fn_802006D4(void*, void*, int, u32, u32);
extern void fn_8019B134(void*, u32);
extern void fn_801D313C(u32, u32, void*);
extern void* fn_80201814(void*);
extern void* fn_80201C24(void*);
extern u32 fn_80157894(void*);
extern void fn_80027B78(u32, void*);
extern void fn_801D1318(u32);
extern void fn_801B05B0(int, u32);
extern void fn_801A9E40(int);
extern void fn_801D0E78(void*);
extern void fn_800A0B68(u32);

/*
 * Object update callback.  The retail routine continues through the object's
 * complete event/state dispatch after this recovered opening and teardown
 * phase.
 */
void fn_801CEF74(Object* object)
{
    Object* owner = *(Object**)(object->bytes + 0x284);
    int local_gate = 0;
    int* gate = &local_gate;
    u8 flags = object->bytes[0xFF0];

    if (flags & 0x10) {
        gate = &lbl_8064D550;
    }

    if (*gate == 0 && *(int*)(object->bytes + 8) == lbl_8064D18C &&
        !(owner->bytes[0xFF0] & 1) && !(flags & 1)) {
        /* The unreconstructed event/state dispatcher starts here. */
        return;
    }

    if (*(u16*)(object->bytes + 0xFF4) != 0) {
        if (*(u16*)(object->bytes + 0xFF4) > 10) {
            void* effect = *(void**)(owner->bytes + 0x30);
            if (effect != 0) {
                void* data = fn_80201B54(effect);
                fn_8020123C(0x39, data, data, 0);
            }
            if (*(u16*)(object->bytes + 0xFF4) > 20) {
                fn_801FDF3C(*(void**)(owner->bytes + 0x44), 0);
                fn_801FDF00(*(void**)(owner->bytes + 0x44), 0);
                fn_801FDFEC(*(void**)(owner->bytes + 0x44), 0);
                fn_801FE024(*(void**)(owner->bytes + 0x44), 60);
            }

            if (*(u16*)(object->bytes + 0xFF4) >= 30) {
                u8* work = object->bytes + 0xBC;
                int i;

                for (i = 0; i < *(s16*)(work + 8); i++) {
                    void* item = *(void**)(work + 0x14 + i * 4);
                    if (item != 0) {
                        fn_802006D4(item, item, -1, 0x39, 0);
                        fn_8020123C(0x39, item, item, 0);
                    }
                }

                if (*(u16*)(object->bytes + 0xFF4) > 30) {
                    for (i = 0; i < *(s16*)(work + 8); i++) {
                        void* item = *(void**)(work + 0x1AC + i * 4);
                        if (item != 0) {
                            fn_8019B134(item, 0);
                        }
                    }

                    if (*(int*)(object->bytes + 8) == lbl_8064D18C &&
                        (object->bytes[0xFF0] & 8)) {
                        fn_801D313C(*(u32*)(owner->bytes + 4),
                                    *(u32*)(object->bytes + 0xC),
                                    owner->bytes + 0x38);
                    }
                }
            }
        }
    }

    if ((*(int*)(owner->bytes + 4) & 0x1FF0) == 0x300) {
        void* resource = *(void**)(owner->bytes + 0xBC);
        void* data = fn_80201C24(fn_80201814(resource));
        if (fn_80157894(data) & 1) {
            fn_80027B78(*(u32*)(object->bytes + 0xC), resource);
        }
        lbl_8064D548 = 0;
    }

    if ((*(u16*)(object->bytes + 0xFF4) <= 30 ||
         !(object->bytes[0xFF0] & 8)) &&
        (object->bytes[0xFF0] & 0x10)) {
        fn_801D1318(0);
    }

    *gate = 0;
    fn_8020123C(0xB0, *(void**)(object->bytes + 0xC),
                *(void**)(object->bytes + 0xC), 0);

    if (*(int*)(owner->bytes + 0x10) != -1) {
        fn_801B05B0(*(int*)(owner->bytes + 0x10), 10);
    }

    fn_801A9E40(-1);
    fn_801D0E78(owner);
    fn_801D0E78(object);
    fn_800A0B68(0);
}
