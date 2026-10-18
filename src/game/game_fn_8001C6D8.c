typedef unsigned int u32;
typedef int s32;

typedef struct Command {
    u32 words[8];
} Command;

extern double lua_tonumber(void*, int);
extern s32 fn_802019EC(s32, void*);
extern void *fn_80201814();
extern void fn_80201ADC(void);
extern void* fn_80201C2C(void);
extern int fn_80201B5C(void*);
#define fn_80201B5C(a) fn_80201B5C((void*)(a))

extern int fn_80201B64(void*);
extern void* fn_80204A94(void*, void*);
extern void* lbl_8064D18C;
extern Command lbl_803023E0;

void fn_8001C6D8(void* arg)
{
    void* saved_arg = arg;
    void* item;
    void* context;
    s32 state;

    lbl_803023E0.words[7] = fn_802019EC((s32)lua_tonumber(saved_arg, 5), lbl_8064D18C);
    if ((s32)lbl_803023E0.words[7] > 0) {
        item = fn_80201814(lbl_803023E0.words[7]);
        if (item != 0) {
            fn_80201ADC();
            context = fn_80201C2C();
            if ((fn_80201B5C(item) == 30 && fn_80201B64(item) == 36) ||
                (context != 0 && fn_80204A94(context, item) != 0)) {
                state = 2;
                if (lbl_803023E0.words[6] & 2) {
                    state = 1;
                }
                lbl_803023E0.words[0] = state;
                lbl_803023E0.words[4] = (s32)lua_tonumber(saved_arg, 6);
                lbl_803023E0.words[7] = 0;
            }
        }
    } else {
        state = 2;
        if (lbl_803023E0.words[6] & 2) {
            state = 1;
        }
        lbl_803023E0.words[0] = state;
        lbl_803023E0.words[4] = (s32)lua_tonumber(saved_arg, 6);
    }
}
