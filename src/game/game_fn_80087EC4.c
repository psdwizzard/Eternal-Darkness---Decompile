typedef unsigned char u8;

typedef struct Vec3 Vec3;

typedef struct State { int mode; } State;
typedef struct Owner { u8 pad[0x159]; u8 active; } Owner;
typedef struct Record {
    u8 pad[0x28];
    u8 count;
    u8 unknown;
    u8 flags_a;
    u8 flags_b;
} Record;
typedef struct WorkFields {
    u8 pad38[0x38]; int object_id; u8 pad3C[4];
    Record records[3];
    Owner* owner;
} WorkFields;
typedef union Work {
    WorkFields fields;
    u8 bytes[0xC8];
} Work;

typedef struct BranchRoles {
    Owner* owner;
    int offset;
    Work* record_base;
} BranchRoles;

extern State* fn_8006ED98(Work*);
extern void* fn_8006D488(Work*);
extern int fn_8006ECD4(Work*, int);
extern void fn_802020B4(void*, int);
extern void fn_801A5C30(int);
extern void fn_8015C8A4(int, int);
extern int lbl_8064C824;
extern int fn_801A6D94(int);
extern void fn_801A6E14(int);
extern int fn_801B05E8(int, u8, u8, u8, Vec3*, u8, int, int);
extern void* fn_8004918C(void);
extern int fn_801A7780(void*);
extern int fn_8006EA4C(Owner*);
extern void fn_8006BEE4(void*, int (*)(Owner*));
extern void fn_8006DEF8(Work*, int, void*, void*, int);

int fn_80087EC4(void* argument)
{
    BranchRoles roles;
    void* object;
    Work* work = argument;
    State* state;

    state = fn_8006ED98(work);
    object = fn_8006D488(work);
    roles.owner = work->fields.owner;

    if (state->mode == 7) {
        int index = fn_8006ECD4(work, 7);
        fn_802020B4(object, 0);
        fn_801A5C30(0);
        fn_8015C8A4(2, 0);
        fn_801A6E14(lbl_8064C824);
        fn_801B05E8(0x1B, 100, 6, 0, 0, 5, 0, 1);
        object = fn_8004918C();
        if (fn_801A7780(object) & 0x80020) {
            work->fields.records[index].flags_a = 2;
            work->fields.records[index].flags_b = 2;
        }
    } else if (fn_801A6D94(lbl_8064C824)) {
        int index;
        int i;

        index = fn_8006ECD4(work, 6);
        roles.offset = index * 0x2C;
        roles.record_base = (Work*)((u8*)work + roles.offset);
        roles.record_base->fields.records[0].count = 4;
        fn_8006DEF8(work, 6, 0, 0, 0);
        roles.offset += 0x68;
        for (i = 0; i < 4; i++) {
            work->bytes[roles.offset] = i;
            fn_8006DEF8(work, 6, 0, 0, 0);
        }
        roles.record_base->fields.records[0].count = 0;
        roles.owner->active = 0;
        fn_8006BEE4(state, fn_8006EA4C);
    } else {
        fn_802020B4(object, 0);
        fn_801A5C30(0);
        fn_8015C8A4(2, 0);
        fn_801A6E14(lbl_8064C824);
    }
    return 1;
}
