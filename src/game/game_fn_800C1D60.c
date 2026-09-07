typedef unsigned char u8;
typedef unsigned int u32;

extern u32 lbl_8064CA8C;

extern void *fn_801A7498(void *);
extern void *fn_80201814();
extern int fn_80201B54();
extern void *fn_80201B8C();
extern u32 fn_8003BD48(void *, void *);
extern u32 fn_80128EE4(void *);
extern int fn_80128F40(void *);
extern int fn_80128EAC(void *);
extern int fn_8012A1BC(void *, int);
extern void *fn_8011F130(void *);
extern void fn_80128B10(void *, int);
extern int fn_801AC9F4(int, int, void *, int);
extern u32 fn_801290D0(void *);
extern void fn_80128F74(void *, u32);
extern int fn_80050950(void);
extern int fn_80050B08(int, int, int, u8 *, int, int, int);
extern void fn_80204028(void *, int, int, int);
extern void fn_8012B344(void*);

#pragma use_lmw_stmw on

int fn_800C1D60(void *object, void *event)
{
    void *event_object;
    int handled = 0;
    void **state;
    u8 *runtime;
    u8 *obj = object;
    u32 mode;
    u32 flags;
    u32 result;
    int delta;

    event_object = fn_80201814(fn_801A7498(event));
    fn_80201B54(event_object);
    state = ((void **)fn_80201B8C(event_object));
    runtime = (u8 *)state[0];
    flags = fn_8003BD48(obj, event);
    mode = fn_80128EE4(obj);
    if ((flags & 3) != 0) {
        lbl_8064CA8C = flags;
    }

    if ((mode & 0x20) != 0) {
        int value = fn_80128F40(obj);
        delta = fn_8012A1BC(obj, fn_80128EAC(obj)) - (value >> 17);

        if ((flags & 0x20) != 0) {
            void *owner = fn_8011F130(obj);
            if ((flags & 8) != 0) {
                fn_80128B10(obj, 20);
            } else {
                fn_80128B10(obj, 7);
                fn_801AC9F4(41, 100, owner, 2);
            }
            result = fn_801290D0(obj);
            fn_80128F74(obj, result | 0x200);
            handled = 1;
        } else if ((flags & 0x10) != 0) {
            u8 sound;
            void *owner = fn_8011F130(obj);
            fn_801AC9F4(fn_80050B08(-2, fn_80050950(), 28, &sound, 0, 0, 0),
                         (int)sound, owner, 2);
            fn_80204028(event_object, 10000, 0, 0);
            fn_80128B10(obj, 4);
            result = fn_801290D0(obj);
            fn_80128F74(obj, result | 0x200);
            handled = 1;
        } else if ((flags & 0x40) != 0) {
            void *owner = fn_8011F130(obj);
            handled = 1;
            fn_801AC9F4(714, 100, owner, 2);
            fn_8012B344(obj);
        }
    }

    if (handled != 0 && delta > 0) {
        int amount = delta < 10 ? delta : 10;
        runtime[0x94] = (u8)(amount * 2);
    }
    return 1;
}
