typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Actor {
    unsigned char pad_000[0x197];
    signed char field_197;
    int field_198;
} Actor;

typedef struct Pair {
    u32 first;
    u32 second;
} Pair;

extern u32 lbl_8064F3E8;
extern u32 lbl_8064F3EC;
extern u32 lbl_8064F3F0;
extern u32 lbl_8064F3F4;
extern unsigned short fn_8012DBE8(void *, int, u32 *);
extern void fn_800A1AF0(void *, int, void *, int, void *, void *, void *, u16, u32);
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
    Pair first;
    Pair second;
    Pair chosen;
    u32 selected;
    u32 copy;
    u32 secondCopy;

    second.first = lbl_8064F3E8;
    second.second = lbl_8064F3EC;
    first.second = lbl_8064F3F0;
    first.first = lbl_8064F3F4;

    if (other != 0) {
        flags |= 0x32;
        chosen = first;
    } else {
        flags |= 0x12;
        chosen = second;
    }
    if (actor->field_198 != -1) {
        fn_8012DBE8(object, 15, &chosen.first);
        selected = chosen.first;
        copy = selected;
        secondCopy = chosen.second;
        fn_800A1AF0(object, actor->field_198, other, value, &copy,
                    &secondCopy, &selected, flags, selected);
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
