typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Work {
    u8 pad0[0xC];
    int owner;
    u8 pad10[0xAC];
    void* value;
    u8 padC0[4];
    u8 flags;
    u8 padC5[3];
    void* control;
    u8 padCC[0xC0];
    void* effect;
    u8 pad190[0xC0];
    u8* samples;
    u8 pad254[0xD9C];
    u8 status;
} Work;

extern int lbl_8064D18C;
extern void* fn_80201814(int);
extern int fn_80201B64(void*);
extern void fn_8020123C(int, void*, void*, void*);
extern u32 fn_801A39A8(void*);
extern void fn_801A39B8(void*);
extern void fn_801A39D4(void*, u8);
extern void fn_801D0E78(Work*);
extern int fn_80201EB8(void*);

void fn_801E3644(Work* work)
{
    void* owner = fn_80201814(work->owner);

    if (owner == 0 || fn_80201B64(owner) != 8) {
        fn_8020123C(57, work->value, work->value, 0);
    }

    if ((work->flags & 1) == 0) {
        if (work->effect != 0 && *(void**)((u8*)work->effect + 0x88) != 0) {
            void* effect = *(void**)((u8*)work->effect + 0x88);
            u8 flags = (u8)fn_801A39A8(effect);
            if (work->control != 0) {
                flags |= 4;
                fn_801A39B8(effect);
            } else {
                flags &= (u8)~1;
            }
            fn_801A39D4(effect, flags);
        }
        fn_801D0E78(work);
        return;
    }

    if (fn_80201EB8(owner) == lbl_8064D18C) {
        work->flags &= (u8)~4;
    } else {
        work->flags &= (u8)~2;
    }
}
