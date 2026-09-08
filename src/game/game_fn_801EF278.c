typedef struct CommandEntry {
    int value0;
    int pad4;
    int value8;
    int valueC;
    int value10;
    int value14;
    int value18;
} CommandEntry;

extern int lbl_8064D630;
extern CommandEntry lbl_8063BC98[];

void fn_801EF278(int value0, int value8, int valueC, int value10, int value18,
                 int value14)
{
    int index = lbl_8064D630++;
    lbl_8063BC98[index].value0 = value0;
    lbl_8063BC98[index].value8 = value8;
    lbl_8063BC98[index].valueC = valueC;
    lbl_8063BC98[index].value10 = value10;
    lbl_8063BC98[index].value14 = value14;
    lbl_8063BC98[index].value18 = value18;
}
