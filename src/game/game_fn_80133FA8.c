typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

typedef struct EffectRecord {
    u32 pad00;
    void* object;
    s32 type;
} EffectRecord;

typedef struct TransitionEffectState {
    u8 pad000[0x1B8];
    u8 values[12];
    u32 flags;
    u8 pad1C8[0x18];
    s8 mode;
} TransitionEffectState;

extern TransitionEffectState lbl_8030F540;
extern void* lbl_8064CF5C;

extern void* fn_80156938(void*);
extern void* fn_8017FDE4(void*);
extern void* fn_801938A8(void*);
extern void* fn_801D5898(Vec3f*, Vec3f*, int, int, int, u8, u8, u8, u8, u8,
                         int, u8, u8, u8, u8, u32, u32);
extern u32 fn_80193860(void*);
extern void fn_801938D8(void*, u32);
extern void fn_801938E0(void*, s8);
extern void fn_801938D0(void*, u8);

void fn_80133FA8(Vec3s* pos, EffectRecord* record)
{
    Vec3f first_float;
    Vec3f second_float;
    Vec3s* first_pos;
    Vec3s* second_pos;
    int mode;

    if ((s8)lbl_8030F540.values[3] == 0) {
        return;
    }

    if (record->object == 0) {
        first_float.x = pos[0].x;
        first_float.y = pos[0].y;
        first_float.z = pos[0].z;
        second_float.x = pos[1].x;
        second_float.y = pos[1].y;
        second_float.z = pos[1].z;

        switch (record->type) {
        case 0x23:
            mode = 1;
            break;
        case 0x24:
            mode = 2;
            break;
        case 0x25:
            mode = 3;
            break;
        case 0x26:
            mode = 4;
            break;
        case 0x2B:
            mode = 0;
            break;
        case 0x28:
            if (lbl_8030F540.mode != 0) {
                mode = lbl_8030F540.mode;
            }
            break;
        }

        record->object = fn_801D5898(
            &first_float, &second_float, mode,
            lbl_8030F540.values[0], lbl_8030F540.values[1],
            lbl_8030F540.values[2], lbl_8030F540.values[3],
            lbl_8030F540.values[4], lbl_8030F540.values[5],
            lbl_8030F540.values[6], lbl_8030F540.values[7],
            lbl_8030F540.values[8], lbl_8030F540.values[9],
            lbl_8030F540.values[10], 0x84,
            lbl_8030F540.flags | 8, 0);
        if (record->object != 0) {
            lbl_8064CF5C = fn_80156938(record->object);
            fn_801938D8(lbl_8064CF5C, fn_80193860(lbl_8064CF5C) | 0x848);
            fn_801938E0(lbl_8064CF5C, 1);
            fn_801938D0(lbl_8064CF5C, lbl_8030F540.values[11]);
        }
    } else {
        lbl_8064CF5C = fn_80156938(record->object);
        first_pos = fn_8017FDE4(lbl_8064CF5C);
        second_pos = fn_801938A8(lbl_8064CF5C);
        first_pos->x = pos[0].x;
        first_pos->y = pos[0].y;
        first_pos->z = pos[0].z;
        second_pos->x = pos[1].x;
        second_pos->y = pos[1].y;
        second_pos->z = pos[1].z;
    }
}
