typedef short s16;

typedef struct ScrollEntry {
    int value;
    void* object;
    char pad08[0x1C];
    void* range;
    char pad28[0x4];
} ScrollEntry;

typedef struct ListGroup {
    void* item[6];
} ListGroup;

typedef struct ScrollState {
    char pad000[0x108];
    ScrollEntry entries[12];
    ScrollEntry shadows[12];
    char pad528[0x9A0 - 0x528];
    ListGroup lists;
} ScrollState;

/* The cursor begins at the menu state, then addresses one shadow entry. */
typedef union ScrollCursor {
    ScrollState state;
    ScrollEntry entry;
} ScrollCursor;

typedef struct ScrollPos {
    int x;
    int y;
    int z;
} ScrollPos;

extern ScrollState lbl_80330D80;
extern float lbl_8064CCB8;
extern int lbl_8064CCC4;
extern int lbl_8064CCC8;
extern int lbl_8064CCD4;
extern const float lbl_8064FE98;
extern double lbl_8064FE78;

extern void fn_80144C40(void);
extern int fn_801E8D24(void*);
extern int fn_801E8D34(void*);
extern int fn_801E8D3C(void*);
extern void fn_801E8B6C(void*, s16);
extern int fn_80157858(void*);
extern int fn_8010D36C(void*);
extern void fn_801F69F0(ScrollPos*, float*, int);
extern void fn_8011F0E8(void*, float*);
extern void fn_80117EF0(void);
extern int fn_8010A32C(int, int, int);
extern void fn_801E5FB0(int);

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void fn_8010D4BC(s16 delta)
{
    register ScrollCursor* state = (ScrollCursor*)&lbl_80330D80;
    register ListGroup* lists;
    ScrollEntry* entry;
    float out[3];
    ScrollPos pos;
    int limit;
    int current;
    int row;
    int offset;
    int steps;
    float frac;

    fn_80144C40();
    switch (lbl_8064CCD4) {
    case 4:
        lists = &state->state.lists;
        /* ASM: mr makes the separately materialized list base opaque to address folding. */
        asm { mr lists, lists }
        row = fn_801E8D24(lists->item[1]) * 2;
        offset = fn_801E8D24(state->state.lists.item[0]);
        offset += row;
        offset *= sizeof(ScrollEntry);
        entry = (ScrollEntry*)((char*)state->state.entries + offset);
        fn_80157858(entry->range);
        steps = 0;
        current = (s16)fn_8010D36C(entry->range);
        frac = (float)(current - fn_80157858(entry->range)) / lbl_8064FE98;
        lbl_8064CCB8 += frac;
        if (frac < 1.0f) {
            entry->value += delta;
        } else {
            while (lbl_8064CCB8 >= 1.0f) {
                lbl_8064CCB8 -= 1.0f;
                steps++;
            }
            entry->value += delta * steps;
        }
        limit = fn_8010D36C(entry->range);
        entry->value = MIN((s16)limit, MAX(entry->value, fn_80157858(entry->range)));
        pos.x = 0x140;
        pos.y = 0xA5;
        pos.z = entry->value;
        fn_801F69F0(&pos, out, 0);
        fn_8011F0E8(entry->object, out);

        state = (ScrollCursor*)state->state.shadows;
        /* ASM: mr retains the shadow table base before indexing; C otherwise folds the address. */
        asm { mr state, state }
        state = (ScrollCursor*)((char*)state + offset);
        if (state->entry.range != 0) {
            fn_80157858(state->entry.range);
            current = state->entry.value;
            pos.x = 0x140;
            pos.y = 0xA5;
            pos.z = current;
            if (frac < 1.0f) {
                state->entry.value = current + delta;
            } else {
                state->entry.value = current + delta * steps;
            }
            state->entry.value = MIN((s16)limit, MAX(state->entry.value, fn_80157858(state->entry.range)));
            fn_801F69F0(&pos, out, 0);
            fn_8011F0E8(state->entry.object, out);
        }
        break;
    case 3:
    case 5:
        break;
    case 2: {
        register ListGroup* menuLists;
        int oldPage;
        int oldLine;
        int newPage;
        int newLine;
        menuLists = &state->state.lists;
        /* ASM: mr makes the separately materialized list base opaque to address folding. */
        asm { mr menuLists, menuLists }
        oldPage = fn_801E8D3C(menuLists->item[4]) * 2;
        oldLine = fn_801E8D34(menuLists->item[4]) * 2;
        fn_801E8B6C(menuLists->item[4], delta);
        newPage = fn_801E8D3C(menuLists->item[4]) * 2;
        newLine = fn_801E8D34(menuLists->item[4]) * 2;
        if (oldPage != newPage) {
            fn_80117EF0();
            lbl_8064CCC4 = fn_8010A32C(newPage, 0, 6);
        }
        if (newLine != oldLine) {
            fn_801E5FB0(lbl_8064CCC8);
            lbl_8064CCC8 = 0;
        }
        break;
    }
    case 1: {
        register ListGroup* menuLists;
        menuLists = &state->state.lists;
        /* ASM: mr makes the separately materialized list base opaque to address folding. */
        asm { mr menuLists, menuLists }
        fn_801E8B6C(menuLists->item[2], delta);
        break;
    }
    case 0: {
        register ListGroup* menuLists;
        int oldPage;
        int oldLine;
        int newPage;
        int newLine;
        menuLists = &state->state.lists;
        /* ASM: mr makes the separately materialized list base opaque to address folding. */
        asm { mr menuLists, menuLists }
        oldPage = fn_801E8D3C(menuLists->item[1]) * 2;
        oldLine = fn_801E8D34(menuLists->item[1]) * 2;
        fn_801E8B6C(menuLists->item[1], delta);
        if (lbl_8064CCC4 != 0) {
            newPage = fn_801E8D3C(menuLists->item[1]) * 2;
            newLine = fn_801E8D34(menuLists->item[1]) * 2;
            if (oldPage != newPage) {
                fn_80117EF0();
                lbl_8064CCC4 = fn_8010A32C(newPage, 0, 6);
            }
            if (newLine != oldLine) {
                fn_801E5FB0(lbl_8064CCC8);
                lbl_8064CCC8 = 0;
            }
        }
        break;
    }
    }
}
