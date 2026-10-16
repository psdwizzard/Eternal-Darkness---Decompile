typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

extern s32 fn_80201B44(void);
extern void *fn_80201814(s32);
extern s32 fn_80049220(void *, s32);
extern s32 fn_80049304(void *, s32);
extern void *fn_80201C24(void *);
extern u8 fn_80157AB8(void *);
extern s32 fn_8006749C(s32);
extern void fn_80120AD0(void *, const void *, u16, u32, float, float);
extern void fn_8020104C(s32, s32, s32, s32, float);

extern float lbl_8064E26C;
extern float lbl_8064E270;
extern float lbl_8064E274;
extern float lbl_8064E278;

void fn_8003C114(s32 unused, void *object, s32 id)
{
    void *current;
    s32 mode;
    void *found;
    s32 state;
    u32 flags;

    current = fn_80201814(fn_80201B44());
    mode = fn_80049220(current, 1);
    found = (void *)fn_80049304(current, mode);
    if (found != 0) {
        state = fn_80157AB8(fn_80201C24(found));
        switch (state) {
        case 1:
        case 2:
        case 3:
        case 4:
            flags = fn_8006749C(state);
            fn_80120AD0(object, 0, 100, (flags | 2) & 0xFFFF,
                         lbl_8064E26C, lbl_8064E270);
            fn_8020104C(0x11, id, id, 0, lbl_8064E274);
            return;
        default:
            fn_8020104C(0x11, id, id, 0, lbl_8064E278);
            return;
        }
    }
    fn_8020104C(0x11, id, id, 0, lbl_8064E278);
}
