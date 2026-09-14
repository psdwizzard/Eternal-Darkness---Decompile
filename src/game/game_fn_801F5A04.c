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
        if ((result->flags & (1 << i)) != 0 && (used & (1 << i)) == 0) {
            s16 index = fn_801F6054(lbl_8064D78A, lbl_8064D788,
                                    lbl_8064D790, value, argument);
            s16 other;
            u16 j;
            lbl_8064D78A = index;
            lbl_8064D78C[index] = value;
            result->values[i] = *(volatile s16*)&lbl_8064D78A;
            used |= 1 << i;
            for (j = i + 1; j < 11; j++) {
                other = result->values[j];
                if (other != -1) {
                    u32 other_bit = 1 << j;
                    if ((result->flags & other_bit) != 0 &&
                        (used & other_bit) == 0 && value == other) {
                        used |= other_bit;
                        result->values[j] = lbl_8064D78A;
                    }
                }
            }
        }
        }
    }
}
