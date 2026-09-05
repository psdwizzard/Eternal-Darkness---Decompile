typedef unsigned int u32;
typedef unsigned char u8;

typedef struct HeapEntry HeapEntry;
struct HeapEntry {
    HeapEntry* next;
    u32 value;
    u32 size;
    u32 allocation_size;
};

extern HeapEntry lbl_80630F38[];
extern HeapEntry* lbl_8064D500;
extern HeapEntry* lbl_8064D504;
extern HeapEntry* lbl_8064D508;
extern u32 lbl_8064D4E8;
extern u32 lbl_8064D4EC;
extern u32 lbl_8064D4F0;

u8 fn_801CDBF4(u32 size)
{
    HeapEntry* selected = 0;
    HeapEntry* entry = lbl_8064D504;
    HeapEntry* previous = 0;
    u32 best_size = -1;
    u32 rounded = (size + 31) & ~31;

    while (entry != 0) {
        if (entry->allocation_size == rounded) {
            selected = entry;
            break;
        }
        if (entry->allocation_size > rounded && best_size > entry->allocation_size) {
            selected = entry;
            best_size = entry->allocation_size;
        }
        previous = entry;
        entry = entry->next;
    }

    if (selected == 0) {
        entry = lbl_8064D508;
        if (entry != 0 && lbl_8064D4F0 - rounded >= lbl_8064D4EC) {
            lbl_8064D508 = entry->next;
            selected = entry;
            entry->allocation_size = rounded;
            entry->size = rounded;
            lbl_8064D4F0 -= rounded;
            entry->value = lbl_8064D4F0;
            entry->next = lbl_8064D500;
            lbl_8064D500 = entry;
        }
    } else {
        if (previous != 0) {
            previous->next = selected->next;
        } else {
            lbl_8064D504 = selected->next;
        }
        selected->size = rounded;
        selected->next = lbl_8064D500;
        lbl_8064D500 = selected;
    }

    if (selected == 0) {
        return 255;
    }
    return selected - lbl_80630F38;
}
