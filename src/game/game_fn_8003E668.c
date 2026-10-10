typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
#define NULL ((void *)0)

extern int fn_800CC4DC(void);
extern void fn_8020123C(int, int, int, int);
extern u32 fn_80036D5C(void *object);
extern void fn_80036DA4(void *object, u32 flags);
extern int fn_80201C48(int);
extern int fn_800359A0(void *object, int);
extern int fn_80201B44(void);
extern void fn_801A977C(int, int);
extern void fn_8003DED0(void *object, int, void *);
extern void fn_800C9C60(void *object);
extern void fn_800C9D68(void *object);
extern int fn_8003D69C(int);
extern int fn_800FBFB0(void);
extern int fn_801AAE68(u16, int, int, float, void *, int, int, int, u16, int);
extern u32 fn_8011FAEC(int);
extern void fn_80067858(int);
extern int fn_800460EC(void);
extern int fn_80201B64(void *object);
extern void *fn_801A717C(void);
extern void fn_801A74A0(void *, int);
extern void fn_801A74A8(void *, int);
extern void fn_801A7538(void *, int);
extern void fn_801A7518(void *, int);
extern void fn_801A7470(void *, int);
extern void fn_801A764C(void *, void *);
extern void fn_8020104C(int, int, int, void *, float);
extern u32 fn_8013017C(int);
extern int fn_801305D4(int);
extern void fn_801301B0(int, int, int);

extern int lbl_8064C598;
extern int lbl_8064D18C;
extern int lbl_8064D5A8;
extern const float lbl_8064E26C;
extern const float lbl_8064E2C0;

void fn_8003E668(void *object, int actor, int id, u8 *info, int target, void *pos,
                 u8 *state, u8 **counter)
{
    u32 flags;
    int value;
    void *event;
    int owner;
    u8 *entry;

    if (fn_800CC4DC() != 0 && *(int *)(info + 0xBC) != 0) {
        fn_8020123C(0xF8, id, *(int *)(info + 0xBC), 0);
    }
    flags = fn_80036D5C(object);
    if (lbl_8064C598 == 0 && !(flags & 8) && fn_80201C48(target) == 0) {
        if (fn_80201B44() == fn_800359A0(object, 0)) {
            fn_80036DA4(object, flags | 8);
            fn_801A977C(actor, 0x17);
        }
    }
    fn_8003DED0(object, actor, info);
    fn_800C9C60(object);
    if ((u8)lbl_8064D5A8 == 0) {
        fn_800C9D68(object);
    }
    if (!(lbl_8064D5A8 & 0x7F) && fn_8003D69C(id) != 0) {
        fn_801AAE68((fn_800FBFB0() & 1) ? 0x19E : 0x1D2, 0x50, 0, lbl_8064E2C0, pos, 2, 2, 0, (u16)lbl_8064D18C, 0);
    }
    if (fn_8011FAEC(actor) & 0x10) {
        (*(u8 **)(state + 0x8C))[0x167]++;
    }
    entry = *counter;
    if (entry != NULL && (s8)entry[0x10A] != 0) {
        entry[0x10A]--;
    } else if (*(int *)(state + 0x94) == 2 && entry == NULL) {
        fn_80067858(id);
    }
    if (state[0x9F] == 0x25 && !(lbl_8064D5A8 & 0x7F) && fn_800460EC() == 0) {
        value = fn_80201B64(object);
        if (value != 8 && value != 9 && value != 0x1F) {
            event = fn_801A717C();
            owner = fn_80201B44();
            fn_801A74A0(event, id);
            fn_801A74A8(event, owner);
            fn_801A7538(event, 2);
            fn_801A7518(event, 1);
            fn_801A7470(event, -1);
            fn_801A764C(event, pos);
            fn_8020104C(0x3A, id, owner, event, lbl_8064E26C);
        }
    }
    if ((fn_8013017C(actor) & 0x40) && fn_801305D4(actor) == 0) {
        fn_801301B0(actor, 0x40, 0);
    }
}
