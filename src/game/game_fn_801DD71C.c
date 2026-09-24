typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

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
extern void fn_801CE594(int, int, void*, int, int, s16, u16, int, void*, u16, int, int, void (*)(void), int, u32*);
extern void fn_801B08BC(int, int, int);

void* fn_801DD71C(int object_id, int kind, void* source_a, u8 count,
                  void* source_b, void* source_c, u8 rows,
                  void (*callback)(void), u32 tag, s16 duration)
{
    int flags;
    int result;
    int handle;
    int low_index;
    int high_index;
    void* object;
    int total;
    u32 word_value;
    u32 copied_word;
    s16 short_value;

    result = 0;
    object = fn_80201814(object_id);
    if (object != 0 && fn_80201B64(object) != 8) {
        flags = 0x820;
        low_index = (int)object;
        handle = -1;
        switch (fn_80035628((void*)low_index)) {
        case 1: flags |= 1; low_index = 0; break;
        case 2: flags |= 2; low_index = 1; break;
        case 3: flags |= 4; low_index = 2; break;
        case 4:
        default: flags |= 8; low_index = 3; break;
        }

        switch (kind) {
        case 5: flags |= 0x20000; high_index = 1; break;
        case 7: flags |= 0x40000; high_index = 2; break;
        case 3:
        default: flags |= 0x10000; high_index = 0; break;
        }

        result = ((int (*)[3])(lbl_802555A0 + 0x150))[low_index][high_index];
        if (result > 0) {
            int is_other = object_id != (int)fn_80201AE4();
            fn_801A9E40(1);
            handle = fn_801B05E8(result, 100, 4, 1, source_a, 6, is_other, 1);
        }

        result = (int)fn_801D0D78(handle, flags, object_id, source_a,
                             fn_801DEEBC, fn_801D0C9C, 0, callback, tag, 0);
        if (result != 0) {
            u8* p = (u8*)result;
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
            memcpy(p + 0xf8, source_b, (u8)count * 4);
            memcpy(p + 0x114, source_c, (u8)count * 12);
            total = (u8)rows;
            total *= (u8)count;
            fn_801D38BC(fn_801D38E8(flags), &word_value,
                         &short_value);
            copied_word = word_value;
            fn_801CE594(flags, object_id, source_a, fn_801CEB2C(flags),
                        250, short_value,
                        (u16)(total + 240), 40, source_a, (u16)(total + 250), 0, 600,
                        fn_801D0CA4, result, &copied_word);
        } else {
            fn_801A9E40(-1);
            fn_801B08BC(handle, -2, 0);
        }
    }
    return (void*)result;
}
