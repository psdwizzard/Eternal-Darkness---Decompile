extern void* memset(void*, int, unsigned int);

typedef struct Entry {
    int field0;
    int field4;
    int field8;
    int fieldC;
    int state;
    int owner;
    int field18;
    unsigned int flags;
} Entry;

extern Entry lbl_805B4170[20];

void fn_80144F8C(void)
{
    Entry* entry = lbl_805B4170;
    Entry* end = lbl_805B4170 + 20;
    for (; entry < end; entry++) {
        if (entry->flags & 1) {
            memset(entry, 0, sizeof(*entry));
            entry->state = -2;
        }
    }
}
