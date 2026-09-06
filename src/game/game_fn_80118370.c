extern void fn_8021345C(void *);
extern void *lbl_8064CD90;
extern void fn_801E85A8(void *);
extern void *fn_801E86A0(void *, int);
extern void *lbl_8064CD80;
extern void *lbl_8064CDE4;
extern unsigned char *lbl_8064C51C;
extern unsigned char *lbl_8064C5CC;
extern void fn_8015DAB0(void *);
extern int lbl_8064D184;
extern volatile unsigned int lbl_8064CDE0;
extern volatile int lbl_8064CDA0;
extern int lbl_8064CDA8;
extern void *lbl_8064D158;
extern unsigned int fn_801E7998(void *);
extern unsigned char lbl_8024E3A4[];
extern void fn_800F9D4C(char *, const char *, ...);
extern unsigned int lbl_8064CD74;
extern unsigned char lbl_8033231C[];
extern void fn_80213394(void *, void *);
extern void *lbl_8064CD84;
extern int fn_80213704(void *, void *, unsigned int, int, void (*)(int, void *), int);
extern void fn_80118288(int, void *);

void fn_80118370(int value, void *resource)
{
    struct Entry {
        unsigned char pad[8];
        signed char value;
        unsigned char tail[3];
    };
    char name[8];

    if (value >= 0) {
        if (resource != 0) {
            fn_8021345C(resource);
        }
        fn_801E85A8(lbl_8064CD90);
        lbl_8064CD80 = fn_801E86A0(lbl_8064CD90, 0);
        lbl_8064CDE4 = fn_801E86A0(lbl_8064CD90, 1);
        lbl_8064C51C = fn_801E86A0(lbl_8064CD90, 2);
        lbl_8064C5CC = fn_801E86A0(lbl_8064CD90, 3);
        fn_801E85A8(lbl_8064C51C);
        fn_801E85A8(lbl_8064C5CC);
        fn_8015DAB0(lbl_8064CD80);

        lbl_8064CDE0 = 0;
        lbl_8064CDA0 = 1;
        lbl_8064CDA8 = 1;
        if (lbl_8064D184 >= 0 &&
            (unsigned int)lbl_8064D184 < fn_801E7998(lbl_8064D158)) {
            struct Entry *slot = (struct Entry *)lbl_8064CDE4;
            int entry = slot[lbl_8064D184].value;
            if (entry > 0 && entry < 16) {
                fn_800F9D4C(name, (const char *)lbl_8024E3A4, entry);
                lbl_8064CDE0 = (unsigned int)lbl_8064CD90 +
                               ((lbl_8064CD74 + 0x1F) & ~0x1F);
                fn_80213394(name, lbl_8033231C);
                lbl_8064CD84 = (unsigned char *)lbl_8064CDE0 +
                                ((*(unsigned int *)(lbl_8033231C + 0x34) + 0x1F) & ~0x1F);
                while (fn_80213704(lbl_8033231C, (void *)lbl_8064CDE0,
                                   (*(unsigned int *)(lbl_8033231C + 0x34) + 0x1F) & ~0x1F,
                                   0, fn_80118288, 2) == 0) {
                }
            }
        }
        if (lbl_8064CDE0 == 0) {
            lbl_8064CD84 = (unsigned char *)lbl_8064CD90 +
                            ((lbl_8064CD74 + 0x1F) & ~0x1F);
            fn_80118288(0, 0);
        }
    }
}
