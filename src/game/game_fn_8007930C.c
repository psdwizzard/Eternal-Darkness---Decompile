typedef struct Vec3 { float x, y, z; } Vec3;
typedef unsigned char u8;

extern void *fn_80201B8C();
extern void* fn_80201B94();
extern void fn_8011F114();
extern u8 fn_80128EE4(void *object);
extern int fn_80201C48(int value);
extern int fn_80201B54();
extern int fn_80079008(void *context, void *object);
extern void *fn_801294DC(void *, int, int, int);
extern void *fn_801A717C(void);
extern int fn_80072354(int value);
extern void fn_801A7460(void *, int);
extern void fn_801A74A0(void *, int);
extern void fn_801A74A8(void *, int);
extern void fn_801A74C8(void *, int);
extern void fn_801A7560(void *, int);
extern void fn_800CF6AC(void *, int, u8 *, void *, int, int);
extern void fn_801A7598(void *, int);
extern void fn_801A7550(void *, int);
extern void fn_801A7558(void *, int);
extern void fn_801A764C(void *, Vec3 *);
extern void fn_8003B8A0(void);
extern void fn_80078794(void);
extern void fn_801287C4(void *, void (*)(void), void *, int);
extern void fn_801296F8(void *, int);
extern void fn_80204230(void);
extern void fn_802042A4(void);
extern void fn_80128C28();
extern void fn_80128C44(void *, void (*)(void), void *);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);

/* NonMatching: behavior-complete object activation and callback setup. */
int fn_8007930C(void *context, void *object)
{
    u8 *state = fn_80201B8C(context);
    int owner = (int)fn_80201B94(context);
    Vec3 copy;
    Vec3 position;
    int result;
    int value;
    int kind;
    void *action;
    void *entry;
    int i;

    fn_8011F114(&position, object);
    copy = position;
    fn_80128EE4(object);
    result = 0;
    kind = fn_80201C48(owner);
    value = fn_80201B54(context);
    if (fn_80079008(context, object)) {
        result = 0;
        goto done;
    }
    if (*(u8 *)(*(u8 **)(state + 0xC) + 0x45) != 0 ||
        *(signed char *)(*(u8 **)(state + 0xC) + 0x41) != 0)
        goto done;
    entry = fn_801294DC(object, 4, 0, 6);
    if (entry == 0)
        goto done;
    action = fn_801A717C();
    i = fn_80072354(*(int *)(state + 0x90));
    fn_801A7460(action, 4);
    fn_801A74A0(action, value);
    fn_801A74A8(action, kind);
    fn_801A74C8(action, 1);
    fn_801A7560(action, 0x704);
    fn_800CF6AC(context, i, state, action, 0, 4);
    fn_801A7598(action, 0x1A4);
    fn_801A7550(action, 0xC);
    fn_801A7558(action, 7);
    fn_801A764C(action, &copy);
    fn_801287C4(entry, fn_8003B8A0, action, 0x22);
    for (i = 0x23; i < 0x2C; i++)
        fn_801287C4(entry, fn_80078794, action, i);
    fn_801296F8(object, 0x1FD70);
    fn_80128C28(entry, fn_80204230, action);
    fn_80128C44(entry, fn_802042A4, action);
    fn_80201D2C(context, 6);
    fn_80201D14(context, 1);
    result = 1;

done:
    return result;
}
