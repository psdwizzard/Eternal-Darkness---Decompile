typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

extern void *fn_80200C38(void *);
extern void *fn_80201BC8(void *);
extern s32 fn_80201B54(void *);
extern s32 fn_801A7468(void *);
extern void *fn_801A7778(void *);
extern void *fn_8004910C(void *);
extern int fn_8011EB04(void *);
extern u16 fn_80157994(void *);
extern void *fn_801294DC(void *, s32, s32, s32);
extern s32 fn_80129364(void *, s32, s32, s32 *, s32);
extern void fn_801A75B0(void *, s32);
extern u8 fn_800CC2D8(void *, s32);
extern void fn_801287C4(void *, void *, void *, s32);
extern void fn_80128C28(void *, void *, u32);
extern void fn_80128C44(void *, void *, u32);
extern void fn_80201D2C(void *, s32);
extern void fn_80201D14(void *, s32);

extern void fn_800BF0C0();
extern void fn_800C48AC();
extern void fn_800C4A74();
extern void fn_800BFF14();
extern void fn_800BF4C8();
extern void fn_800BFF84();
extern void fn_800BF36C();
extern void fn_80204810();

s32 fn_800C4C4C(void *obj, void *arg1) {
    s32 index;
    s32 proto;
    s32 id;
    void *item;
    void *src;
    void *queue;
    void *owner;
    void *target;
    void *kind;

    owner = fn_80201BC8(obj);
    src = fn_80200C38(arg1);
    proto = fn_801A7468(src);
    id = fn_80201B54(obj);
    item = fn_8004910C(src);
    target = fn_80201BC8(item);
    kind = fn_801A7778(src);
    if (target != 0 && fn_8011EB04(target) == 0xC6 && fn_80157994(kind) == 0) {
        fn_80201D2C(obj, 1);
        fn_80201D14(obj, 1);
        return 1;
    }
    queue = fn_801294DC(owner, proto, 0, 6);
    if (queue != 0) {
        id <<= 8;
        fn_80128C28(queue, fn_80204810, id | 6);
        fn_80128C44(queue, fn_80204810, id | 7);
        if (item != 0 && fn_8011EB04(target) == 0xC6 &&
            fn_80129364(owner, 1, 0, &index, -1) != -1) {
            fn_801A75B0(src, 1);
            fn_801287C4(queue, fn_800BF0C0, src, index);
            fn_801287C4(queue, fn_800C48AC, target, index);
            fn_801287C4(queue, fn_800C4A74, target, index + 5);
            if (fn_800CC2D8(target, 0) != 0) {
                fn_801287C4(queue, fn_800BFF14, src, index - 1);
                fn_801287C4(queue, fn_800BF4C8, src, index + 1);
                fn_801287C4(queue, fn_800BFF84, src, index + 10);
                fn_801287C4(queue, fn_800BF36C, src, index - 1);
            }
        }
        fn_80201D2C(obj, 0x55);
        fn_80201D14(obj, 1);
    } else {
        return 0;
    }
    return 1;
}
