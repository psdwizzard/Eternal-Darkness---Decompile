typedef unsigned char u8;

typedef struct DisplayEntry {
    void* display_list;
    void* object;
} DisplayEntry;

extern void GXSetTexCoordGen2(int, int, int, int, int, int);

static DisplayEntry display_entries[0x400] = {0};
static u8 lbl_8063B260[0x40] = {0};
static u8 lbl_8063B2A0[0xC] = {0};
static u8 lbl_8063B2AC[0xC] = {0};
static u8 lbl_8063B2B8[0xC] = {0};
static u8 lbl_8063B2C4[0xC] = {0};
static u8 lbl_8063B2D0[0x2C] = {0};
static u8 lbl_8063B2FC[0x20] = {0};
static u8 lbl_8063B31C[0x40] = {0};
static u8 lbl_8063B35C[0x18] = {0};
static u8 lbl_8063B374[0x18] = {0};
static u8 lbl_8063B38C[0x18] = {0};
static u8 lbl_8063B3A4[0x38] = {0};
static u8 lbl_8063B3DC[0x50] = {0};
static u8 lbl_8063B42C[0x6C] = {0};
static u8 lbl_8063B498[0x80] = {0};
static int lbl_8063B518[16] = {0};
static int values0[16] = {0};
static int values1[16] = {0};
static int values2[16] = {0};

void fn_801EDEC4(int index, int value0, int value1, int value2)
{
    if (values1[index] != value1 || value0 != values0[index] ||
        value2 != values2[index]) {
        GXSetTexCoordGen2(index, value0, value1, value2, 0, 125);
        values1[index] = value1;
        values0[index] = value0;
        values2[index] = value2;
    }
}
