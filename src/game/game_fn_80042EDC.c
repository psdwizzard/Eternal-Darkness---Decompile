typedef short s16;
typedef struct Rec {
    s16 kind;
    s16 sub;
    int pad;
    void *ptr;
} Rec;

extern char lbl_80304060[];
extern int lbl_8064C7D0;
extern void fn_8020D250(void *, void *, int, void *, int, void *);

void fn_80042EDC(void) {
    Rec *rec = (Rec *)(lbl_80304060 + 0x78);
    void *buf = lbl_80304060 + 0x58;
    s16 *kind = (s16 *)lbl_80304060 + 0x3C;
    *kind = 5;
    rec->sub = 0;
    rec->ptr = buf;
    lbl_8064C7D0 += 1;
    fn_8020D250(lbl_80304060 + 0x2C, rec, 1, buf, 0, lbl_80304060);
}
