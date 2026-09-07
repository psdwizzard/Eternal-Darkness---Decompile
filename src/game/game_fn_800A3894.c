typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec800A3894 { float x, y, z; } Vec800A3894;
typedef struct Object800A3894 {
    u8 pad0[0x160];
    void* active;
    u8 pad164[0x18];
    Vec800A3894 position;
    void* sound;
    u8 pad18C[0xD8];
    struct { u8 pad0[4]; u16 owner; }* data;
} Object800A3894;

extern u16 fn_801869DC(void*);
extern void fn_80211A6C();
extern void fn_80211AAC(Vec800A3894*, Vec800A3894*);
extern void fn_80211A90(Vec800A3894*, Vec800A3894*, float);
extern void fn_80211A48(void*, Vec800A3894*, Vec800A3894*);
extern void* fn_801AC8AC(u16, int, int, Vec800A3894*);
extern int fn_801AC908(void*, Vec800A3894*, int);

/*
 * Behavior-complete, size-equal reconstruction. Code differs only because the
 * implicit u16-to-float pool relocation is named @13 rather than retail's
 * lbl_8064EE98. Objdiff: 99.86207%, 232/232 bytes.
 */
void fn_800A3894(Object800A3894* object, void* arg1, void* arg2)
{
    Vec800A3894 direction;
    u16 distance;

    if (object->active != 0) {
        distance = fn_801869DC(object->active);
        fn_80211A6C(arg2, arg1, &direction);
        fn_80211AAC(&direction, &direction);
        fn_80211A90(&direction, &direction, distance);
        fn_80211A48(arg1, &direction, &object->position);
        if (object->sound == 0) {
            object->sound = fn_801AC8AC(object->data->owner, 127, 1200,
                                        &object->position);
        } else {
            fn_801AC908(object->sound, &object->position, 50);
        }
    }
}
