typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct SpawnInfo {
    Vec3 position;
    float scale;
    int kind;
    int field14;
    int pad18;
    int field1c;
    int field20;
    int field24;
    int field28;
} SpawnInfo;
typedef struct EffectOutputs {
    s16 short_value;
    u8 pad[2];
    u32 copied_word;
    u32 word_value;
} EffectOutputs;
typedef union EffectScratch {
    volatile u32 initial_flags;
    EffectOutputs outputs;
} EffectScratch;

extern int* lbl_8064C5A8;
extern u8 lbl_802555A0[];
extern void fn_801E0088(void);
extern void fn_801D0C9C(void);
extern void fn_801D0CA4(void);
extern void* fn_80201814(int);
extern void fn_80201E78(Vec3*, void*);
extern void* fn_80201AE4(void);
extern void fn_801A9E40(int);
extern int fn_801B05E8();
extern void* fn_801D0D78();
extern void fn_801D1318(u32);
extern int fn_8015ABD4(int, int);
extern int fn_80054BCC(int);
extern int fn_801D38E8(u32);
extern void fn_801D38BC(int, u32*, s16*);
extern int fn_801CEB2C(u32);
extern void fn_801CE594();
extern void fn_801B08BC(int, int, int);

void* fn_801DD200(int object_id, SpawnInfo* info, int arg2, int arg3,
                  int use_position, u16 arg6, int arg7)
{
    u32 flags;
    void* result;
    int low_index;
    int high_index;
    int type;
    Vec3 copied_position;
    Vec3 position;
    int handle;
    int owner;
    EffectScratch scratch;

    scratch.initial_flags = 0x820;
    flags = scratch.initial_flags;
    result = 0;
    low_index = 0;
    high_index = 0;
    type = info->field14;

    switch (type) {
    case 1: case 2: case 3: case 4: case 28:
        flags |= (low_index = 0, 1); break;
    case 6: case 16: case 29: case 79: case 128:
        flags |= (low_index = 1, 2); break;
    case 7: case 15: case 30: case 80: case 93:
        flags |= (low_index = 2, 4); break;
    case 8:
        flags |= (low_index = 3, 8); break;
    case 10:
        switch (*lbl_8064C5A8) {
        case 1: flags |= (low_index = 0, 1); break;
        case 2: flags |= (low_index = 1, 2); break;
        case 3: flags |= (low_index = 2, 4); break;
        }
        break;
    case 126:
        switch (*lbl_8064C5A8) {
        case 1: flags |= (low_index = 0, 1); break;
        case 2: flags |= (low_index = 1, 2); break;
        case 3: flags |= (low_index = 2, 4); break;
        }
        break;
    }

    switch (type) {
    case 3: case 4: case 28: case 29: case 30: case 79: case 80: case 93:
        flags |= 1 << 16; high_index = 0; break;
    case 1: case 6: case 7: case 8: case 128:
        flags |= 2 << 16; high_index = 1; break;
    case 2: case 15: case 16:
        flags |= 4 << 16; high_index = 2; break;
    case 10:
        flags |= 8 << 16; break;
    case 126:
        flags |= 2 << 16; high_index = 1; break;
    }

    {
        void* object = fn_80201814(object_id);
        if (object != 0) {
            fn_80201E78(&position, object);
            copied_position = position;
            owner = *(int*)(lbl_802555A0 + low_index * 12 + high_index * 4 + 0x150);
            handle = -1;
            if (owner > 0) {
                int is_other = object_id != (int)fn_80201AE4();
                fn_801A9E40(1);
                handle = fn_801B05E8(owner, 127, 4, 1, &copied_position, 6,
                                     is_other, 1);
            }
            result = fn_801D0D78(handle, flags, object_id, &copied_position,
                                 fn_801E0088, fn_801D0C9C, 0, arg2, arg3, 0);
            if (result != 0) {
                u8* p = result;
                if ((p[0xff0] & 0x10) != 0)
                    fn_801D1318(flags);
                *(int*)(p + 0xc8) = 0;
                *(int*)(p + 0xc0) = 1;
                *(int*)(p + 0xc4) = use_position;
                *(int*)(p + 0xcc) = 0;
                *(int*)(p + 0xbc) = 0;
                if (arg7 != 0 && fn_8015ABD4(2, 2) == 0 &&
                    fn_80054BCC(*(int*)(p + 8)) != 0) {
                    *(int*)(p + 0xc8) = 1;
                    *(int*)(p + 0xcc) = 1;
                    *(int*)(p + 0xbc) = 1;
                }
                if (use_position != 0)
                    *(Vec3*)(p + 0x108) = info->position;
                else
                    *(u16*)(p + 0xdc) = arg6;
                p[0xd8] = 1;
                *(int*)(p + 0xd0) = 0;
                *(float*)(p + 0x104) = info->scale;
                *(int*)(p + 0xe4) = info->kind;
                *(int*)(p + 0xe8) = info->field14;
                *(int*)(p + 0xec) = info->field1c;
                *(int*)(p + 0xf0) = info->field20;
                *(int*)(p + 0xf4) = info->field24;
                *(int*)(p + 0x138) = info->field28;
                *(int*)(p + 0x13c) = 0;
                fn_801D38BC(fn_801D38E8(flags), &scratch.outputs.word_value,
                             &scratch.outputs.short_value);
                scratch.outputs.copied_word = scratch.outputs.word_value;
                owner = fn_801CEB2C(flags);
                fn_801CE594(flags, object_id, &copied_position, owner, 250,
                            scratch.outputs.short_value, 240, 40, &copied_position,
                            250, 0, 600, fn_801D0CA4, result,
                            &scratch.outputs.copied_word);
            } else {
                fn_801A9E40(-1);
                fn_801B08BC(handle, -2, 0);
            }
        }
    }
    return result;
}
