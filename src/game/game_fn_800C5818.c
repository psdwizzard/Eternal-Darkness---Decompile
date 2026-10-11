typedef struct Unk8C {
    char pad[0x44];
    int unk44;
} Unk8C;

typedef struct Context {
    char pad[0x8C];
    Unk8C* unk8C;
} Context;

typedef struct SubC4 {
    char pad[0x34];
    int unk34;
} SubC4;

typedef struct Player {
    char pad[0xC4];
    SubC4* unkC4;
} Player;

extern void* lbl_8064C504;

extern Context* fn_80201B8C(void*);
extern void* fn_80201B94(void*);
extern int fn_80201D0C(void);
extern void* fn_80201814(void);
extern int fn_80201B54(void*);
extern int fn_80201B4C(void*);
extern void* fn_80201BC8(void*);
extern void* fn_80201C24(void*);
extern int fn_80157BC4(void);
extern int fn_80157BF4(void*);
extern unsigned int fn_8011FAEC(void*);
extern void* fn_80201B9C(void);
extern void* fn_80204844(void*, int);
extern Player* fn_8006D444(void);
extern int fn_8006D2C8(Player*, int);
extern void* fn_801E6CA0(void*, int, int, int, int);
extern void fn_80027E34(void*, int, int);
extern void fn_80027948(void*, int, int, int, int, int, int);
extern void fn_8020123C(int, int, int, int);

void fn_800C5818(void* object) {
    Context* ctx;
    Unk8C* data;
    int arg;
    void* target;
    int id;
    int state;
    void* item;
    void* sub;
    int a;
    int b;
    Player* player;

    ctx = fn_80201B8C(object);
    if (ctx != 0) {
        data = ctx->unk8C;
    } else {
        data = 0;
    }
    fn_80201B94(object);
    arg = fn_80201D0C();
    target = fn_80201814();
    id = fn_80201B54(object);
    item = 0;
    if (target != 0) {
        state = fn_80201B4C(target);
    } else {
        state = 0;
    }
    if (target != 0) {
        item = fn_80201BC8(target);
    }
    if (item == 0) {
        return;
    }
    sub = fn_80201C24(target);
    if (sub != 0) {
        a = fn_80157BC4();
        b = fn_80157BF4(sub);
    }
    if (fn_8011FAEC(item) & 0x4000) {
        fn_80204844(fn_80201B9C(), 0x20);
        player = fn_8006D444();
        if (fn_8006D2C8(player, 0x11) != 0) {
            player->unkC4->unk34 = 2;
            fn_80027E34(fn_801E6CA0(lbl_8064C504, 0, 0x15, 0, 1), 0, arg);
            fn_8020123C(0x5B, id, data->unk44, player->unkC4->unk34);
        } else if (fn_8006D2C8(player, 9) != 0) {
            fn_80027E34(fn_801E6CA0(lbl_8064C504, b, a, 0, 1), 0, arg);
        }
        fn_8020123C(0x47, id, arg, 0);
    } else if (state == 2) {
        fn_80027948(fn_801E6CA0(lbl_8064C504, b, a, 0, 1), 0, id, arg, 0, 0, 0);
    }
}
