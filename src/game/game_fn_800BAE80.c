typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned char u8;
typedef float f32;
#define NULL 0

typedef struct NodeHeader {
    /* 0x00 */ f32 scale;
    /* 0x04 */ u16 id;
    /* 0x08 */ s32 param8;
    /* 0x0C */ s32 paramC;
    /* 0x10 */ s32 param10;
    /* 0x14 */ s16 val14;
    /* 0x16 */ s16 val16;
    /* 0x18 */ u16 val18;
    /* 0x1A */ u16 val1A;
    /* 0x1C */ u8 val1C;
    /* 0x1D */ u8 val1D;
    /* 0x1E */ u8 val1E;
    /* 0x1F */ u8 val1F;
    /* 0x20 */ u8 val20;
    /* 0x21 */ u8 flags;
    /* 0x22 */ s16 val22;
} NodeHeader;

typedef struct Model {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ void *unk4;
} Model;

extern void *memcpy(void *dst, const void *src, unsigned long n);
extern void *fn_80047D6C(void);
extern int fn_800BA6D4(char *, int, u16 *, int, int);
extern void fn_800CBAB8();
extern void fn_800CBF40();
extern void fn_800CC140(void *, void *, int, s32, int);
extern void fn_800DBF60(void *, void *, int, void *, f32);
extern void fn_800DC2B8(void *, int, int, f32);
extern void *fn_80155DB4(void *);
extern void fn_801568B8(void *, int);
extern void fn_801568C0(void *, int);
extern void fn_801568FC(void *, int);
extern void fn_801579E0(void *, void *, void *);
extern void fn_80157A98(Model *, int, int);
extern void fn_80157AC4(Model *, s32);
extern void fn_80157B3C(Model *, int);
extern void fn_80157B48(Model *, int);
extern void fn_80157B54(Model *, int);
extern void fn_80157B60(Model *, int);
extern void fn_80157B94(Model *, int);
extern void fn_80157BA0(Model *, int);
extern void fn_80157BAC(Model *, int);
extern void fn_80157BB8(Model *, int);
extern void fn_80157C88(Model *, s32);
extern void fn_80157FA8(void *);
extern int fn_8015821C(Model *);
extern void *fn_80158598(void *, int);
extern void fn_801586CC(void *, int, void (*)(), void (*)());
extern void fn_801FDF74(void *, int);
extern void fn_801FE22C(void *);
extern int fn_801FE25C(void *);
extern void fn_801FE4FC(void *);
extern void *fn_80201814(void *);
extern int fn_80201B54(int *object);
extern void fn_80201BC8(void *);
extern void *fn_80201C24(void *);
typedef struct ListNode80204CE4 ListNode80204CE4;
extern int fn_80204CE4(void *object, ListNode80204CE4 *node);

extern f32 lbl_8064F010;

int fn_800BAE80(u8 *data, void *arg1, void *arg2, s32 *count, void **out) {
    NodeHeader hdr;
    void *child;
    u16 size;
    int total;
    void *node;
    void *anim;
    Model *model;
    void **effect;

    memcpy(&hdr, data, sizeof(NodeHeader));
    node = (void *)fn_800BA6D4((char *)data + 0x24, hdr.id, &size, 1, 1);
    *out = (void *)fn_80201B54(node);
    total = size + 0x24;
    fn_80204CE4(node, arg1);
    model = fn_80201C24(node);
    anim = fn_80155DB4(node);
    fn_80201BC8(node);
    fn_80157C88(model, hdr.param8);
    if (model->unk4 != NULL) {
        fn_80157A98(model, hdr.val18, 1);
        fn_80157A98(model, hdr.val1A, 2);
        fn_80157B60(model, hdr.val1C);
        fn_80157B3C(model, hdr.val1D);
        if (hdr.val1C != 0 && hdr.scale > lbl_8064F010) {
            if (fn_8015821C(model) == 0x83) {
                fn_800DC2B8(*out, hdr.val1C, hdr.val1D, hdr.scale);
            } else {
                effect = NULL;
                if (hdr.flags & 1) {
                    effect = fn_80047D6C();
                    if (fn_801FE25C(*effect) != 0) {
                        fn_801FDF74(*effect, 0);
                        fn_801FE22C(*effect);
                        fn_801FE4FC(*effect);
                    }
                }
                fn_800DBF60(arg2, node, hdr.val1D, effect, hdr.scale);
            }
        }
        if (fn_8015821C(model) == 0xA9) {
            effect = NULL;
            if (hdr.flags & 1) {
                effect = fn_80047D6C();
                if (fn_801FE25C(*effect) != 0) {
                    fn_801FDF74(*effect, 0);
                    fn_801FE22C(*effect);
                    fn_801FE4FC(*effect);
                }
            }
            fn_800DBF60(arg2, node, hdr.val1D, effect, lbl_8064F010);
        }
        fn_80157B48(model, hdr.val14);
        fn_80157B54(model, hdr.val16);
        fn_80157BA0(model, hdr.val22);
        fn_80157BB8(model, hdr.val1E);
        fn_80157BAC(model, hdr.val1F);
        fn_80157B94(model, hdr.val20);
        fn_80157AC4(model, hdr.param10);
    }
    if (hdr.flags & 2) {
        fn_801568B8(anim, 0);
    }
    if (hdr.flags & 4) {
        fn_801568C0(anim, 0);
    }
    if (hdr.flags & 8) {
        fn_801568FC(anim, 0);
    }
    if (hdr.flags & 1) {
        void *entry = fn_80158598(arg2, 0);
        if (entry == NULL) {
            entry = fn_80158598(arg2, 1);
            fn_801586CC(entry, 6, fn_800CBAB8, fn_800CBF40);
        }
        fn_800CC140(arg2, *out, 0, hdr.paramC, 1);
        fn_80157FA8(entry);
    }
    if (hdr.flags & 0x10) {
        *count += 1;
        total += fn_800BAE80(data + (u16)total, arg1, arg2, count, &child);
        fn_801579E0(model, NULL, child);
        fn_801579E0(fn_80201C24(fn_80201814(child)), *out, NULL);
    }
    return total;
}
