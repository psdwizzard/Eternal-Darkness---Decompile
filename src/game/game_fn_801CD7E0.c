typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Block { u16 values[80]; } Block;
typedef struct Queue {
    u8 entries[0x280];
    u8 write_index;
    volatile u8 count;
    u8 pad[0x282];
    u8 alternate_write_index;
    volatile u8 alternate_count;
} Queue;

extern Queue lbl_80630A30;
extern u32 lbl_8064D4E8, lbl_8064D4EC, lbl_8064D4F4;
extern u32 fn_8021AB5C(void), fn_8021AB64(void);
extern void* fn_801CE330(u32);
extern void fn_801CE358(void*), DCFlushRange(void*, u32);
extern void fn_801CD5D0(void*, u32, u32, u32, u32, u32);
extern void fn_801CDB2C(void);

void fn_801CD7E0(u32 duration)
{
    Queue* queue = &lbl_80630A30;
    u32 start;
    Block* allocation;
    Block* block;
    u32 i;

    start = fn_8021AB5C();
    allocation = fn_801CE330(0x500);
    block = allocation;
    for (i = 0; i < 8; i++) {
        block->values[0] = 0;
        block->values[1] = 0;
        block->values[2] = 0;
        block->values[3] = 0;
        block->values[4] = 0;
        block->values[5] = 0;
        block->values[6] = 0;
        block->values[7] = 0;
        block->values[8] = 0;
        block->values[9] = 0;
        block->values[10] = 0;
        block->values[11] = 0;
        block->values[12] = 0;
        block->values[13] = 0;
        block->values[14] = 0;
        block->values[15] = 0;
        block->values[16] = 0;
        block->values[17] = 0;
        block->values[18] = 0;
        block->values[19] = 0;
        block->values[20] = 0;
        block->values[21] = 0;
        block->values[22] = 0;
        block->values[23] = 0;
        block->values[24] = 0;
        block->values[25] = 0;
        block->values[26] = 0;
        block->values[27] = 0;
        block->values[28] = 0;
        block->values[29] = 0;
        block->values[30] = 0;
        block->values[31] = 0;
        block->values[32] = 0;
        block->values[33] = 0;
        block->values[34] = 0;
        block->values[35] = 0;
        block->values[36] = 0;
        block->values[37] = 0;
        block->values[38] = 0;
        block->values[39] = 0;
        block->values[40] = 0;
        block->values[41] = 0;
        block->values[42] = 0;
        block->values[43] = 0;
        block->values[44] = 0;
        block->values[45] = 0;
        block->values[46] = 0;
        block->values[47] = 0;
        block->values[48] = 0;
        block->values[49] = 0;
        block->values[50] = 0;
        block->values[51] = 0;
        block->values[52] = 0;
        block->values[53] = 0;
        block->values[54] = 0;
        block->values[55] = 0;
        block->values[56] = 0;
        block->values[57] = 0;
        block->values[58] = 0;
        block->values[59] = 0;
        block->values[60] = 0;
        block->values[61] = 0;
        block->values[62] = 0;
        block->values[63] = 0;
        block->values[64] = 0;
        block->values[65] = 0;
        block->values[66] = 0;
        block->values[67] = 0;
        block->values[68] = 0;
        block->values[69] = 0;
        block->values[70] = 0;
        block->values[71] = 0;
        block->values[72] = 0;
        block->values[73] = 0;
        block->values[74] = 0;
        block->values[75] = 0;
        block->values[76] = 0;
        block->values[77] = 0;
        block->values[78] = 0;
        block->values[79] = 0;
        block++;
    }
    DCFlushRange(allocation, 0x500);
    queue->count = 0;
    queue->write_index = 0;
    queue->alternate_count = 0;
    queue->alternate_write_index = 0;
    fn_801CD5D0(allocation, start, 0x500, 0, 0, 0);
    while (queue->count != 0) {
    }
    fn_801CE358(allocation);
    lbl_8064D4E8 = start + duration;
    if (lbl_8064D4E8 > fn_8021AB64()) {
        lbl_8064D4E8 = fn_8021AB64();
    }
    lbl_8064D4EC = start + 0x500;
    lbl_8064D4F4 = 0;
    fn_801CDB2C();
}

