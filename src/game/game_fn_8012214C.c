typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u32 a, b, c, d;
} Entry;

typedef struct DisplayList {
    u32* data;
    u32 unk4;
    Entry* entries;
    int size;
    int count;
    u32 unk14, unk18, unk1C;
} DisplayList;

typedef struct TransferState {
    void* source;
    void* destination;
    u16 count;
    u16 pad;
    int remaining;
    u32 transferred;
    u32 unk14;
    int size;
} TransferState;

extern DisplayList lbl_804ED5CC[2][64];
extern u32 lbl_8064CEDC[2];
extern int lbl_8064D738;
extern TransferState fn_80121FCC(DisplayList* src, DisplayList* dst);
extern void* memset(void* dst, int value, unsigned long size);

int fn_8012214C(void* object, int kind, int mode, TransferState* state)
{
    int index = lbl_8064D738;
    int other_index = index ^ 1;
    int count = lbl_8064CEDC[index];
    int other_count = lbl_8064CEDC[other_index];
    DisplayList* other = lbl_804ED5CC[other_index];
    DisplayList* current = lbl_804ED5CC[index];
    DisplayList* list = current;
    int i;

    for (i = count; i > 0; --i, ++list) {
        if (list->unk4 == (u32)object && (int)list->unk14 == kind &&
            (int)list->unk18 == mode && list->data != 0) {
            memset(state, 0, sizeof(*state));
            return 0;
        }
    }
    for (i = other_count; i > 0; --i, ++other) {
        if (other->unk4 == (u32)object && (int)other->unk14 == kind &&
            (int)other->unk18 == mode && other->data != 0) {
            *state = fn_80121FCC(other, current + count);
            break;
        }
    }
    return 1;
}
