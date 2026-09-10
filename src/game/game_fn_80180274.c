typedef unsigned char u8;

typedef struct Object {
    u8 pad_00[3];
    u8 active;
    u8 pad_04[2];
    u8 count;
    u8 flags;
    u8 pad_08[0x2C];
    void* handle;
    void* source;
    u8 pad_3C[0x10];
    void* entries;
    void* secondary;
    void* fourth;
    void* third;
    void* default_value;
} Object;

typedef struct DefaultConfig {
    u8 pad_00[0xC];
    void* value;
} DefaultConfig;

extern DefaultConfig lbl_802FC5BC;
extern void* lbl_8064D18C;

extern void* fn_801801D4(void*);
extern void* fn_80180214(void*);
extern void* fn_80180234(void*);
extern void* fn_80180254(void*);
extern void fn_8017FD34(void*);
extern void* fn_8018094C(void);

int fn_80180274(Object* object, void** config)
{
    int result;

    object->entries = fn_80180214(config[0]);
    object->secondary = fn_80180254(config[1]);
    object->third = fn_801801D4(config[2]);
    object->fourth = fn_80180234(config[3]);
    object->default_value = lbl_802FC5BC.value;
    object->active = 1;
    object->source = lbl_8064D18C;
    object->count = 10;
    object->flags = 0x80;
    result = object->entries != 0 && object->secondary != 0 && object->third != 0 && object->fourth != 0;

    if (result == 0) {
        fn_8017FD34(object);
        object->entries = 0;
        object->secondary = 0;
        object->third = 0;
        object->fourth = 0;
    } else {
        object->handle = fn_8018094C();
    }
    return result;
}
