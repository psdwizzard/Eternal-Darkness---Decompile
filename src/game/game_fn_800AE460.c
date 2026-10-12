typedef unsigned char u8;
typedef unsigned short u16;

typedef struct SoundEntry {
    u8 kind;
    u8 pad1[3];
    int stop;
    u16 id;
    u16 state;
    u16 flags;
    u16 durations[4];
    u8 pad16[2];
    unsigned int timer;
    int handle;
} SoundEntry;

extern SoundEntry lbl_8031F718[5];
extern void fn_800AE348(SoundEntry*);
extern void fn_800AE35C(SoundEntry*, unsigned int);
extern int fn_800AE368(SoundEntry*, unsigned int);
extern int fn_8006BE44(void);
extern int fn_800AE5C4(int, int, int, int, u16*, u8*, int);

void fn_800AE460(int owner)
{
    /* Sound types for the five entries, in retail table order. */
    int types[5] = { 0x3B, 0x3D, 0x3E, 0x3C, 0x55 };
    u8 volume;
    int* type = types;
    SoundEntry* entry = lbl_8031F718;
    int i;

    i = 0;
    do {
        fn_800AE348(entry);
        if (fn_800AE368(entry, entry->durations[entry->state])) {
            fn_800AE35C(entry, 0);
            entry->durations[entry->state] = 0;
            switch (entry->state) {
            case 0:
                break;
            case 1:
                entry->state = 0;
                break;
            case 2:
                entry->state = 3;
                if (entry->kind <= fn_8006BE44()) {
                    volume = 100;
                    entry->handle = fn_800AE5C4(entry->handle, owner, *type,
                                              entry->stop, &entry->id,
                                              &volume, entry->flags);
                }
                break;
            case 3:
                entry->state = 1;
                break;
            }
        }
        ++i;
        ++entry;
        ++type;
    } while (i < 5);
}

