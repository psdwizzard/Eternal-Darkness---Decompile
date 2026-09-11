typedef struct Object802019EC {
    unsigned char unk0[0x18];
    int id;
} Object802019EC;

typedef struct Entry802019EC {
    struct Entry802019EC *prev;
    struct Entry802019EC *next;
    int unk8;
    int unkC;
    int id;
    unsigned char unk14[0x10];
    Object802019EC *object;
    unsigned char unk28[0xC];
    void *owner;
} Entry802019EC;

typedef struct Manager802019EC {
    int unk0;
    Entry802019EC *head;
} Manager802019EC;

extern Manager802019EC *fn_802014AC(void);
extern int fn_8011FB4C(void *);

int fn_802019EC(int id, int group)
{
    Entry802019EC *entry;
    Manager802019EC *manager = fn_802014AC();

    for (entry = manager->head; entry != 0; entry = entry->next) {
        if ((group == -1 || entry->owner == 0 ||
             fn_8011FB4C(entry->owner) == group) &&
            entry->object != 0 && entry->object->id == id) {
            return entry->id;
        }
    }

    return -1;
}
