typedef struct Pool {
    unsigned char data[0x320];
    unsigned char pad320[8];
    int environment;
    int object_id;
    int frame;
    unsigned char flags;
    unsigned char pad335[3];
} Pool;

typedef struct Slot {
    int index;
    int object_id;
    int start_frame;
    int last_frame;
    int count;
    unsigned char flags;
    unsigned char pad15[3];
} Slot;

extern Pool lbl_80320FD0[];
extern Slot lbl_80320DF0[];
extern int lbl_8064D5A8;
extern int lbl_8064D18C;
extern void *memset(void *dest, int value, unsigned long size);

void fn_800BD0F0(int index, int object_id)
{
    lbl_80320FD0[index].flags = 1;
    lbl_80320FD0[index].frame = lbl_8064D5A8;
    lbl_80320FD0[index].object_id = object_id;
    lbl_80320FD0[index].environment = lbl_8064D18C;
    memset(lbl_80320FD0[index].data, 0, 0x320);

    lbl_80320DF0[index].flags = 1;
    lbl_80320DF0[index].index = -1;
    lbl_80320DF0[index].count = 0;
    lbl_80320DF0[index].object_id = object_id;
    lbl_80320DF0[index].start_frame = lbl_8064D5A8;
    lbl_80320DF0[index].last_frame = lbl_8064D5A8;
}
