typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct Object Object;
typedef struct Entry Entry;
typedef struct RangeControl RangeControl;

typedef struct Slot {
    unsigned char pad[0x24];
    Object* object;
    int value;
} Slot;

typedef struct SlotTable {
    Slot previous[6];
    Slot current[6];
    Slot previousShadow[6];
    Slot shadow[6];
    Slot extra[32];
    RangeControl* lists[2][3];
} SlotTable;

extern SlotTable lbl_80330D80;
extern u32* lbl_8064C4E0;
extern int fn_801E8D24(RangeControl*);
extern int fn_80201B44(void);
extern int fn_8015821C(Object*);
extern u64 fn_8020123C(int, int, int, int);
extern short fn_801578E8(Object*);
extern Entry* fn_80158598(int, int);
extern int fn_80158514(Entry*, int);
extern int fn_80158390(Entry*, u32***, int);
extern int fn_801E79FC(u32*, u32);
extern short fn_8015790C(Object*);
extern u32 fn_801578A0(Object*);
extern u32 fn_801E7578(u32);

int fn_8010B194(int action)
{
    register unsigned char* base = (unsigned char*)&lbl_80330D80;
    register RangeControl** lists;
    register Slot* shadow;
    register RangeControl* column;
    int row;
    register u32 selection;
    register int offset;
    register Slot* slot;
    Object* object;
    int value;

    /* ASM: addi preserves the list-bank base; C folds it into the load offset. */
    asm { addi lists, base, 0x9A0 }
    row = 2 * fn_801E8D24(lists[1]);
    /* ASM: lwz uses the retained table base; C rematerializes the global address. */
    asm { lwz column, 0x9A0(base) }
    selection = fn_801E8D24(column);
    selection += row;
    /* ASM: addi retains the shadow-bank base; C folds it into the member offset. */
    asm { addi shadow, base, 0x318 }
    offset = selection * sizeof(Slot);
    /* ASM: add reuses the slot ordinal register for its address.
     * C instead coalesces the ordinal with the byte displacement. */
    asm { add selection, shadow, offset }

    slot = (Slot*)selection;
    if (slot->object != 0) {
        object = slot->object;
        value = slot->value;
    } else {
        register Slot* current;
        /* ASM: addi retains the current-bank base before indexing; C combines the offsets. */
        asm { addi current, base, 0x108 }
        value = slot->value;
        /* ASM: add reuses the selected-slot register after reading its value;
         * C folds this address into indexed member addressing. */
        asm { add selection, current, offset }
        slot = (Slot*)selection;
        object = slot->object;
    }
    switch (action) {
    case 0: {
        int owner = fn_80201B44();
        if (fn_8015821C(object) == 12 &&
            (u32)(fn_8020123C(0x34, owner, owner, 0) & 0xFFFFFFFFULL) == 0) {
            return 0;
        }
        return fn_801578E8(object);
    }
    case 1: {
        Entry* entry = fn_80158598(fn_80201B44(), 0);
        if (fn_80158514(entry, value) == -1) {
            return fn_80158390(entry, (u32***)object, -1);
        }
        return 1;
    }
    case 2:
        return 1;
    case 3:
        if (fn_801E79FC(lbl_8064C4E0, 0x25A)) {
            register int result;
            fn_8015790C(object);
            /* ASM: mr forwards the lha-extended return register; a C
             * short-to-int conversion emits a redundant extsh. */
            asm { mr result, r3 }
            return result;
        }
        return 0;
    case 4:
        return (int)fn_801E7578(fn_801578A0(object)) > 1;
    default:
        return 0;
    }
}
