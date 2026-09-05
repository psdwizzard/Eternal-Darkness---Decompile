typedef unsigned char u8;

typedef struct Queue {
    u8 entries[0x280];
    u8 write_index;
    volatile u8 count;
} Queue;

extern Queue lbl_80630A30;

void fn_801CD7C8(void)
{
    while (lbl_80630A30.count != 0) {
    }
}
