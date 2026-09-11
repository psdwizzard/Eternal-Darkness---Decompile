typedef struct Entry80201814 {
    struct Entry80201814 *prev;
    struct Entry80201814 *next;
    int unk8;
    int unkC;
    int id;
} Entry80201814;

typedef struct Manager80201814 {
    int unk0;
    Entry80201814 *head;
} Manager80201814;

extern Manager80201814 *fn_802014AC(void);
extern int fn_80201B44(void);
extern Entry80201814 *fn_80201B3C(void);

Entry80201814 *fn_80201814(int id)
{
    Entry80201814 *entry;
    Manager80201814 *manager = fn_802014AC();

    if (id == fn_80201B44()) {
        return fn_80201B3C();
    }

    if (id != 0) {
        for (entry = manager->head; entry != 0; entry = entry->next) {
            if (entry->id == id) {
                return entry;
            }
        }
    }

    return 0;
}
