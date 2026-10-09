typedef unsigned char u8;
typedef unsigned short u16;

typedef struct ObjectEntry {
    void *object;
    u8 pad04[0x38];
} ObjectEntry;

extern void *fn_8015C5E4(int selector, u16 *count);
extern int fn_80201A84(void *object);
extern void fn_800E7154(int id, void *object);

void fn_80047674(void *state, void *object)
{
    u16 count;
    u16 index;
    ObjectEntry *entries;

    entries = fn_8015C5E4(2, &count);
    if (entries != 0) {
        for (index = 0; index < count; index++) {
            if (object == entries[index].object) {
                fn_800E7154(fn_80201A84(state), object);
                return;
            }
        }
    }
}
