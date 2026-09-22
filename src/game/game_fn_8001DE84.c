typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct DataState {
    u8 pad00[0x28];
    u32 field28;
    u32 field2C;
} DataState;

typedef struct Info {
    u8 pad00[0x14];
    u32 field14;
    u8 pad18[4];
    u32 value;
    u32 previous_value;
    u8 pad24[0xC];
    u32 flags;
    u8 pad34[0xA];
    u8 mode;
    u8 previous_mode;
    u8 pad40[4];
} Info;

typedef struct Work {
    u32 field00;
    u32 field04;
    u32 field08;
    u32 field0C;
    u32 field10;
    u16* values;
} Work;

typedef struct GlobalState {
    u8 pad00[0x1C];
    Info info;
    u8 object60[0x38];
    Work work;
    u8 padB0[0x10];
    u16 values[0x100];
    u8 clear[0x100];
} GlobalState;

extern u8 lbl_80302400[];
extern DataState lbl_8023D660;

typedef struct TypeA TypeA;
typedef struct TypeB TypeB;
extern void fn_8020EFBC(TypeA*);
extern void fn_8020F0F8(TypeB*);
extern void fn_80228B50(void*, void*, s32, u32);

void fn_8001DE84(u8 mode, u32 value)
{
    register u8* state = lbl_80302400;
    register Info* info = (Info*)(state + 0x1C);
    register Work* work = (Work*)(state + 0x98);
    s32 i;

    info->flags &= ~2U;
    fn_8020EFBC((TypeA*)(state + 0x60));
    fn_8020F0F8((TypeB*)((u8*)info + 0x44));

    info->previous_mode = info->mode;
    info->mode = mode;
    info->previous_value = info->value;
    info->value = value;
    info->field14 = 0;

    work->field00 = 0;
    work->field04 = 0;
    work->field08 = 0;
    work->field0C = 0;
    work->field10 = 0;
    work->values = (u16*)(state + 0xC0);
    fn_80228B50(state + 0x2C0, state + 0xC0, 0, 0x100);

    for (i = 0; i < 0x100; i++) {
        ((u16*)(state + 0xC0))[i] = 0xFF;
    }

    lbl_8023D660.field2C = 0xFF;
    lbl_8023D660.field28 = 0;
}
