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

extern GlobalState lbl_80302400;
extern DataState lbl_8023D660;

typedef struct TypeA TypeA;
typedef struct TypeB TypeB;
extern void fn_8020EFBC(TypeA*);
extern void fn_8020F0F8(TypeB*);
extern void fn_80228B50(void*, void*, s32, u32);

void fn_8001DFEC(u8 mode, u32 value)
{
    s32 i;
    Work* work;
    Info* info;
    GlobalState* state;

    state = &lbl_80302400;
    info = &state->info;
    work = &state->work;

    info->previous_mode = info->mode;
    info->previous_value = info->value;
    info->mode = mode;
    info->value = value;
    info->flags &= ~2U;
    fn_8020EFBC((TypeA*)state->object60);
    fn_8020F0F8((TypeB*)((u8*)info + 0x44));

    work->field00 = 0;
    work->values = state->values;
    work->field04 = 0;
    work->field08 = 0;
    work->field0C = 0;
    work->field10 = 0;
    fn_80228B50(state->clear, state->values, 0, sizeof(state->clear));

    for (i = 0; i < 0x100; i++) {
        state->values[i] = 0xFF;
    }

    lbl_8023D660.field2C = 0xFF;
    lbl_8023D660.field28 = 0;
}
