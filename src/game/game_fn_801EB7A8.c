typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#pragma use_lmw_stmw on

typedef struct Entry { void* display_list; void* object; } Entry;
typedef struct PatchState { u32 unknown; void* data; u32 stream; u8 pad[8]; } PatchState;
typedef struct Object { u8 pad[8]; void* stream; u8 rest[8]; } Object;
typedef struct Scene { u8 pad[0x4C]; int count; Object* objects; } Scene;
typedef struct Resource { u8 pad[2]; short mode0; u8 pad2[8]; short mode1; u8 pad3[2]; short mode2; } Resource;

extern int lbl_8064D618;
extern int lbl_8064D654;
extern void* lbl_8064D5FC;
extern Entry lbl_80639260[];
extern void fn_8015DB84(void*, void*, short);
extern void fn_801EB340(void*, void*);
extern void fn_801EB5C8(void*, void*, int);
extern void fn_80228D9C(void);

void fn_801EB7A8(Scene* scene, int mode)
{
    register Entry* entry;
    int i;
    void* display_list;
    Object* object;
    Resource* resource;
    int value;
    int count;

    if (lbl_8064D618 == mode)
        return;

    for (entry = lbl_80639260, i = 0; i < lbl_8064D654; entry++, i++) {
        display_list = entry->display_list;
        resource = entry->object;
        value = -1;
        switch (mode) {
        case 0: value = resource->mode0; break;
        case 1: value = resource->mode1; break;
        case 2: value = resource->mode2; break;
        }
        if ((short)value != -1) {
            u32 data[8];
            fn_8015DB84(lbl_8064D5FC, data, (short)value);
            fn_801EB340(display_list, data);
        }
    }

    object = scene->objects;
    i = 0;
    count = scene->count;
    for (; i < count; object++, i++) {
        if (object->stream != 0)
            fn_801EB5C8(object, object->stream, mode);
    }
    lbl_8064D618 = mode;
    fn_80228D9C();
}
