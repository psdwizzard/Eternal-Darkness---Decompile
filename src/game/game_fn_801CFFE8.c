typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef struct DispatchData {
    s32 value;
    u8 enabled;
    u8 reserved[7];
} DispatchData;

extern void fn_801D0794(u32, u32, s32, DispatchData*, void*, u32, void*, u32);
extern void fn_801D0C94(void);
extern void fn_801D0C9C(void);

void fn_801CFFE8(s32 subject, u32 flags_a, u32 flags_b, s32 value)
{
    if (subject > 0 && value > 0) {
        DispatchData data;
        data.value = value;
        data.enabled = 1;
        fn_801D0794((flags_a | 0x1010) | flags_b, 0, subject, &data,
                    fn_801D0C9C, 0, fn_801D0C94, 0);
    }
}
