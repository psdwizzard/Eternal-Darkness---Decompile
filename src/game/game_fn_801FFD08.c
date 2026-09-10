typedef unsigned int u32;

typedef struct SceneHeader {
    int values[16];
} SceneHeader;

extern int lbl_8064D7D8;
extern u32 lbl_8064D7E0[2];
extern void* lbl_8064D810[2];
extern void* lbl_8064D828[2];
extern void* lbl_8064D830[2];
extern void* lbl_8064D838[2];
extern void* lbl_8064D840[2];
extern void* lbl_8064D848[2];
extern void* lbl_8064D850[2];

extern void fn_801FEB54(int, int, int, int, int, int);
extern void fn_801FEE10(void*, int, void*, void*, void*);
extern void fn_801FEE98(void*, int, void*, void*, void*);
extern void fn_801FEF20(void*, int, void*, void*, void*);
extern void fn_801FEF90(void*, int, void*, void*, void*);
extern void fn_801FF008(SceneHeader*, void*);
extern void fn_801FF9A0(void);
extern void* memcpy(void*, const void*, unsigned long);

void fn_801FFD08(SceneHeader* header)
{
    int other = lbl_8064D7D8 ^ 1;

    fn_801FEB54(lbl_8064D7D8, header->values[10], header->values[2],
                header->values[13], header->values[0], header->values[7]);
    fn_801FEE10((void*)header->values[11], header->values[10],
                lbl_8064D850[other], lbl_8064D850[lbl_8064D7D8],
                (void*)header->values[12]);
    fn_801FEE98((void*)header->values[14], header->values[13],
                lbl_8064D830[other], lbl_8064D830[lbl_8064D7D8],
                (void*)header->values[15]);
    fn_801FEF20((void*)header->values[3], header->values[2],
                lbl_8064D848[other], lbl_8064D848[lbl_8064D7D8],
                (void*)header->values[6]);
    fn_801FEF90((void*)header->values[8], header->values[7],
                lbl_8064D828[other], lbl_8064D828[lbl_8064D7D8],
                (void*)header->values[9]);

    memcpy(lbl_8064D840[lbl_8064D7D8], (void*)header->values[4],
           (header->values[2] >> 3) + ((header->values[2] & 7) > 0));
    memcpy(lbl_8064D838[lbl_8064D7D8], (void*)header->values[5],
           header->values[2]);
    fn_801FF008(header, lbl_8064D810[lbl_8064D7D8]);
    lbl_8064D7E0[lbl_8064D7D8] = header->values[0];
    lbl_8064D7D8 = lbl_8064D7D8 ^ 1;
    fn_801FF9A0();
}
