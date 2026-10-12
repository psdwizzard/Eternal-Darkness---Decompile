typedef struct CardInfo {
    unsigned char pad00[0x20];
    int size;
    unsigned char pad24[4];
    char gameCode[4];
    char companyCode[2];
} CardInfo;

typedef struct SaveCard SaveCard;

extern int fn_800B6908(void);
extern int fn_8017B1AC(int, void *);
extern void *fn_8017B9C4(int);
extern const char *fn_802161E0(void);
extern int fn_800FD1E8(const char *, const char *, unsigned long);
extern void fn_800B2548(int, int);
extern void fn_8017B8BC(int);
extern void fn_8017B96C(int);
extern void fn_800B261C(int);
extern void fn_800B2624(int, int, const char *, int, int);
extern void fn_800B4D5C(SaveCard *);
extern void fn_800B6234(int, int);

extern char lbl_80247434[];
extern int lbl_8064CA60;
extern int lbl_8064CA64;
extern int lbl_8064CA6C;

void fn_800BBCD4(int slot)
{
    int status;
    CardInfo *info;
    const char *discId;

    fn_800B6908();
    status = fn_8017B1AC(slot, lbl_80247434);
    lbl_8064CA6C = 0;
    if (status == 0) {
        info = fn_8017B9C4(slot);
        discId = fn_802161E0();
        if (fn_800FD1E8(info->gameCode, discId, 4) != 0 ||
            fn_800FD1E8(info->companyCode, discId + 4, 2) != 0) {
            fn_800B2548(0x42, slot);
            return;
        }
        if (((CardInfo *)fn_8017B9C4(slot))->size == 0x1E000) {
            fn_8017B8BC(0x2000);
            fn_8017B96C(0);
            fn_800B261C(1);
            lbl_8064CA64 = 1;
            lbl_8064CA60 = 0;
            fn_800B2624(7, slot, lbl_80247434, 0, (int)fn_800B4D5C);
            return;
        }
        fn_800B2548(0x17, slot);
        return;
    }
    fn_800B6234(slot, status);
}
