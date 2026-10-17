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

extern void* fn_80201B8C(unsigned char*);
extern void* fn_80201B94(unsigned char*);
extern void* fn_80201D0C(void**);
typedef struct Entry80201814 Entry80201814;
extern Entry80201814* fn_80201814(int);
extern int fn_80201B54(int*);
extern int fn_80201B4C(int*);
extern void* fn_80201BC8(void*);
typedef struct Object80201C24 Object80201C24;
extern void* fn_80201C24(Object80201C24*);
typedef struct Object { void* primary; unsigned char* secondary; } Object;

extern unsigned char fn_80157BC4(Object*);
extern unsigned char fn_80157BF4(Object*);
extern unsigned int fn_8011FAEC(void*);
extern void* fn_80201B9C(void);
extern void* fn_80204844(void*, int);
extern void* fn_8006D444(void*);
typedef struct Owner Owner;
extern int fn_8006D2C8(Owner*, int);
typedef struct TextDescriptor TextDescriptor;
extern TextDescriptor* fn_801E6CA0(void*, unsigned int, unsigned int, unsigned int, int);
extern void fn_80027E34(int, int, void*);
extern void fn_80027948(void*, int, void*, void*, int, int, int);
extern unsigned long long fn_8020123C(int, int, int, int);

void fn_800C5818(void* object) {
    Context* ctx;
    Unk8C* data;
    int targetId;
    int lookupId;
    void* target;
    int objectId;
    int state;
    void* item;
    Object* sub;
    register unsigned int textIndex;
    register unsigned int textGroup;
    register unsigned char fieldByte;
    register unsigned int indexWord;
    Player* player;

    ctx = fn_80201B8C(object);
    if (ctx != 0) {
        data = ctx->unk8C;
    } else {
        data = 0;
    }
    lookupId = (int)fn_80201D0C(fn_80201B94(object));
    targetId = lookupId;
    target = fn_80201814(lookupId);
    objectId = fn_80201B54(object);
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
        fieldByte = fn_80157BC4(sub);
        /* ASM: mr preserves the zero-extended lbz result; C promotion adds a redundant clrlwi. */
        asm { mr indexWord, fieldByte }
        textIndex = indexWord;
        fieldByte = fn_80157BF4(sub);
        /* ASM: mr preserves the zero-extended lbz result; C promotion adds a redundant clrlwi. */
        asm { mr textGroup, fieldByte }
    }
    if (fn_8011FAEC(item) & 0x4000) {
        player = fn_8006D444(fn_80204844(fn_80201B9C(), 0x20));
        if (fn_8006D2C8((Owner*)player, 0x11) != 0) {
            player->unkC4->unk34 = 2;
            fn_80027E34((int)fn_801E6CA0(lbl_8064C504, 0, 0x15, 0, 1), 0, (void*)targetId);
            fn_8020123C(0x5B, objectId, data->unk44, player->unkC4->unk34);
        } else if (fn_8006D2C8((Owner*)player, 9) != 0) {
            fn_80027E34((int)fn_801E6CA0(lbl_8064C504, textGroup, textIndex, 0, 1), 0, (void*)targetId);
        }
        fn_8020123C(0x47, objectId, targetId, 0);
    } else if (state == 2) {
        fn_80027948(fn_801E6CA0(lbl_8064C504, textGroup, textIndex, 0, 1), 0, (void*)objectId, (void*)targetId, 0, 0, 0);
    }
}
