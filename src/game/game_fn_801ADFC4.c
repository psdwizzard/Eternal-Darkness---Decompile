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
    u8 padding01[7];
    struct Entry* next;
    struct Entry* previous;
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

u32 fn_801ADFC4(Source* first_source, Source* second_source, u8 value1,
                u8 value69, u8 value6A)
{
    Entry* second;
    Entry* first;
    u32 first_amount;
    u32 second_amount;
    u32 id;

    fn_801ADC08();
    id = fn_801AD9F4(&first);
    if (id != 0xFFFFFFFF) {
        if (fn_801AD9F4(&second) != 0xFFFFFFFF) {
            first->next = second;
            second->previous = first;
            first_amount = fn_801ADE0C(first, first_source, value1, 0, 0,
                                       value69, value6A);
            second_amount = fn_801ADE0C(second, second_source, value1, 0x7F,
                                        0, value69, value6A);
            fn_801ADBC0();
            DVDOpen(first->source->owner, first->work);
            DVDOpen(second->source->owner, second->work);
            while (DVDReadAsyncPrio(first->work, first->buffer, first_amount,
                               first->source->value08, fn_801AE6B0, 2) == 0) {
            }
            while (DVDReadAsyncPrio(second->work, second->buffer, second_amount,
                               second->source->value08, fn_801AE6B0, 2) == 0) {
            }
            return id;
        }
        first->state = 0;
        id = 0xFFFFFFFF;
    }
    fn_801ADBC0();
    return id;
}
