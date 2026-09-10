typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    u32 x;
    u32 y;
    u32 z;
} Vec3;

typedef struct Entry {
    u32 id;
    u8 pad04[0x29];
    u8 priority;
    u8 pad2E[0x32];
    Vec3 position;
    u8 pad6C[0x10];
} Entry;

extern Entry* lbl_8063EA00[12];
extern Vec3 lbl_8063F000;
extern int fn_801FD3E8(void);

Entry* fn_801FD3F8(u8 priority, u8 replace_equal)
{
    Entry* entry = 0;
    int i;

    for (i = 0; i < 12; i++) {
        u8 current_priority = lbl_8063EA00[i]->priority;
        if (current_priority < priority) {
            goto found;
        } else if (current_priority == priority) {
            if (replace_equal) {
                goto found;
            }
        }
        continue;
found:
        {
            int j;
            entry = lbl_8063EA00[11];
            for (j = 11; j > i; j--) {
                lbl_8063EA00[j] = lbl_8063EA00[j - 1];
            }
            entry->id = fn_801FD3E8();
            entry->position = lbl_8063F000;
            lbl_8063EA00[i] = entry;
            break;
        }
    }
    return entry;
}
