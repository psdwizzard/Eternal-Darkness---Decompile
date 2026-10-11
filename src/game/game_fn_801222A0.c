typedef unsigned int u32;

typedef struct Entry {
    u32 a;
    u32 b;
    u32 c;
    u32 d;
} Entry;

typedef struct DisplayList {
    u32* data;
    u32 unk4;
    Entry* entries;
    int size;
    int count;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
} DisplayList;

extern DisplayList lbl_804ED5CC[2][64];
extern u32 lbl_8064CEDC[2];
extern int lbl_8064D738;
extern void fn_80121AE4(DisplayList* src, DisplayList* dst);

DisplayList* fn_801222A0(void* object, int kind, int mode, int value)
{
    int index = lbl_8064D738;
    int other_index = index ^ 1;
    int count = lbl_8064CEDC[index];
    int other_count = lbl_8064CEDC[other_index];
    DisplayList* current = lbl_804ED5CC[index];
    DisplayList* other = lbl_804ED5CC[other_index];
    DisplayList* result = 0;
    DisplayList* list = current;
    int i;

    /* Prefer a live display list already cached in this frame. */
    for (i = count; i > 0; --i, ++list) {
        if (list->unk4 == (u32)object && (int)list->unk14 == kind &&
            (int)list->unk18 == mode && list->data != 0 &&
            (int)list->unk1C == value) {
            return list;
        }
    }
    /* Copy a matching list from the other frame into the next free slot. */
    for (i = other_count; i > 0; --i, ++other) {
        if (other->unk4 == (u32)object && (int)other->unk14 == kind &&
            (int)other->unk18 == mode && other->data != 0 &&
            (int)other->unk1C == value) {
            DisplayList* destination = current + count;
            fn_80121AE4(other, destination);
            result = destination;
            break;
        }
    }
    ++lbl_8064CEDC[lbl_8064D738];
    if (result == 0) {
        list = lbl_804ED5CC[lbl_8064D738] + count;
        list->data = 0;
        result = list;
        list->unk18 = mode;
        list->unk14 = kind;
        list->unk4 = (u32)object;
        list->unk1C = value;
    }
    return result;
}
