typedef unsigned char u8;

typedef struct Entry802014F0 {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
    int unk10;
    u8 pad14[8];
    int unk1C;
    u8 unk20;
    u8 pad21[0x17];
    int unk38;
} Entry802014F0;

extern char lbl_802FC944[];
extern void *lbl_8064D880;
extern int lbl_8064D888;
extern int lbl_8064D88C;
extern int lbl_8064D890;
extern int lbl_8064D894;
extern int lbl_8064D898;
extern int lbl_8064D89C;
extern int lbl_8064D8A0;
extern Entry802014F0 *volatile lbl_8064D8A4;

extern void *fn_801FEA8C(unsigned int, int, const char *, int);
extern void *fn_8017CCD8(void *, unsigned int, unsigned int);
extern void *fn_8017CDB4(void *);

void fn_802014F0(int mode)
{
    Entry802014F0 *entry;

    if (mode == 0) {
        void *storage = fn_801FEA8C(0x4524, 1, lbl_802FC944, 0xF3);
        lbl_8064D880 = fn_8017CCD8(storage, 0x3C, 0x127);
    }

    entry = lbl_8064D8A4 = fn_8017CDB4(lbl_8064D880);
    entry->unk4 = 0;
    lbl_8064D8A4->unk0 = 0;
    lbl_8064D8A4->unk10 = 0;
    lbl_8064D8A4->unk8 = 0;
    lbl_8064D8A4->unk1C = 1;
    lbl_8064D8A4->unk20 = 0;
    lbl_8064D8A4->unk38 = -1;
    lbl_8064D888 = 0;
    lbl_8064D88C = 0;
    lbl_8064D890 = 0;
    lbl_8064D894 = 0;
    lbl_8064D89C = 0;
    lbl_8064D8A0 = 0;
    lbl_8064D898 = 0;
}
