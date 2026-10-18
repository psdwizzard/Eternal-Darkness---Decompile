typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Source {
    void* owner;
    u32 padding04;
    u32 value08;
    u32 size;
} Source;

typedef struct Entry {
    u8 state;
    u8 padding01[15];
    Source* source;
    u8 work[72];
    void* buffer;
} Entry;

extern void fn_801ADC08(void);
extern void fn_801ADBC0(void);
extern u32 fn_801AD9F4(Entry**);
extern u32 fn_801ADE0C(Entry*, Source*, u8, u8, u8, u8, u8);
extern void fn_801AE6B0(void);
extern void DVDOpen(void*, void*);
extern int DVDReadAsyncPrio(void*, void*, u32, u32, void (*)(void), u32);

u32 fn_801ADEEC(Source* source, u8 value1, u8 value2, u8 value3,
                u8 value69, u8 value6A)
{
    Entry* entry;
    u32 amount;
    u32 id;

    fn_801ADC08();
    id = fn_801AD9F4(&entry);
    if (id != 0xFFFFFFFF) {
        amount = fn_801ADE0C(entry, source, value1, value2, value3,
                             value69, value6A);
        fn_801ADBC0();
        DVDOpen(entry->source->owner, entry->work);
        while (DVDReadAsyncPrio(entry->work, entry->buffer, amount,
                           entry->source->value08, fn_801AE6B0, 2) == 0) {
        }
        return id;
    } else {
        fn_801ADBC0();
        return id;
    }
}
