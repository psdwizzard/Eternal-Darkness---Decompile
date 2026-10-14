typedef struct CodecEntry {
    void *unk0;
    void *model;
    char pad8[0x18];
    void *actor;
    void *owner;
    int unk28;
} Slot;

/* banks: 0 = previous, 1 = current, 2 = previous shadow, 3 = shadow. */
typedef struct SlotTable {
    Slot banks[4][6];
    Slot extra[32];
    int panels[5];
} SlotTable;

typedef struct FadeState {
    char pad0[0x80];
    int color;
    int unk84;
    char pad88[0xA];
    short unk92;
    int unk94;
    int unk98;
} FadeState;

extern FadeState lbl_8024B3E4;
extern unsigned char lbl_80330D80[];
extern unsigned char lbl_80332140[];
extern void *lbl_8064C4E0;
extern short lbl_8064CCAC;
extern int lbl_8064CCC4;
extern int lbl_8064CCC8;
extern int lbl_8064CCCC;
extern int lbl_8064CCD0;
extern int lbl_8064CCD4;
extern int lbl_8064CCD8;
extern int lbl_8064CCE0;
extern void *lbl_8064CD88;
extern void *lbl_8064CD8C;
extern int lbl_8064CDB0;
extern int lbl_8064CDB4;
extern void *lbl_8064CDC0;

extern void *memset(void *, int, unsigned long);
extern void *fn_80144628(int, void *, int);
extern void fn_801446D4(void *, void (*)(void));
extern int fn_8010A32C(int, int, int);
extern void fn_8010ACF8(void);
extern void fn_8010CCD0(void);
extern void fn_8016B400(int, int, int);
extern void fn_801E5FB0(int);
extern int fn_801E79FC(void *, int);
extern int fn_801E8A8C(void);
extern void fn_801E8AEC(int, int, int, int);
extern void fn_801E8B10(int, int, int, void (*)(void), void (*)(void));

extern void fn_8010B704(void);
extern void fn_8010E448(void);
extern void fn_8010BFF0(void);
extern void fn_8010B33C(void);
extern void fn_8010B398(void);
extern void fn_8010B194(void);
extern void fn_8010B400(void);
extern void fn_8010B45C(void);
extern void fn_80118080(void);

void fn_8010AD7C(void)
{
    SlotTable *table = (SlotTable *)lbl_80330D80;
    int *panel;
    int i;

    lbl_8024B3E4.color = 0x600C0000;
    lbl_8024B3E4.unk84 = 0;
    lbl_8024B3E4.unk92 = -1;
    lbl_8024B3E4.unk94 = 30;
    lbl_8024B3E4.unk98 = 20;
    fn_801446D4(lbl_8064CDC0 = fn_80144628(11, &lbl_8024B3E4, 0), fn_8010B704);
    lbl_8064CD8C = fn_8010E448;
    lbl_8064CD88 = fn_8010BFF0;
    lbl_8064CCE0 = 0;
    lbl_8064CCD8 = 0;
    lbl_8064CCAC = 0;
    lbl_8064CCCC = 0;
    memset(table->banks[1], 0, sizeof(table->banks[1]));
    memset(table->banks[3], 0, sizeof(table->banks[3]));
    memset(table->banks[0], 0, sizeof(table->banks[0]));
    memset(table->panels, 0, sizeof(table->panels));
    lbl_8064CCC4 = fn_8010A32C(0, 0, 6);
    fn_801E5FB0(lbl_8064CCC8);
    lbl_8064CCC8 = 0;
    *(int *)(lbl_80332140 + 0x14) = 0;
    lbl_8064CCD4 = 0;

    panel = table->panels;
    for (i = 0; i < 5; i++) {
        *panel++ = fn_801E8A8C();
    }

    fn_801E8AEC(table->panels[0], 0, 2, 2);
    fn_801E8AEC(table->panels[1], 0, (lbl_8064CCC4 + 1) / 2, 3);
    fn_801E8AEC(table->panels[2], 0, 5, 5);
    fn_801E8AEC(table->panels[3], 0, 2, 2);
    fn_801E8AEC(table->panels[4], 0, (lbl_8064CCC4 + 1) / 2, 3);

    fn_801E8B10(table->panels[0], 1, 0, fn_8010B33C, fn_80118080);
    fn_801E8B10(table->panels[1], 1, 0, fn_8010B398, fn_80118080);
    fn_801E8B10(table->panels[2], 1, 0, fn_8010B194, fn_80118080);
    fn_801E8B10(table->panels[3], 1, 0, fn_8010B400, fn_80118080);
    fn_801E8B10(table->panels[4], 1, 0, fn_8010B45C, fn_80118080);

    fn_801E5FB0(lbl_8064CDB0);
    lbl_8064CDB4 = 0;
    fn_801E5FB0(0);
    lbl_8064CDB0 = 0;
    fn_8010ACF8();

    if (fn_801E79FC(lbl_8064C4E0, 0x2B6) && !fn_801E79FC(lbl_8064C4E0, 0x360)) {
        fn_8016B400(0x1E0, 0, 0);
        lbl_8064CCD0 = 2;
    } else if (!fn_801E79FC(lbl_8064C4E0, 0x1E2)) {
        fn_8016B400(0x7BB, 0, 0);
        lbl_8064CCD0 = 2;
    } else if (fn_801E79FC(lbl_8064C4E0, 0x2CC) && !fn_801E79FC(lbl_8064C4E0, 0x2CD)) {
        fn_8016B400(0x2B6, 0, 0);
        lbl_8064CCD0 = 2;
    } else if (fn_801E79FC(lbl_8064C4E0, 0x257) && !fn_801E79FC(lbl_8064C4E0, 0x258)) {
        fn_8016B400(0x335, 0, 0);
        lbl_8064CCD0 = 2;
    } else if (fn_801E79FC(lbl_8064C4E0, 0x259) && !fn_801E79FC(lbl_8064C4E0, 0x25A)) {
        fn_8016B400(0x361, 0, 0);
        lbl_8064CCD0 = 2;
    } else if (fn_801E79FC(lbl_8064C4E0, 0x25B) && !fn_801E79FC(lbl_8064C4E0, 0x25C)) {
        fn_8016B400(0x337, 0, 0);
        lbl_8064CCD0 = 2;
    } else {
        fn_8010CCD0();
    }
}
