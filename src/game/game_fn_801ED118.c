typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;

extern u8 lbl_80639260[];
extern s32 lbl_8064D634;
extern s32 lbl_8064D63C;
extern s32 lbl_8064D680;
extern s32 lbl_8064D684;
extern s32 lbl_8064D6B0;

typedef struct Record16 {
    s32 value[4];
} Record16;

typedef struct Record24 {
    s32 pad0; /* Preserved when the rest of the record is invalidated. */
    s32 a;
    s32 b;
    s32 c;
    u8 flag;
    u8 pad11[3];
    s32 d;
} Record24;

typedef struct Record8 {
    s32 a;
    s32 b;
} Record8;

void fn_801ED118(void)
{
    register u8* high;
    register s16* half;
    register s32* word;
    s32 i;

    lbl_8064D634 = -1;
    /* ASM: lis and addi bind the pooled BSS base to r30; C allocates a volatile
     * register and folds the base into individual array accesses. */
    asm {
        lis high, lbl_80639260@ha
        addi r30, high, lbl_80639260@l
    }
    /* ASM: addi retains the two array bases instead of folding them into the stores. */
    asm {
        addi half, r30, 0x21D8
        addi word, r30, 0x21F8
    }
    for (i = 0; i < 11; i++) {
        half[i] = -1;
        word[i] = -1;
    }

    {
        register s32* h;
        register s32* g;
        register s32* f;
        register s32* e;
        register s32* d;
        register s32* c;
        register s32* z;
        register s32* a;
        register s32 empty;
        register s32* count;
        s32* b;
        register s32 zero;
        Record16* r16a;
        Record16* r16b;
        Record24* r24a;
        Record24* r24b;
        Record8* r8;

        /* ASM: li keeps this sentinel separate; C merges it with the first
         * loop's constant and changes the working-register allocation. */
        asm { li empty, -1 }
        /* ASM: addi retains the parallel array bases; C folds these offsets
         * into the unrolled stores instead of retaining the cursors. */
        asm {
            addi a, r30, 0x2238
            addi c, r30, 0x22F8
            addi d, r30, 0x2338
            addi e, r30, 0x2378
            addi f, r30, 0x2938
            addi g, r30, 0x2978
            addi h, r30, 0x29B8
        }
        /* ASM: li and addi keep zero and the state-array base independent;
         * C constant/address folding changes their register lifetimes. */
        asm {
            li zero, 0
            addi z, r30, 0x2278
        }
        /* ASM: addi and mr retain the header cursor; C otherwise folds the
         * count store into a direct BSS-relative access. */
        asm { addi count, r30, 0x21D8; mr count, count }
        count[6] = zero;
        lbl_8064D63C = zero;
        r16a = (Record16*)((u8*)a + 0x180);
        b = a + 0x80 / sizeof(s32);
        r16b = (Record16*)((u8*)a + 0x280);
        r24a = (Record24*)((u8*)a + 0x380);
        r24b = (Record24*)((u8*)a + 0x500);
        r8 = (Record8*)((u8*)a + 0x680);
        for (i = 0; i < 8; i++) {
            *a++ = empty;
            *z++ = zero;
            *c++ = empty;
            *d++ = empty;
            *e++ = empty;
            *f++ = empty;
            *g++ = empty;
            *h++ = empty;
        }

        for (i = 0; i < 16; i++) {
            r24a->a = -1;
            r24b->a = -1;
            r16a->value[0] = -1;
            r16b->value[0] = -1;
            r24a->b = -1;
            r24b->b = -1;
            r16a->value[1] = -1;
            r16b->value[1] = -1;
            r24a->c = -1;
            r24b->c = -1;
            r16a->value[2] = -1;
            r16b->value[2] = -1;
            r24a->flag = 255;
            r24b->flag = 255;
            r8->a = -1;
            *b++ = -1;
            r16a->value[3] = -1;
            r16b->value[3] = -1;
            r24a->d = -1;
            r24b->d = -1;
            r8->b = -1;
            r16a++;
            r16b++;
            r24a++;
            r24b++;
            r8++;
        }
    }
    /* Preserve the order of the final array and global invalidation stores. */
    for (i = 0; i < 16; i++) {
        ((volatile s32*)(lbl_80639260 + 0x29F8))[i] = -1;
    }
    *(volatile s32*)&lbl_8064D6B0 = -1;
    *(volatile s32*)&lbl_8064D684 = 0;
    *(volatile s32*)&lbl_8064D680 = 0;
}
