typedef unsigned int u32;

typedef struct Slot {
    void* owner;
    u32 capacity;
} Slot;

typedef struct Object {
    char pad_0[0x118];
    u32 source;
    u32 size;
    char pad_120[4];
    Slot* slot;
} Object;

extern void* fn_801358AC(Slot*);
extern int fn_8015E830(u32);
extern void VIWaitForRetrace(void);
extern void fn_8013535C(void);
extern void fn_8013530C(void);
extern void fn_8015CBB0(u32, u32, void*);
extern void fn_8015B274(u32, u32, void*, u32, void*, u32, void*, int);
extern char lbl_805AD620[];
extern char lbl_805E29BC[];

/* The control flow and arguments are recovered; this initial honest-C pass is
 * retained if MWCC's register allocation does not yet match retail. */
void* fn_8013523C(void* manager, Object* object)
{
    void* data = fn_801358AC(object->slot);

    if ((object->source & 0x80000000) == 0 && fn_8015E830(object->source) == 0) {
        VIWaitForRetrace();
        if ((object->source & 0x80000000) == 0 && fn_8015E830(object->source) == 0) {
            fn_8013535C();
            fn_8013530C();
        }
    }
    if (object->source & 0x80000000) {
        fn_8015CBB0(object->source, object->size, data);
    } else {
        fn_8015B274(object->size, object->source, data,
                    object->slot->capacity, lbl_805AD620, 0x400,
                    lbl_805E29BC, 2);
    }
    return data;
}
