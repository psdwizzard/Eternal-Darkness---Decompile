typedef struct Entry80201A84 {
    struct Entry80201A84 *prev;
    struct Entry80201A84 *next;
    int unk8;
    int unkC;
    int id;
    unsigned char unk14[0x20];
    void *object;
} Entry80201A84;

typedef struct Manager80201A84 {
    int unk0;
    Entry80201A84 *head;
} Manager80201A84;

extern Manager80201A84 *fn_802014AC(void);

int fn_80201A84(void *object)
{
    Entry80201A84 *entry;
    Manager80201A84 *manager = fn_802014AC();

    for (entry = manager->head; entry != 0; entry = entry->next) {
        if (entry->object == object) {
            return entry->id;
        }
    }

    return -1;
}
