typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct Object {
    u8 pad_00[0x94];
    s32 subtype;
    u8 pad_98[7];
    u8 type;
} Object;

extern u32 lbl_8064CCF4;

u32 fn_800361F8(Object* object)
{
    u32 result = 0;

    switch ((u32)object->type) {
    case 12:
        switch (object->subtype) {
        case 1:
            result = lbl_8064CCF4 & 0x800;
            break;
        case 2:
            result = lbl_8064CCF4 & 0x2000;
            break;
        case 3:
            result = lbl_8064CCF4 & 0x1000;
            break;
        }
        break;
    case 3:
        switch (object->subtype) {
        case 1:
            result = lbl_8064CCF4 & 2;
            break;
        case 2:
            result = lbl_8064CCF4 & 8;
            break;
        case 3:
            result = lbl_8064CCF4 & 4;
            break;
        case 4:
            result = lbl_8064CCF4 & 1;
            break;
        }
        break;
    case 4:
        switch (object->subtype) {
        case 1:
            result = lbl_8064CCF4 & 0x100;
            break;
        case 2:
            result = lbl_8064CCF4 & 0x400;
            break;
        case 3:
            result = lbl_8064CCF4 & 0x200;
            break;
        }
        break;
    case 5:
        switch (object->subtype) {
        case 1:
            result = lbl_8064CCF4 & 0x20;
            break;
        case 2:
            result = lbl_8064CCF4 & 0x80;
            break;
        case 3:
            result = lbl_8064CCF4 & 0x40;
            break;
        }
        break;
    case 6:
        result = lbl_8064CCF4 & 0x10;
        break;
    case 7:
        break;
    }

    return result;
}
