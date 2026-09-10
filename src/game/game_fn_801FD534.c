typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u32 id;
    u8 data[0x78];
} Entry;

extern Entry* lbl_8063EA00[12];
extern void* memset(void*, int, unsigned int);

void fn_801FD534(u32 id)
{
    Entry* entry;
    int i;

    for (i = 0; i < 12; i++) {
        entry = lbl_8063EA00[i];
        if (entry->id == id) {
            int j;
            memset(entry, 0, sizeof(Entry));
            for (j = i; j < 11; j++) {
                lbl_8063EA00[j] = lbl_8063EA00[j + 1];
            }
            lbl_8063EA00[11] = entry;
            break;
        }
    }
}
