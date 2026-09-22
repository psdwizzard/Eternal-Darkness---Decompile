typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct EntryView {
    u8 pad[0x20];
    u16 enabled;
    u8 pad62[6];
    u8 mode;
    u8 pad69;
    u8 flag;
    u8 count;
} EntryView;

typedef struct Owner {
    u8 pad[0x159];
    u8 active;
    u8 pad15A[6];
    u16 value160;
} Owner;

typedef struct Work {
    u8 pad38[0x38];
    int object_id;
    u8 pad3C[4];
    EntryView entries[3];
    Owner* owner;
} Work;

typedef struct State {
    int mode;
} State;

extern State* fn_8006ED98(Work*);
extern void *fn_8006ED3C();
extern void *fn_80201814();
extern void fn_80088A04(Work*);
extern int fn_8006ECD4(Work*, int);
extern void fn_8006EA4C(void);
extern void fn_8006BEE4(void*, void (*)(void));
extern int lbl_8064C824;
extern int fn_801A6D94(int);
extern void fn_8006DEF8(Work*, u32, u32, u32, u16);
extern unsigned int fn_800496EC(void*);

int fn_80087D64(Work* work)
{
    void* object;
    Owner* owner;
    State* state;

    state = fn_8006ED98(work);
    object = fn_80201814(work->object_id);
    owner = work->owner;

    if (state->mode == 7) {
        int slot;

        fn_80088A04(work);
        slot = fn_8006ECD4(work, 7);
        work->entries[slot].enabled = 1;
    }

    if (state->mode == 6) {
        fn_8006BEE4(state, fn_8006EA4C);
        if (fn_801A6D94(lbl_8064C824)) {
            int slot;
            u8* entry;
            int i;

            slot = fn_8006ECD4(work, 6);
            entry = (u8*)work + slot * 0x2C;
            entry[0x68] = 4;
            fn_8006DEF8(work, 6, 0, 0, 0);
            for (i = 0; i < 4; i++) {
                work->entries[slot].mode = i;
                fn_8006DEF8(work, 6, 0, 0, 0);
            }
            entry[0x68] = 0;
            owner->active = 0;
        }
    } else {
        int index;

        fn_8006ED3C(work, 7, &index);
        work->entries[index].flag = 0;
        work->entries[index].count = 4;
        work->owner->value160 = fn_800496EC(object);
    }
    return 1;
}
