typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    u32 x;
    u32 y;
    u32 z;
} Vec3;

typedef struct Object {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0C;
    u32 field_10;
    char pad14[8];
    u32 field_1C;
    u32 field_20;
    u32 field_24;
    u32 field_28;
    u32 field_2C;
    u32 field_30;
    u32 field_34;
    Vec3 position;
    char pad44[0xFAC];
    u8 flags;
    u8 state;
    u8 active;
    u8 padFF3;
    u16 field_FF4;
} Object;

extern void* lbl_8064D554;
extern u32 lbl_8064D18C;
extern Object* fn_8017CDB4(void*);
extern int fn_80201AE4(void);

Object* fn_801D0D78(u32 arg0, u32 arg1, int arg2, Vec3* position,
                    u32 arg4, u32 arg5, u32 arg6, u32 arg7, u32 arg8,
                    int arg9)
{
    Object* object = fn_8017CDB4(lbl_8064D554);

    if (object != 0) {
        object->field_1C = arg4;
        object->field_20 = arg5;
        object->field_24 = arg6;
        object->field_28 = arg7;
        object->field_2C = arg8;
        object->field_04 = arg1;
        object->field_0C = arg2;
        object->field_10 = arg0;
        object->field_FF4 = 0;
        object->field_00 = 0;
        if (position != 0) {
            object->position = *position;
        }
        object->active = 1;
        object->flags = 8;
        if (arg9 != 0) {
            object->flags |= 4;
        }
        if (arg2 == fn_80201AE4()) {
            object->flags |= 0x10;
        }
        object->field_08 = lbl_8064D18C;
        object->field_30 = 0;
        object->field_34 = 0;
        object->state = 0;
    }
    return object;
}
