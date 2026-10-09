typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct BufferOwner {
    unsigned char pad0[8];
    u16 type;
    unsigned char padA[0x14];
    u16 count;
} BufferOwner;

typedef struct Object {
    unsigned char pad0[0x3C];
    BufferOwner* owner;
} Object;

extern s32 lbl_8064CEBC[2];
extern s32 lbl_8064CF20;
extern s32 lbl_8064CF24;
extern s32 lbl_8064D738;

int fn_801207F0(Object* object)
{
    BufferOwner* owner = object->owner;
    s32 result = 0;
    s32 size = owner->count + owner->count;
    size = (size + 31) & ~31;

    if (owner->type <= 3) {
        if (lbl_8064CF24 + lbl_8064CF20 > 0x42) {
            return 0;
        }
    } else if (lbl_8064CF24 > 0x12) {
        return 0;
    }

    if (size + lbl_8064CEBC[lbl_8064D738 ^ 1] < 0x9C40) {
        result = 1;
    }
    return result;
}
