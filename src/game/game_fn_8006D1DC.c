typedef signed int s32;

typedef struct Entry {
    s32 kind;
    unsigned char pad_4[32];
} Entry;

extern Entry *lbl_8064C8D4;

Entry *fn_8006D1DC(s32 kind)
{
    Entry *entry = lbl_8064C8D4;
    Entry *result = 0;
    s32 i;

    for (i = 0; i < 33;) {
        if (entry->kind == kind) {
            result = entry;
            break;
        }
        if ((++entry)->kind == kind) {
            result = entry;
            break;
        }
        if ((++entry)->kind == kind) {
            result = entry;
            break;
        }
        if ((++entry)->kind == kind) {
            result = entry;
            break;
        }
        entry++;
        i += 3;
    }
    return result;
}
