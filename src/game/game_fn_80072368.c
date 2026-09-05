typedef short s16;

typedef struct Entry {
    int field_00;
    int id;
    char pad_08[0xD8];
} Entry;

extern Entry lbl_80313120;

s16 fn_80072368(int id)
{
    s16 index = 0;
    char *entry;

    while (index < 0xAF) {
        if (id == (&lbl_80313120)[index].id) {
            return (s16)index;
        }
        index++;
    }
    return -1;
}
