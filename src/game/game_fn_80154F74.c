typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;


typedef struct Entry {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    float value;
    int kind;
    u32 unk14;
} Entry;

typedef struct BatchHeader {
    u8 count;
    u8 pad1[0x13];
} BatchHeader;

typedef struct BatchBody {
    Entry* entries;
    float value;
    int kind;
    void* stamp;
    u16 indices[32];
    u16 index_count;
    u8 pad66;
    u8 flag;
    u8 tail[0x28];
} BatchBody;

extern void fn_801A1A4C(void*);
extern void* fn_8015E780(void);
extern void fn_801550C8();

void fn_80154F74(Entry* entries, u16 first, u16 last, int kind, int flag)
{
    BatchHeader header;
    BatchBody body;
    BatchBody* b = &body;
    int span;
    u32 index;
    void* stamp;
    float value;

    fn_801A1A4C(&header);
    b->kind = kind;
    b->pad66 = 0;
    b->index_count = 0;
    b->entries = entries;
    b->flag = flag;
    stamp = flag != 0 ? fn_8015E780() : 0;
    b->stamp = stamp;

    if (entries != 0) {
        value = entries->value;
        span = last - first;
        for (index = 0; (u16)index < span; index++) {
            Entry* entry = &entries[(u16)index];
            if (kind == entry->kind && value == entry->value) {
                b->indices[b->index_count] = index;
                b->index_count++;
                if (b->index_count >= 32) {
                    fn_80154F74(entry, index, span, kind, flag);
                    break;
                }
            } else if (kind == entry->kind) {
                fn_80154F74(entry, index, span, kind, flag);
                break;
            }
        }
        if (b->index_count != 0) {
            header.count = b->index_count;
            b->value = value / 72.0f;
            fn_801550C8(&header, flag);
        }
    }
}
