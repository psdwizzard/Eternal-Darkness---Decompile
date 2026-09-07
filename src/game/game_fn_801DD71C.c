typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct EffectOutputs {
    s16 short_value;
    u8 pad[2];
    u32 copied_word;
    u32 word_value;
} EffectOutputs;

extern u8 lbl_802555A0[];
extern void* fn_80201814(int);
extern int fn_80201B64(void*);
extern int fn_80035628(void*);
extern void* fn_80201AE4(void);
extern void fn_801A9E40(int);
extern int fn_801B05E8();
extern void* fn_801D0D78();
extern void fn_801DEEBC(void);
extern void fn_801D0C9C(void);
extern void* memcpy(void*, const void*, u32);
extern int fn_801D38E8(u32);
extern void fn_801D38BC(int, u32*, s16*);
extern int fn_801CEB2C(u32);
extern void fn_801D0CA4(void);
extern void fn_801CE594();
extern void fn_801B08BC(int, int, int);

void* fn_801DD71C(int object_id, int kind, void* source_a, int count,
                  void* source_b, void* source_c, int rows,
                  void (*callback)(void), u32 tag, s16 duration)
{
    void* result;
    u32 flags;
    int handle;
    int low_index;
    int high_index;
    int owner;
    int total;
    EffectOutputs outputs;

    result = 0;
    handle = (int)fn_80201814(object_id);
    if (handle != 0 && fn_80201B64((void*)handle) != 8) {
        flags = 0x820;
        switch (fn_80035628((void*)handle)) {
        case 1: flags |= 1; low_index = 0; break;
        case 2: flags |= 2; low_index = 1; break;
        case 3: flags |= 4; low_index = 2; break;
        default: flags |= 8; low_index = 3; break;
        }

        switch (kind) {
        case 5: flags |= 0x20000; high_index = 1; break;
        case 7: flags |= 0x40000; high_index = 2; break;
        default: flags |= 0x10000; high_index = 0; break;
        }

        owner = *(int*)(lbl_802555A0 + low_index * 12 + high_index * 4 + 0x150);
        if (owner > 0) {
            int is_other = object_id != (int)fn_80201AE4();
            fn_801A9E40(1);
            handle = fn_801B05E8(owner, 100, 4, 1, source_a, 6, is_other, 1);
        }

        result = fn_801D0D78(handle, flags, object_id, source_a,
                             fn_801DEEBC, fn_801D0C9C, 0, callback, tag, 0);
        if (result != 0) {
            u8* p = result;
            int n = (u8)count;
            *(int*)(p + 0xbc) = 0;
            *(int*)(p + 0xd0) = 1;
            *(int*)(p + 0xc8) = 0;
            *(int*)(p + 0xcc) = 0;
            *(int*)(p + 0xd4) = 1;
            *(s16*)(p + 0xdc) = duration;
            p[0xda] = rows;
            p[0xd9] = 0;
            p[0xd8] = count;
            *(int*)(p + 0xf4) = 0;
            *(int*)(p + 0xf0) = -1;
            memcpy(p + 0xf8, source_b, n * 4);
            memcpy(p + 0x114, source_c, n * 12);
            total = (u8)rows * n;
            fn_801D38BC(fn_801D38E8(flags), &outputs.word_value,
                         &outputs.short_value);
            outputs.copied_word = outputs.word_value;
            fn_801CE594(flags, object_id, source_a, fn_801CEB2C(flags),
                        (u16)(total + 250), outputs.short_value,
                        (u16)(total + 240), 40, source_a, 250, 0, 600,
                        fn_801D0CA4, result, &outputs.copied_word);
        } else {
            fn_801A9E40(-1);
            fn_801B08BC(handle, -2, 0);
        }
    }
    return result;
}
