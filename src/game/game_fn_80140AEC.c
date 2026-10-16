typedef struct DebugEntry {
    void* object;
    void* owner;
    signed char active;
    unsigned char pad9;
    unsigned short timer;
} DebugEntry;

extern DebugEntry lbl_805B1268[6];
extern int lbl_8064CB8C;
extern unsigned char lbl_8064D018;
extern int fn_80140CD8(void* object, void* owner);

static inline void initialize_entry(DebugEntry* destination, void* object, void* owner)
{
    destination->active = 1;
    destination->object = object;
    destination->owner = owner;
    destination->timer = 200;
}

void fn_80140AEC(void* object, void* owner)
{
    int index;
    int i;
    DebugEntry* entry;
    DebugEntry* base;
    unsigned short minimum;

    if (lbl_8064CB8C != 0 && object != 0) {
        index = -1;
        if ((signed char)lbl_8064D018 > 0)
            index = fn_80140CD8(object, owner);
        if (index == -1) {
            base = lbl_805B1268;
            entry = base;
            for (i = 0; i < 6; i++, entry++) {
                if (entry->active == 0) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                minimum = 201;
                entry = base;
                for (i = 0; i < 6; i++, entry++) {
                    if (entry->timer < minimum) {
                        minimum = entry->timer;
                        index = i;
                    }
                }
            }
            initialize_entry(&lbl_805B1268[index], object, owner);
            lbl_8064D018++;
        } else {
            lbl_805B1268[index].timer = 200;
        }
    }
}
