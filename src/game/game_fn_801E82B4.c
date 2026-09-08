typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u32 word0;
    u32 word4;
    u32 word8;
    u16 halfwordC;
} Entry;

extern Entry* fn_801E84BC(void);

int fn_801E82B4(u32 word4, u32 word8, u32 word0, u16 halfwordC)
{
    Entry* entry = fn_801E84BC();

    if (entry != 0) {
        entry->word0 = word0;
        entry->word4 = word4;
        entry->word8 = word8;
        entry->halfwordC = halfwordC;
        return 1;
    }
    return 0;
}
