typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Owner {
    u8 pad[0x159];
    u8 active;
    u8 pad15A[6];
    u16 value160;
} Owner;

typedef struct Work {
    u8 pad38[0x38];
    int object_id;
    u8 pad3C[0xC4 - 0x3C];
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
extern void fn_8006DEF8(Work*, int, void*, void*, int);
extern u16 fn_800496EC(void*, void*, int, int);

int fn_80087D64(Work* work)
{
    Owner* owner;
    void* object;
    State* state;

    state = fn_8006ED98(work);
    object = fn_80201814(work->object_id);
    owner = work->owner;

    if (state->mode == 7) {
        int slot;
        u8* temp;

        fn_80088A04(work);
        slot = fn_8006ECD4(work, 7);
        temp = (u8*)work + slot * 0x2C;
        *(u16*)(temp + 0x60) = 1;
    }

    if (state->mode == 6) {
        fn_8006BEE4(state, fn_8006EA4C);
        if (fn_801A6D94(lbl_8064C824)) {
            int i;
            int offset;
            u8* entry;

            offset = fn_8006ECD4(work, 6) * 0x2C;
            entry = (u8*)work + offset;
            entry[0x68] = 4;
            fn_8006DEF8(work, 6, 0, 0, 0);
            for (i = 0; i < 4; i++) {
                ((u8*)work)[offset + 0x68] = i;
                fn_8006DEF8(work, 6, 0, 0, 0);
            }
            entry[0x68] = 0;
            owner->active = 0;
        }
    } else {
        int index;
        u8* entry;

        fn_8006ED3C(work, 7, &index);
        ((u8*)work)[index * 0x2C + 0x6A] = 0;
        entry = (u8*)work + index * 0x2C;
        entry[0x6B] = 4;
        work->owner->value160 = fn_800496EC(object, entry, 4, 0);
    }
    return 1;
}
