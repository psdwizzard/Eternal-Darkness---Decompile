typedef unsigned char u8;
typedef struct Pools {
    u8 slots[0xF0];
    u8 work[0x24C0];
    u8 quads[0x7E0];
} Pools;
extern Pools lbl_805B1310;
extern u8 lbl_8064D038;
extern void* memset(void*, int, unsigned int);

void fn_80142944(void)
{
    u8* pools = (u8*)&lbl_805B1310;
    /* NonMatching: the running pointer recovers retail's r31 allocation and
     * all three pool offsets. GC/1.3 emits mr r3,r31 for the first call where
     * retail uses the equivalent addi r3,r31,0. */
    memset(pools, 0, 0xF0);
    pools += 0xF0;
    memset(pools, 0, 0x24C0);
    pools += 0x24C0;
    memset(pools, 0, 0x7E0);
    lbl_8064D038 = 0;
}
