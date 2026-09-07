typedef unsigned char u8;
typedef unsigned int u32;
typedef signed short s16;

typedef struct EffectOutputs {
    s16 short_value;
    u8 pad[2];
    u32 copied_word;
    u32 word_value;
} EffectOutputs;

extern void fn_801E0088(void);
extern void fn_801D0CA4(void);
extern void* fn_801D0D78();
extern int fn_801D38E8(int);
extern void fn_801D38BC(int, u32*, s16*);
extern int fn_801CEB2C(int);
extern void fn_801CE594();

void* fn_801DE4A8(int handle, int input_flags, void* input_source, int input_tag,
                  void* callback, int arg6, int arg7, int arg8, int arg9)
{
    int saved_flags = input_flags;
    void* result;
    int saved_tag = input_tag;
    void* saved_source = input_source;
    s16 short_value;
    u32 word_value;
    u32 copied_word;

    result = fn_801D0D78(handle, saved_flags, saved_source, saved_tag,
                         fn_801E0088, arg6, arg7, arg8, arg9, callback);
    *(int*)((u8*)result + 0xbc) = 0;
    *(int*)((u8*)result + 0xc4) = 0;
    *(int*)((u8*)result + 0xd0) = 0;
    *(s16*)((u8*)result + 0xdc) = 300;
    *(int*)((u8*)result + 0xc8) = 1;
    *(int*)((u8*)result + 0x138) = 0;
    *((u8*)result + 0xd8) = 1;
    *(int*)((u8*)result + 0xcc) = 0;
    *(int*)((u8*)result + 0x13c) = 0;
    *(int*)((u8*)result + 0xc0) = 0;
    fn_801D38BC(fn_801D38E8(saved_flags), &word_value, &short_value);
    copied_word = word_value;
    fn_801CE594(saved_flags, saved_source, saved_tag, fn_801CEB2C(saved_flags),
                250, short_value, 240, 40, saved_tag, 250, 0, 600,
                fn_801D0CA4, result, &copied_word);
    return result;
}
