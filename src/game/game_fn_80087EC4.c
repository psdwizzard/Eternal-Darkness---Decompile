typedef unsigned char u8;

typedef struct State { int mode; } State;
typedef struct Owner { u8 pad[0x159]; u8 active; } Owner;
typedef struct Work {
    u8 pad38[0x38]; int object_id; u8 pad3C[0xC4 - 0x3C]; Owner* owner;
} Work;

extern State* fn_8006ED98(Work*);
extern void* fn_8006D488(Work*);
extern int fn_8006ECD4(Work*, int);
extern void fn_802020B4(void*, int);
extern void fn_801A5C30(int);
extern void fn_8015C8A4(int, int);
extern int lbl_8064C824;
extern int fn_801A6D94(int);
extern void fn_801A6E14(int);
extern void fn_801B05E8(int, int, int, int, int, int, int, int);
extern void* fn_8004918C(void);
extern int fn_801A7780(void*);
extern void fn_8006EA4C(void);
extern void fn_8006BEE4(void*, void (*)(void));
extern void fn_8006DEF8(Work*, int, void*, void*, int);

/* NonMatching: behavior- and size-exact reconstruction. Canonical GC/1.3
 * output scores 98.194176% (412/412 bytes); retail coalesces the branch-local
 * index with owner in r31 and therefore saves r26-r31, while this source uses
 * r25-r31 and lowers the indexed byte stores through equivalent registers. */
int fn_80087EC4(Work* work)
{
    State* state = fn_8006ED98(work);
    void* object = fn_8006D488(work);
    Owner* owner_or_index = work->owner;

    if (state->mode == 7) {
        owner_or_index = (Owner*)fn_8006ECD4(work, 7);
        fn_802020B4(object, 0);
        fn_801A5C30(0);
        fn_8015C8A4(2, 0);
        fn_801A6E14(lbl_8064C824);
        fn_801B05E8(0x1B, 100, 6, 0, 0, 5, 0, 1);
        object = fn_8004918C();
        if (fn_801A7780(object) & 0x80020) {
            ((u8*)work)[(int)owner_or_index * 0x2C + 0x6A] = 2;
            ((u8*)work)[(int)owner_or_index * 0x2C + 0x6B] = 2;
        }
    } else if (fn_801A6D94(lbl_8064C824)) {
        int index = fn_8006ECD4(work, 6);
        int offset = index * 0x2C;
        int i;
        ((u8*)work)[offset + 0x68] = 4;
        fn_8006DEF8(work, 6, 0, 0, 0);
        for (i = 0; i < 4; i++) {
            ((u8*)work)[offset + 0x68] = i;
            fn_8006DEF8(work, 6, 0, 0, 0);
        }
        ((u8*)work)[offset + 0x68] = 0;
        owner_or_index->active = 0;
        fn_8006BEE4(state, fn_8006EA4C);
    } else {
        fn_802020B4(object, 0);
        fn_801A5C30(0);
        fn_8015C8A4(2, 0);
        fn_801A6E14(lbl_8064C824);
    }
    return 1;
}
