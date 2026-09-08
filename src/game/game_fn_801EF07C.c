typedef unsigned char u8;

typedef struct CommandCache5 {
    int pad0;
    int value4;
    int value8;
    int valueC;
    u8 value10;
    u8 pad11[3];
    int value14;
} CommandCache5;

extern CommandCache5 lbl_8063B818[];
extern void fn_80229C0C(int, int, int, int, int, int);

void fn_801EF07C(int index, int value4, int value8, int valueC, int value10,
                 int value14)
{
    if (lbl_8063B818[index].value4 != value4 ||
        lbl_8063B818[index].value8 != value8 ||
        lbl_8063B818[index].valueC != valueC ||
        lbl_8063B818[index].value10 != (u8)value10 ||
        lbl_8063B818[index].value14 != value14) {
        lbl_8063B818[index].value4 = value4;
        lbl_8063B818[index].value8 = value8;
        lbl_8063B818[index].valueC = valueC;
        lbl_8063B818[index].value10 = value10;
        lbl_8063B818[index].value14 = value14;
        fn_80229C0C(index, value4, value8, valueC, value10, value14);
    }
}
