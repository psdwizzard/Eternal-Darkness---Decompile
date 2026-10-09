typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ObjectEntry {
    u32 object;
    u8 pad04[0x38];
} ObjectEntry;

extern ObjectEntry *fn_8015C5E4(int selector, u16 *count);
extern int fn_80201A84(void *object);
extern void fn_800E7050(int owner, u32 object);

void fn_800475E8(void *state, u32 object)
{
    u16 count;
    u16 index;
    ObjectEntry *entries;

    entries = fn_8015C5E4(2, &count);
    if (entries != 0) {
        for (index = 0; index < count; index++) {
            if (object == entries[index].object) {
                fn_800E7050(fn_80201A84(state), object);
                return;
            }
        }
    }
}
