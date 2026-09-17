typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#pragma use_lmw_stmw on

typedef struct Entry {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    float value;
    int kind;
    u32 unk14;
} Entry;

typedef struct Batch {
    u8 count;
    u8 pad1[0x13];
    Entry* entries;
    float value;
    int kind;
    u32 stamp;
    u16 indices[32];
    u16 index_count;
    u8 pad66;
    u8 flag;
    u8 tail[0x20];
} Batch;

extern void fn_801A1A4C(Batch* batch);
extern u32 fn_8015E780(void);
extern void fn_801550C8(Batch* batch, int flag);

void fn_80154F74(Entry* entries, u16 first, u16 last, int kind, int flag)
{
    Batch batch;
    Batch* batch_ptr = &batch;
    int span;
    u16 index;
    u32 stamp;
    float value;

    fn_801A1A4C(batch_ptr);
    stamp = 0;
    batch.kind = kind;
    batch.pad66 = 0;
    batch.index_count = 0;
    batch.entries = entries;
    batch.flag = flag;
    if (flag != 0)
        stamp = fn_8015E780();
    batch.stamp = stamp;

    if (entries != 0) {
        value = entries->value;
        span = last - first;
        for (index = 0; index < span; index++) {
            Entry* entry = &entries[index];
            if (kind == entry->kind && value == entry->value) {
                batch.indices[batch.index_count] = index;
                batch.index_count++;
                if (batch.index_count >= 32) {
                    fn_80154F74(entry, index, span, kind, flag);
                    break;
                }
            } else if (kind == entry->kind) {
                fn_80154F74(entry, index, span, kind, flag);
                break;
            }
        }
        if (batch.index_count != 0) {
            batch.count = batch.index_count;
            batch.value = value / 72.0f;
            fn_801550C8(&batch, flag);
        }
    }
}
