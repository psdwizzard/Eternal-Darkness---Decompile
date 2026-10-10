typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;

typedef struct State {
    void *unk0;
    u8 pad04[0x90];
    u8 unk94;
} State;

typedef struct Context {
    State *unk0;
} Context;

extern Context *fn_80201B8C(void);
extern void *fn_80200C38(void *);
extern void *fn_80201BC8(void *);
extern s32 fn_80201B54(void *);
extern s32 fn_801A7490(void *);
extern s32 fn_801A7468(void *);
extern s32 fn_801A7778(void *);
extern void *fn_801294DC(void *, s32, s32, s32);
extern s32 fn_8015793C(s32);
extern void *fn_801A717C(void);
extern void fn_801A7324(void *, void *);
extern u32 fn_801A7570(void *);
extern void fn_801A7560(void *, u32);
extern s32 fn_801A77F8(void *);
extern s32 fn_801A76B0(void *);
extern void fn_801A75A8(void *, u8);
extern void fn_801A74A0(void *, s32);
extern u32 fn_801A74C0(void *);
extern void fn_801A74C8(void *, u32);
extern void fn_801A7538(void *, s32);
extern void fn_801A7518(void *, u8);
extern void fn_801A7550(void *, s32);
extern void fn_801A7558(void *, s32);
extern void fn_801A75B0(void *, s32);
extern s32 fn_8011F130(void *);
extern void fn_801A764C(void *, s32);
extern s32 fn_80129364(void *, s32, s32, s32 *, s32);
extern void fn_801287C4(void *, void *, void *, s32);
extern void fn_80128C28(void *, void *, u32);
extern void fn_80128C44(void *, void *, u32);
extern void fn_8020123C(s32, s32, s32, void *);
extern void fn_80201D2C(void *, s32);
extern void fn_80201D14(void *, s32);

extern void fn_800C3418();
extern void fn_800C328C();
extern void fn_800BF7C0();
extern void fn_800BF81C();
extern void fn_80204810();

s32 fn_800C2FC4(void *obj, void *arg1, s32 arg2) {
    void *queue;
    Context *ctx;
    s32 index = 0;
    s32 id;
    s32 sound;
    int busy;
    void *src;
    void *owner;
    s32 proto;
    s32 kind;
    u8 color;
    u8 alpha;
    u32 flags;
    u32 mask;

    ctx = fn_80201B8C();
    busy = 0;
    src = fn_80200C38(arg1);
    owner = fn_80201BC8(obj);
    id = fn_80201B54(obj);
    sound = fn_801A7490(src);
    proto = fn_801A7468(src);
    kind = fn_801A7778(src);
    if (ctx->unk0->unk94 != 0) {
        busy = 1;
    }
    if (!busy && proto != -1) {
        queue = fn_801294DC(owner, proto, 0, 6);
        if (queue != 0) {
            void *inst;

            color = fn_8015793C(kind);
            inst = fn_801A717C();
            fn_801A7324(src, inst);
            flags = fn_801A7570(src) | 0x28204;
            if (arg2 == 0) {
                flags |= 0x20;
            }
            fn_801A7560(inst, flags);
            alpha = fn_801A77F8(src);
            fn_801A75A8(inst, alpha | fn_801A76B0(src));
            fn_801A74A0(inst, id);
            fn_801A74C8(inst, fn_801A74C0(inst) | 1);
            fn_801A7538(inst, 1);
            fn_801A7518(inst, color);
            fn_801A7550(inst, 0xC);
            fn_801A7558(inst, 0xC);
            fn_801A75B0(inst, 1);
            fn_801A764C(inst, fn_8011F130(owner));
            if (fn_80129364(owner, 1, 0, &index, -1) != -1) {
                if (arg2 != 0) {
                    fn_801287C4(queue, fn_800C3418, inst, index);
                } else {
                    fn_801287C4(queue, fn_800C328C, inst, index);
                }
                fn_801287C4(queue, fn_800BF7C0, inst, index + 2);
                fn_801287C4(queue, fn_800BF81C, src, index + 2);
            }
            mask = (id << 8) | 0xC;
            fn_80128C28(queue, fn_80204810, mask);
            fn_80128C44(queue, fn_80204810, mask);
            if (sound != 0) {
                fn_8020123C(0xA, id, sound, inst);
            }
            fn_80201D2C(obj, 0x6C);
            fn_80201D14(obj, 1);
            ctx->unk0->unk0 = inst;
            return 1;
        }
    }
    return 0;
}
