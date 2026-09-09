typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    s16 values[12];
    u32 flags;
    u32 field_1C;
} Entry;

typedef struct Table {
    u32 pad[2];
    Entry* entries;
} Table;

extern s16 lbl_8064D78A;
extern u16 lbl_8064D788;
extern s16* lbl_8064D78C;
extern void* lbl_8064D790;

extern s16 fn_801F6054(s16, u16, void*, s16, int);

#pragma use_lmw_stmw on

void fn_801F5A04(Entry* result, u32 entry_index, Table* table, int argument)
{
    s16 value;
    u16 i;
    u32 used = 0;

    *result = table->entries[entry_index];
    for (i = 0; i < 11; i++) {
        value = result->values[i];
        if (value == -1)
            continue;
        {
        u32 bit = 1 << i;
        if ((result->flags & bit) != 0 && (used & bit) == 0) {
            u16 j;
            s16 index = fn_801F6054(lbl_8064D78A, lbl_8064D788,
                                    lbl_8064D790, value, argument);
            lbl_8064D78A = index;
            lbl_8064D78C[index] = value;
            result->values[i] = index;
            used |= bit;
            for (j = i + 1; j < 11; j++) {
                s16 other = result->values[j];
                u32 other_bit = 1 << j;
                if (other != -1 && (result->flags & other_bit) != 0 &&
                    (used & other_bit) == 0 && value == other) {
                    used |= other_bit;
                    result->values[j] = lbl_8064D78A;
                }
            }
        }
        }
    }
}
