typedef unsigned char u8;
typedef signed short s16;
typedef int s32;
typedef unsigned int u32;

typedef struct KindInfo {
    u8 pad0[0x9F];
    u8 kind;
} KindInfo;

extern s16 lbl_8023BA30[5][5];
extern void* fn_80201814(s32);
extern s32 fn_801D38E8(u32);
extern s32 fn_80035628(void*);
extern KindInfo* fn_80201B8C(void*);

u32 fn_801E2E1C(u32 flags, s32 id)
{
    void* object;
    u32 result = 0;
    object = fn_80201814(id);

    if (object != 0) {
        s32 first = fn_801D38E8(flags);
        s32 second = fn_80035628(object);

        if (first == 4 || second == 4 || lbl_8023BA30[first][second] == 1) {
            KindInfo* info = fn_80201B8C(object);
            if (info != 0) {
                switch (info->kind) {
                case 6:
                    result = 1;
                    break;
                case 3:
                    result = flags & 0x60000;
                    break;
                case 4:
                    result = flags & 0x40000;
                    break;
                }
            }
        }
    }
    return result;
}
