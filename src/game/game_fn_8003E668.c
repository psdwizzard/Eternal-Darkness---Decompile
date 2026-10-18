typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct Object Object;
typedef struct Object80201C48 Object80201C48;
typedef struct EffectState EffectState;
typedef struct Vec3 { float x, y, z; } Vec3;

/* Each event accessor exposes a different part of the event record. */
typedef struct { u8 pad[0x9C]; u32 value; } EventId;
typedef struct { u8 pad[0x98]; u32 value; } EventOwner;
typedef struct { u8 pad[0xB6]; u16 value; } EventKind;
typedef struct { u8 pad[0xB4]; s16 value; } EventMode;
typedef struct { u8 pad[0x88]; u32 value; } EventFlags;
typedef struct { u32 words[3]; } EventPosition;
typedef struct { u8 pad[0x54]; EventPosition value; } EventLocation;
#define NULL ((void *)0)

extern s32 fn_800CC4DC(s32 object);
extern u64 fn_8020123C(int, int, int, int);
extern void *fn_80036D5C(void *object);
extern void fn_80036DA4(void *object, void *value);
extern void *fn_80201C48(Object80201C48 *);
extern s32 fn_800359A0(void *object, void *);
extern int fn_80201B44(void);
extern void fn_801A977C(void *, int);
extern int fn_8003DED0(int *object, void *, EffectState *);
extern float fn_800C9C60(void *object);
extern void fn_800C9D68(void *object, float value);
extern int fn_8003D69C(int);
extern u32 rand(void);
extern int fn_801AAE68(u16, u8, u8, float, Vec3 *, s8, u8, u8, u16, u32);
extern u32 fn_8011FAEC(void *);
extern s32 fn_80067858(s32);
extern int fn_800460EC(void);
extern int fn_80201B64(int *object);
extern void *fn_801A717C(void);
extern void fn_801A74A0(EventId *, u32);
extern void fn_801A74A8(EventOwner *, u32);
extern void fn_801A7538(EventKind *, u16);
extern void fn_801A7518(EventMode *, s16);
extern void fn_801A7470(EventFlags *, u32);
extern void fn_801A764C(EventLocation *, const EventPosition *);
extern void fn_8020104C(int, int, int, int, float);
extern u8 fn_8013017C(Object *);
extern int fn_801305D4(Object *);
extern int fn_801301B0(Object *, u8, u8);

extern int lbl_8064C598;
extern int lbl_8064D18C;
extern int lbl_8064D5A8;
extern const float lbl_8064E26C;
extern const float lbl_8064E2C0;

void fn_8003E668(void *object, Object *actor, int id, u8 *info,
                 Object80201C48 *target, void *pos, u8 *state, u8 **counter)
{
    u32 flags;
    float ratio;
    int value;
    void *event;
    int owner;
    u8 *entry;

    if (fn_800CC4DC((s32)object) != 0 && *(int *)(info + 0xBC) != 0) {
        fn_8020123C(0xF8, id, *(int *)(info + 0xBC), 0);
    }
    flags = (u32)fn_80036D5C(object);
    if (lbl_8064C598 == 0 && !(flags & 8) && (s32)fn_80201C48(target) == 0) {
        if (fn_80201B44() == fn_800359A0(object, 0)) {
            fn_80036DA4(object, (void *)(flags | 8));
            fn_801A977C(actor, 0x17);
        }
    }
    fn_8003DED0(object, actor, (EffectState *)info);
    ratio = fn_800C9C60(object);
    if ((u8)lbl_8064D5A8 == 0) {
        fn_800C9D68(object, ratio);
    }
    if (!(lbl_8064D5A8 & 0x7F) && fn_8003D69C(id) != 0) {
        fn_801AAE68((rand() & 1) ? 0x19E : 0x1D2, 0x50, 0, lbl_8064E2C0, pos, 2, 2, 0, (u16)lbl_8064D18C, 0);
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
            fn_8020104C(0x3A, id, owner, (int)event, lbl_8064E26C);
        }
    }
    if ((fn_8013017C(actor) & 0x40) && fn_801305D4(actor) == 0) {
        fn_801301B0(actor, 0x40, 0);
    }
}
