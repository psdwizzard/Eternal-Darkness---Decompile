typedef void (*EntryCallback)(int, int);
typedef void (*BeginCallback)(int, int);
typedef void (*DoneCallback)(int);

typedef struct WorkEntry {
    unsigned int flags;
    int side;
    EntryCallback callback;
    int callback_arg;
    short adjustment;
    short scale;
    unsigned int trigger;
    unsigned int period;
    unsigned int counter;
} WorkEntry;

typedef struct WorkList {
    BeginCallback begin;
    WorkEntry* entries;
    DoneCallback done;
    int callback_arg;
    int active;
    int count;
    int index;
    unsigned int flags;
} WorkList;

extern unsigned int lbl_8064D050;
extern int lbl_8064D06C;
extern WorkList* lbl_8064D078;
extern unsigned int fn_80144760(unsigned int, int, short, int);
extern int fn_80144A2C(unsigned int, short, short, int);

int fn_80144C4C(WorkList* list)
{
    int result = 0;
    WorkEntry* entry;
    int remaining;

    list->flags |= 2;
    if (list->active != 0)
        result = 4;
    if (lbl_8064D078 != 0 && list != lbl_8064D078) {
        result |= 2;
        if (list->active == 0 && list->begin != 0)
            list->begin(list->callback_arg, 2);
    }
    if (result == 0) {
        entry = list->entries;
        lbl_8064D06C = 0;
        result = 1;
        if (list->begin != 0)
            list->begin(list->callback_arg, 1);
        if (lbl_8064D050 == 0) {
            remaining = list->count;
            while (remaining > 0) {
                if (entry->callback != 0) {
                    if (entry->trigger != 0) {
                        unsigned int mask = fn_80144760(entry->flags, 1, entry->adjustment, list->index);
                        if ((mask | (entry->flags == 0)) != 0) {
                            if (lbl_8064D06C != 0)
                                goto next;
                            if (entry->counter == entry->trigger + entry->period)
                                entry->counter = entry->trigger;
                            if (entry->counter == 0 || entry->counter == entry->trigger)
                                entry->callback(fn_80144A2C(mask, entry->adjustment, entry->scale, list->index), entry->callback_arg);
                            entry->counter++;
                        } else {
                            entry->counter = 0;
                        }
                    } else if (lbl_8064D06C == 0) {
                        unsigned int mask = fn_80144760(entry->flags, entry->side, entry->adjustment, list->index);
                        if ((mask | (entry->flags == 0)) != 0)
                            entry->callback(fn_80144A2C(mask, entry->adjustment, entry->scale, list->index), entry->callback_arg);
                    }
                }
            next:
                remaining--;
                entry++;
            }
        }
        if (list->done != 0)
            list->done(list->callback_arg);
    }
    list->flags &= ~2u;
    return result;
}
