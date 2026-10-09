typedef struct Entry {
    int id;
    unsigned char pad[8];
    void **object;
} Entry;

extern Entry lbl_80325DB8[10];
extern void fn_800E7770(unsigned char);

void fn_800E77A8(unsigned char index, int id, void *object)
{
    Entry *entry;

    index++;
    while (index < 9) {
        entry = &lbl_80325DB8[index];
        if (id == entry->id && object == *entry->object) {
            fn_800E7770(index);
        }
        index++;
    }
}
