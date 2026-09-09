typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    s16 values[12];
    u32 flags;
} Entry;

extern s16* lbl_8064D78C;
extern void* lbl_8064D790;
extern void fn_801F5D28(void*);

#pragma use_lmw_stmw on

void fn_801F5B60(Entry* entry, int unused1, void* unused2, int release)
{
    u32 bit;
    s16 value;
    u16 i;
    u32 used = 0;

    for (i = 0; i < 11; i++) {
        value = entry->values[i];
        if (value != -1) {
            bit = 1 << i;
            if ((entry->flags & bit) != 0 && (used & bit) == 0) {
                u16 j;
                s16 replacement = lbl_8064D78C[value];
                used |= bit;
                entry->values[i] = replacement;
                for (j = i + 1; j < 11; j++) {
                    s16 other = entry->values[j];
                    if (other != -1) {
                        u32 other_bit = 1 << j;
                        if ((entry->flags & other_bit) != 0 &&
                            (used & other_bit) == 0 && value == other) {
                            entry->values[j] = replacement;
                            used |= other_bit;
                        }
                    }
                }
                if (release != 0) {
                    fn_801F5D28((char*)lbl_8064D790 + value * 12);
                }
            }
        }
    }
}
