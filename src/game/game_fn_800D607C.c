typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Actor {
    unsigned char pad_000[0x197];
    signed char field_197;
    int field_198;
} Actor;

/* Separate value wrappers preserve the original scalar copy stores. */
typedef struct Word {
    u32 value;
} Word;

extern u32 lbl_8064F3E8;
extern u32 lbl_8064F3EC;
extern u32 lbl_8064F3F0;
extern u32 lbl_8064F3F4;
extern unsigned short fn_8012DBE8(void *, int, u32 *);
extern void fn_800A1AF0(void *, int, void *, int, void *, void *, void *, u16);
extern void fn_800A3C84(void *, int, void *, int);
extern void fn_800D4214(void *, Actor *);
extern void fn_800A4C98(Actor *, void *);
extern void fn_800A4670(Actor *, void *, int);
extern void fn_800A2D78(Actor *);
extern void fn_800A4D04(Actor *);
extern void fn_800A4634(Actor *, void *);

void fn_800D607C(Actor *actor, void *object, void *other, int value)
{
    u16 flags = 0x200;
    Word secondFirst;
    Word chosenSecond;
    Word secondSecond;
    Word firstSecond;
    Word chosenFirst;
    Word firstFirst;
    u32 copy;
    u32 secondCopy;
    u32 selected;
    /* This retained local copy is not a ninth fn_800A1AF0 argument. */
    volatile u32 extra;

    secondFirst.value = lbl_8064F3E8;
    secondSecond.value = lbl_8064F3EC;
    firstSecond.value = lbl_8064F3F0;
    firstFirst.value = lbl_8064F3F4;

    if (other != 0) {
        flags |= 0x32;
        chosenFirst = firstFirst;
        chosenSecond = firstSecond;
    } else {
        flags |= 0x12;
        chosenFirst = secondFirst;
        chosenSecond = secondSecond;
    }
    if (actor->field_198 != -1) {
        fn_8012DBE8(object, 15, &chosenFirst.value);
        selected = chosenFirst.value;
        secondCopy = chosenSecond.value;
        copy = selected;
        extra = selected;
        fn_800A1AF0(object, actor->field_198, other, value, &copy,
                    &secondCopy, &selected, flags);
    }
    if (actor->field_197 != 0) {
        fn_800A3C84(object, actor->field_198, other, value);
    }
    if ((int)other != 0) {
        fn_800D4214(object, actor);
        fn_800A4C98(actor, object);
        fn_800A4670(actor, object, 8);
    } else {
        fn_800A2D78(actor);
        fn_800A4D04(actor);
        fn_800A4634(actor, object);
    }
}
