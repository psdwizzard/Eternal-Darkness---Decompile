typedef unsigned int u32;

extern void *fn_80201BC8(void *object);
extern int fn_80201B54(void *object);
extern int fn_80201EB8(void *object);
extern int fn_800CA2C8(void *object);
extern int fn_801E8328(u32 kind, u32 value);
extern unsigned char *fn_801294DC(void *owner, int kind, int flags, int mode);
extern int fn_8012A1FC(void *owner, int kind);
extern int fn_8012A1BC(void *owner, int kind);
extern int fn_800389E0(void *object, int channel, short value, int propagate);
extern void fn_801287C4(void *queue, void *callback, u32 value, u32 kind);
extern void fn_80128A84(void *queue, unsigned short value, u32 kind);
extern void fn_80128C44(void *runtime, u32 callback, u32 value);
extern int fn_80204810(void *object, int event);
extern void fn_80201D2C(void *object, int value);
extern void fn_80201D14(void *object, int value);
extern void fn_80201138(int kind, void *context, int value, int id, int arg4,
                       float delay);
extern int lbl_8064D18C;

void fn_800CD094(void *object, void *event, int requested)
{
    void *queue;
    void *owner = fn_80201BC8(object);
    int id = fn_80201B54(object);
    int group = fn_80201EB8(object);

    if (group != lbl_8064D18C) {
        fn_800CA2C8(object);
        fn_801E8328(2, (u32)object);
    } else {
        queue = fn_801294DC(owner, 0x18, 0x20, 10);
        if (queue != 0) {
            int start = fn_8012A1FC(owner, 0x18);
            int end = fn_8012A1BC(owner, 0x18);
            int duration;
            int packed;

            if (requested == -1) {
                duration = end - start;
                if (duration < 0) {
                    duration = -duration;
                }
            } else {
                duration = requested;
            }
            fn_800389E0(object, 0, 0, 1);
            packed = id << 8;
            fn_801287C4(queue, fn_80204810, packed | 0xF9, end - 1);
            fn_80128A84(queue, 0, end);
            fn_80128C44(queue, (u32)fn_80204810, packed | 7);
            fn_80201D2C(object, 8);
            fn_80201D14(object, 1);
            fn_80201138(0x11, object, 8, -1, 0, (float)duration);
        }
    }
}
