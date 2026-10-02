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
    u8 pad18[0x10];
} Work;

extern DataState lbl_8023D660;

extern void fn_8020EFBC(void*);
extern void fn_8020F0F8(void*);
extern void fn_80228B50(void*, void*, s32, u32);

static u8 head[0x1C] = {0};
static Info info = {0};
static u8 object[0x38] = {0};
static Work work = {0};
static u16 values[0x100] = {0};
static u8 clear[0x100] = {0};

void fn_8001DE84(u8 mode, u32 value)
{
    s32 i;

    info.flags &= ~2U;
    fn_8020EFBC(object);
    fn_8020F0F8(object);

    info.previous_mode = info.mode;
    info.mode = mode;
    info.previous_value = info.value;
    info.value = value;
    info.field14 = 0;

    work.field00 = 0;
    work.field04 = 0;
    work.field08 = 0;
    work.field0C = 0;
    work.field10 = 0;
    work.values = values;
    fn_80228B50(clear, values, 0, sizeof(clear));

    for (i = 0; i < 0x100; i++) {
        values[i] = 0xFF;
    }

    lbl_8023D660.field2C = 0xFF;
    lbl_8023D660.field28 = 0;
}
