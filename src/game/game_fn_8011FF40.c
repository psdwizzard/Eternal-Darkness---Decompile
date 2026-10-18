typedef unsigned char u8;

typedef struct ResourcePart {
    unsigned size;
    unsigned pad04;
    unsigned index;
    unsigned pad0C;
} ResourcePart;

typedef struct ResourceList {
    u8* data;
    unsigned pad04;
    ResourcePart* parts;
    unsigned pad0C;
    int count;
} ResourceList;

typedef struct Color3 {
    u8 red;
    u8 green;
    u8 blue;
} Color3;

typedef struct Color4 {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} Color4;

extern void fn_801ECF50(int mode);
extern ResourceList* fn_801222A0(void* object, void* name, int mode, int value);
extern void fn_80122428(void* object, ResourceList* list, void* name, int mode,
                       int value);
extern void fn_801EDA7C(void* destination, void* manager, int type, int value);
extern int fn_8011FAF4(void* object);
extern void fn_801ECD74(Color4 color);
extern void GXCallDisplayList(void* data, void* part);
extern void* lbl_8064D790;
extern volatile u8 lbl_8064CEB4[3];
extern volatile u8 lbl_8064CEB8[3];

void fn_8011FF40(void* object, unsigned flags, void* name, int alpha,
                 void* color_object)
{
    int mode = (flags & 0x00400000) != 0 ? 1 : 7;
    ResourceList* list;
    ResourcePart* part;
    u8* data;
    int i;

    fn_801ECF50(mode);
    list = fn_801222A0(object, name, mode, 1);
    if (list->data == 0) {
        fn_80122428(object, list, name, mode, 1);
    }

    part = list->parts;
    data = list->data;
    for (i = 0; i < list->count; part++, i++) {
        if (part->size != 0) {
            unsigned offset = part->index * 0x20;
            fn_801EDA7C(*(u8**)((u8*)object + 0x60) + offset,
                        lbl_8064D790, 0x8ABF, 0);
            if (alpha != 0) {
                Color4 color;
                if (fn_8011FAF4(color_object) & 1) {
                    color.red = lbl_8064CEB4[0];
                    color.green = lbl_8064CEB4[1];
                    color.blue = lbl_8064CEB4[2];
                } else {
                    color.red = lbl_8064CEB8[0];
                    color.green = lbl_8064CEB8[1];
                    color.blue = lbl_8064CEB8[2];
                }
                color.alpha = alpha;
                fn_801ECD74(color);
            }
            GXCallDisplayList(data, (void*)part->size);
        }
        data += part->size;
    }
}
