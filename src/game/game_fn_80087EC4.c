typedef unsigned char u8;

typedef struct State { int mode; } State;
typedef struct Owner { u8 pad[0x159]; u8 active; } Owner;
typedef struct Record {
    u8 pad[0x28];
    u8 count;
    u8 unknown;
    u8 flags_a;
    u8 flags_b;
} Record;
typedef struct Work {
    u8 pad38[0x38]; int object_id; u8 pad3C[4];
    Record records[3];
    Owner* owner;
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

/* NonMatching: canonical GC/1.3 is size-exact at 412 bytes and 99.11651%.
 * Typed records recover the mode-7 stores and mode-6 address expression.
 * The byte-indexed loop still hoists work + 0x68 instead of offset + 0x68,
 * retaining a seventh saved register and a 0x30-byte frame (retail: 0x20).
 */
int fn_80087EC4(Work* work)
{
    int index;
    int offset;
    Owner* owner;
    void* object;
    State* state;
    state = fn_8006ED98(work);
    object = fn_8006D488(work);
    owner = work->owner;

    if (state->mode == 7) {
        index = fn_8006ECD4(work, 7);
        fn_802020B4(object, 0);
        fn_801A5C30(0);
        fn_8015C8A4(2, 0);
        fn_801A6E14(lbl_8064C824);
        fn_801B05E8(0x1B, 100, 6, 0, 0, 5, 0, 1);
        object = fn_8004918C();
        if (fn_801A7780(object) & 0x80020) {
            work->records[index].flags_a = 2;
            work->records[index].flags_b = 2;
        }
    } else if (fn_801A6D94(lbl_8064C824)) {
        int i;
        index = fn_8006ECD4(work, 6);
        offset = index * 0x2C;
        work->records[index].count = 4;
        fn_8006DEF8(work, 6, 0, 0, 0);
        for (i = 0; i < 4; i++) {
            ((u8*)work)[offset + 0x68] = i;
            fn_8006DEF8(work, 6, 0, 0, 0);
        }
        work->records[index].count = 0;
        owner->active = 0;
        fn_8006BEE4(state, fn_8006EA4C);
    } else {
        fn_802020B4(object, 0);
        fn_801A5C30(0);
        fn_8015C8A4(2, 0);
        fn_801A6E14(lbl_8064C824);
    }
    return 1;
}
