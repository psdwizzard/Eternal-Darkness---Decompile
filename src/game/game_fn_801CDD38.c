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
extern u32 lbl_8064D4F0;

void fn_801CDD38(u8 index)
{
    HeapEntry* target = &lbl_80630F38[index];
    HeapEntry* entry = lbl_8064D500;
    HeapEntry* previous = 0;

    while (entry != 0) {
        if (entry == target) {
            if (previous != 0) {
                previous->next = target->next;
            } else {
                lbl_8064D500 = target->next;
            }
            break;
        }
        previous = entry;
        entry = entry->next;
    }

    if (target->value == lbl_8064D4F0) {
        u32 lowest = -1;

        target->next = lbl_8064D508;
        lbl_8064D508 = target;

        entry = lbl_8064D500;
        while (entry != 0) {
            if (entry->value <= lowest) {
                lowest = entry->value;
            }
            entry = entry->next;
        }

        {
            HeapEntry* next;
            HeapEntry* current = lbl_8064D504;
            while (current != 0) {
                next = current->next;
                if (current->value < lowest) {
                    lbl_8064D504 = next;
                    current->next = lbl_8064D508;
                    lbl_8064D508 = current;
                }
                current = next;
            }
        }

        lbl_8064D4F0 = lowest != -1 ? lowest : lbl_8064D4E8;
    } else {
        target->next = lbl_8064D504;
        lbl_8064D504 = target;
    }
}
