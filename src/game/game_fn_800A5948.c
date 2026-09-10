typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry800A5948 {
    u8 pad0[0x2C];
    u32 value;
    u8 pad30[0x44];
} Entry800A5948;

typedef struct List800A5948 {
    u8 pad0[0xB0];
    u16 count;
    u8 padB2[2];
    Entry800A5948* entries;
} List800A5948;

extern List800A5948* fn_8015C28C(int);
extern int fn_8013B8C0(void*, void*);

int fn_800A5948(u32 value, void* unused, void* object)
{
    List800A5948* list = fn_8015C28C(2);
    int result = 0;
    int i;
    Entry800A5948* entry;

    if (list != 0) {
        for (i = 0; i < list->count && result == 0; i++) {
            entry = &list->entries[i];
            if (value == entry->value && fn_8013B8C0(object, entry) != 0) {
                result = 1;
            }
        }
    }
    return result;
}
