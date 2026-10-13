typedef unsigned int u32;
typedef unsigned char u8;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

typedef struct FourWords {
    u32 words[4];
} FourWords;

typedef union Rotation {
    Vec4 vector;
    FourWords words;
} Rotation;

typedef struct Record {
    char pad[0xC];
    FourWords value;
} Record;

typedef struct Object {
    void *primary;
    Record *secondary;
} Object;

typedef struct Slot {
    int depth;
    u8 *model;
    char pad8[0x1C];
    Object *actor;
    int owner;
} Slot;

typedef struct SlotTable {
    Slot previous[6];
    Slot current[6];
    Slot previousShadow[6];
    Slot shadow[6];
    Slot extra[32];
    void *lists[6];
} SlotTable;

typedef struct MenuState {
    int owner;
    int unused4;
    int text;
    u32 action;
    u32 flags;
} MenuState;

typedef struct FadeState {
    char pad0[0x6C];
    void *handle;
    char pad70[0x10];
    int color;
    int active;
    char pad88[0xA];
    short enable;
    int duration;
    int delay;
} FadeState;

extern SlotTable lbl_80330D80;
extern MenuState lbl_80332140;
extern FadeState lbl_8024B3E4;
extern int lbl_8064CCB0;
extern int lbl_8064CCB4;
extern int lbl_8064CCC4;
extern void *lbl_8064CCC8;
extern int lbl_8064CCD4;
extern int lbl_8064CCDC;
extern int lbl_8064CDC8;
extern float lbl_8064FE70;
extern float lbl_8064FE74;
extern float lbl_8064FE84;
extern float lbl_8064FE88;
extern float lbl_8064FE8C;

/* The wrapper forwards f1 to the double-precision inverse cosine. */
extern float fn_8003315C();
extern int fn_8010A32C(int, int, int);
extern void fn_8010C220(int, int, float);
/* Retail forwards the inputs; this callee does not use them. */
extern void fn_8010F218();
extern void fn_80117EF0(void);
extern void fn_8012CDF0(u8 *, int, FourWords, int);
extern void fn_8012CEA4(u8 *, int, Vec4 *);
extern void fn_8012CF08(u8 *, int, Vec4, Vec4, int, int, float);
extern void fn_80144C40(void);
extern void fn_80157824(FourWords *, Object *);
extern float fn_8017A574(const Vec4 *, const Vec4 *);
extern int fn_801A98F4(int, void *);
extern int fn_801AF85C(int);
extern void fn_801B05B0(int, int);
extern void fn_801D1318(int);
extern void *fn_801E5D20(void *);
extern void fn_801E5FB0(void *);
extern int fn_801E8D24(void *);
extern int fn_801E8D3C(void *);
extern unsigned long long fn_8020123C(int, int, int, int);
extern int fn_80201B44(void);

void fn_8010CE70(int owner, int mode)
{
    Rotation target;
    Vec4 current;
    FourWords initial;
    register u8 *base = (u8 *)&lbl_80330D80;
    register void **lists = (void **)(base + 0x9A0);
    Slot *primary;
    Slot *secondary;
    int ready;
    int index;
    int row;
    int offset;
    float angle;
    float dot;
    float magnitude;

    if (lbl_80332140.flags & 2) {
        return;
    }
    fn_80144C40();
    if (lbl_80332140.flags & 1) {
        int actor;
        lbl_8064CDC8 = 2;
        actor = fn_80201B44();
        fn_801D1318(0);
        fn_8020123C(0xB0, actor, actor, 0);
        return;
    }

    switch (lbl_8064CCD4) {
    case 4:
        ready = 1;
        if (!(*(u32 *)fn_801E5D20(lbl_8024B3E4.handle) & 0x4000)) {
            ready = 0;
        }
        fn_801A98F4(0x263, (void *)0x32);
        fn_8010F218(owner, mode);
        if (ready) {
            lbl_8064CCD4 = 5;
            lbl_8064CCB0 = 0;
            if (lbl_8064CCDC != -1 && fn_801AF85C(lbl_8064CCDC)) {
                fn_801B05B0(lbl_8064CCDC, 10);
            }
            lbl_8064CCDC = -1;
            lbl_8024B3E4.color = 0x600C0000;
            lbl_8024B3E4.active = 0;
            lbl_8024B3E4.enable = -1;
            lbl_8024B3E4.duration = 30;
            lbl_8024B3E4.delay = 20;

            row = fn_801E8D24(lists[1]) * 2;
            index = fn_801E8D24(*(void **)(base + 0x9A0));
            index += row;
            offset = index * sizeof(Slot);
            primary = (Slot *)(base + 0x108);
            primary += index;
            fn_80157824(&initial, primary->actor);
            target.words = initial;
            angle = lbl_8064FE74;
            lbl_8064CCB4 = primary->depth;
            fn_8012CEA4(primary->model, 15, &current);
            if (target.vector.x == lbl_8064FE74 &&
                target.vector.y == lbl_8064FE74 &&
                target.vector.z == lbl_8064FE74 &&
                target.vector.w == lbl_8064FE74) {
                target.vector.w = lbl_8064FE70;
            }
            dot = fn_8017A574(&current, &target.vector);
            magnitude = dot < lbl_8064FE74 ? -dot : dot;
            if (lbl_8064FE70 - magnitude > lbl_8064FE84) {
                angle = fn_8003315C(dot);
            }
            if (angle < lbl_8064FE88) {
                fn_8012CDF0(primary->model, 15, target.words, 1);
                fn_8010C220(index, 1, lbl_8064FE88);
                fn_8012CEA4(primary->model, 15, &current);
            }
            fn_8012CF08(primary->model, 15, current, target.vector, 1, 2,
                        lbl_8064FE8C);
            secondary = (Slot *)(base + 0x318);
            secondary = (Slot *)((u8 *)secondary + offset);
            if (secondary->actor != 0) {
                fn_80157824(&target.words, secondary->actor);
                fn_8012CEA4(secondary->model, 15, &current);
                if (target.vector.x == lbl_8064FE74 &&
                    target.vector.y == lbl_8064FE74 &&
                    target.vector.z == lbl_8064FE74 &&
                    target.vector.w == lbl_8064FE74) {
                    target.vector.w = lbl_8064FE70;
                }
                fn_8012CF08(secondary->model, 15, current, target.vector, 1, 2,
                            lbl_8064FE8C);
            }
        }
        break;
    case 2:
        /* ASM: addi retains the list-bank address; C folds it into the load. */
        asm { addi lists, base, 0x9A0 }
        row = fn_801E8D3C(lists[1]) * 2;
        fn_801A98F4(0x263, (void *)0x32);
        fn_80117EF0();
        lbl_8064CCC4 = fn_8010A32C(row, 0, 6);
        lbl_8064CCD4 = 0;
        fn_801E5FB0(lbl_8064CCC8);
        lbl_8064CCC8 = 0;
        break;
    case 1:
        fn_801A98F4(0x263, (void *)0x32);
        lbl_8064CCD4 = 0;
        break;
    case 0:
        lbl_8064CDC8 = 2;
        break;
    case 3:
    case 5:
        break;
    }
}
