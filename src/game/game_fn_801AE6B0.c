typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry Entry;
struct Entry {
    u8 state;
    u8 type;
    u8 channels;
    u8 rate;
    u8 padding04[4];
    Entry* first;
    Entry* second;
    void* header;
    u8 lock[60];
    void* stream;
    u8 padding54[16];
    u32 buffer_size;
    u8 alternate_half;
    u8 padding69;
    u8 phase;
    u8 padding6B[9];
    u32 active;
    int pending;
    u8 padding7C[8];
};

extern Entry lbl_8060B430[4];
extern void fn_8021345C(void*);
extern int fn_80215C34(void*);
extern int fn_801AE5DC(Entry*);
extern void fn_801B9E7C(void*, u32, u32, u32, u32);
extern void fn_801BB3A0(void*);

void fn_801AE6B0(u32 unused, void* lock)
{
    u32 index = 0;
    Entry* entry = &lbl_8060B430[0];

    for (; index < 3; index++) {
        if ((void*)entry->lock == lock) {
            break;
        }
        entry++;
    }

    entry = &lbl_8060B430[index];
    entry->active = 0;
    if (entry->pending != 0) {
        entry->pending = 0;
        fn_8021345C(entry->lock);
        entry->state = 0;
        return;
    }

    if (fn_80215C34(lock) == 0) {
        switch (entry->state) {
        case 2:
            if (entry->first != 0) {
                if (entry->first->state != 3) {
                    entry->state = 3;
                    break;
                }
                if (entry->phase == 2) {
                    entry->first->phase = 3;
                    entry->phase = 3;
                    entry->state = 5;
                    break;
                }
                if (fn_801AE5DC(entry->first) == 0) {
                    entry->first = 0;
                }
            }
            if (entry->second != 0) {
                if (entry->second->state != 3) {
                    entry->state = 3;
                    break;
                }
                if (entry->phase == 2) {
                    entry->second->phase = 3;
                    entry->phase = 3;
                    entry->state = 5;
                    break;
                }
                if (fn_801AE5DC(entry->second) == 0) {
                    entry->second = 0;
                }
            }
            if (entry->phase == 2) {
                entry->phase = 3;
                entry->state = 5;
                break;
            }
            if (fn_801AE5DC(entry) == 0) {
                if (entry->first != 0) {
                    entry->first->second = 0;
                }
                if (entry->second != 0) {
                    entry->second->first = 0;
                }
            }
            break;
        case 4:
            fn_801B9E7C(entry->stream,
                        entry->alternate_half != 0 ? 0 : entry->buffer_size >> 1,
                        entry->buffer_size >> 1, 0, 0);
            break;
        case 5:
            break;
        }
    } else {
        if (entry->state == 4) {
            fn_801BB3A0(entry->stream);
        }
        fn_8021345C(entry->lock);
        entry->state = 0;
        if (entry->first != 0) {
            entry->first->second = 0;
        }
        if (entry->second != 0) {
            entry->second->first = 0;
        }
    }
}
