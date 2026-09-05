typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u32 field_0;
    u32 field_4;
    u32 field_8;
    u32 field_C;
    u32 field_10;
    u32 field_14;
    u32 field_18;
    void (*callback)(void*);
    u32 field_20;
    u32 field_24;
} Entry;

typedef struct Queue {
    Entry entries[16];
    volatile u8 write_index;
    volatile u8 count;
} Queue;

extern Queue lbl_80630A30;
extern Queue lbl_80630CB4;
extern void (*lbl_8064D4FC)(void*);
extern void fn_801CD46C(void*);
extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);
extern void fn_8021B730(void*, u32, u32, u32, u32, u32, u32, void*);

void fn_801CD5D0(u32 field_10, u32 field_14, u32 field_18, u32 alternate,
                 u32 field_20, u32 field_24)
{
    Queue* queue;
    u32 enabled;
    u32 alternate_flag;

    queue = alternate != 0 ? &lbl_80630CB4 : &lbl_80630A30;
    for (;;) {
        enabled = OSDisableInterrupts();
        if (queue->count < 16) {
            queue->entries[queue->write_index].field_4 = 42;
            queue->entries[queue->write_index].field_8 = alternate_flag = 0;
            if (alternate != 0) {
                alternate_flag = 1;
            }
            queue->entries[queue->write_index].field_C = alternate_flag;
            queue->entries[queue->write_index].field_10 = field_10;
            queue->entries[queue->write_index].field_14 = field_14;
            queue->entries[queue->write_index].field_18 = field_18;
            queue->entries[queue->write_index].callback = fn_801CD46C;
            queue->entries[queue->write_index].field_20 = field_20;
            queue->entries[queue->write_index].field_24 = field_24;

            if (lbl_8064D4FC != 0) {
                lbl_8064D4FC(&queue->entries[queue->write_index]);
            } else {
                fn_8021B730(&queue->entries[queue->write_index],
                             queue->entries[queue->write_index].field_4,
                             queue->entries[queue->write_index].field_8,
                             queue->entries[queue->write_index].field_C,
                             queue->entries[queue->write_index].field_10,
                             queue->entries[queue->write_index].field_14,
                             queue->entries[queue->write_index].field_18,
                             queue->entries[queue->write_index].callback);
            }

            queue->count++;
            queue->write_index = (queue->write_index + 1) % 16;
            OSRestoreInterrupts(enabled);
            break;
        }
        OSRestoreInterrupts(enabled);
    }
}
