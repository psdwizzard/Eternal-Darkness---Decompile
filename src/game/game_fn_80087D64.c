typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Owner {
    u8 pad[0x159];
    u8 active;
    u8 pad15A[6];
    u16 value160;
} Owner;

typedef struct Record {
    u8 pad[0x20];
    u16 value;
    u8 pad22[8];
    u8 field_2A;
    u8 field_2B;
} Record;

typedef struct Work {
    u8 pad38[0x38];
    int object_id;
    u8 pad3C[4];
    Record records[3];
    Owner* owner;
    int pad;
} Work;

typedef struct State {
    int mode;
} State;

extern State* fn_8006ED98(Work*);
extern void *fn_8006ED3C();
extern void *fn_80201814();
extern int fn_80088A04(Work*);
extern int fn_8006ECD4(Work*, int);
extern int fn_8006EA4C(Owner*);
extern void fn_8006BEE4(void*, int (*)(Owner*));
extern int lbl_8064C824;
extern int fn_801A6D94(int);
extern void fn_8006DEF8(Work*, int, void*, void*, int);
extern unsigned int fn_800496EC(void*);

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

        fn_80088A04(work);
        slot = fn_8006ECD4(work, 7);
        work->records[slot].value = 1;
    }

    if (state->mode == 6) {
        fn_8006BEE4(state, fn_8006EA4C);
        if (fn_801A6D94(lbl_8064C824)) {
            u8* entry;
            int offset = fn_8006ECD4(work, 6) * 0x2C;
            int data_offset;
            int i;

            entry = (u8*)work + offset;
            entry[0x68] = 4;
            fn_8006DEF8(work, 6, 0, 0, 0);
            i = 0;
            data_offset = offset + 0x68;
            do {
                *(u8*)((unsigned int)work + data_offset) = i;
                fn_8006DEF8(work, 6, 0, 0, 0);
                i++;
            } while (i < 4);
            entry[0x68] = 0;
            owner->active = 0;
        }
    } else {
        int index;

        fn_8006ED3C(work, 7, &index);
        work->records[index].field_2A = 0;
        work->records[index].field_2B = 4;
        work->owner->value160 = fn_800496EC(object);
    }
    return 1;
}
