typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Item {
    u8 pad0[0xA];
    s16 index;
    u8 padC[0x13];
    u8 kind;
} Item;

typedef struct Child {
    u8 pad0[8];
    u16 flags;
    u8 padA[0x25];
    u8 kind;
} Child;

typedef struct ObjectSlot {
    Child* child;
    u32 pad4;
} ObjectSlot;

typedef struct Object {
    u8 pad0[0x17C];
    ObjectSlot slots[1];
} Object;

extern float fn_801ECD58(void);
extern float lbl_806500A4;

int fn_80122538(Object* object, Item* item, int object_index)
{
    Child* child;

    if (item->index != -1 || item->kind != 0xFF) {
        return 1;
    }
    if (lbl_806500A4 != fn_801ECD58()) {
        return 1;
    }

    child = object->slots[object_index].child;
    if (child != 0 && (child->flags & 4) && child->kind != 0xFF) {
        return 1;
    }
    return 0;
}
